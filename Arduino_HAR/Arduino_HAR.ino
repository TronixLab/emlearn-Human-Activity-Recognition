#include <Arduino_BMI270_BMM150.h>
#include "eml_iir_filter.h"
#include "eml_FFT.h"
#include "boxcar_128_lut.h"
#include "SlidingWindow.h"
#include "StandardScaler.h"
#include "SpectralFeatures.h"
#include "NeuralNetworkClassifier.h"

// IIR filter coefficients for a 4th order Butterworth low-pass filter
// with cutoff frequency of 5 Hz at 100 Hz sampling rate
constexpr int IIR_STAGES = 2;
constexpr int IIR_ORDER = 4;

// Compile-time assertion to ensure the IIR filter configuration is correct
static_assert(IIR_ORDER == (IIR_STAGES * 2), "IIR_ORDER must be 2 * IIR_STAGES");

// SOS coefficients for the IIR filter (b0, b1, b2, bn... a0, a1, a2, an... for each stage)
const float sos[12] = { 0.000062f, 0.000125f, 0.000062f, 1.000000f, -1.674661f, 0.704859f,
                        1.000000f, 2.000000f, 1.000000f, 1.000000f, -1.833125f, 0.866180f };

// Create IIR filter instances for each axis
EmlIIRFilter<IIR_ORDER, IIR_STAGES> iir_x(sos);
EmlIIRFilter<IIR_ORDER, IIR_STAGES> iir_y(sos);
EmlIIRFilter<IIR_ORDER, IIR_STAGES> iir_z(sos);

// Sensor data parameters
const float CONVERT_G_TO_MS2 = 9.80665f;
const int FREQUENCY_HZ = 100;
const int INTERVAL_MS = (1000 / (FREQUENCY_HZ + 1));
static unsigned long last_interval_ms = 0;

// Sliding window parameters (milliseconds)
constexpr uint16_t WINDOW_FRAME_SIZE_MS = 2000;
constexpr uint16_t WINDOW_FRAME_STRIDE_MS = 500;
constexpr size_t MAX_WINDOW_SAMPLES = (FREQUENCY_HZ * WINDOW_FRAME_SIZE_MS) / 1000;
constexpr size_t FFT_N = 128;
constexpr size_t FFT_BINS = (FFT_N / 2) + 1;

// Compile-time assertion to ensure the sliding window can hold at least FFT_N samples
static_assert(MAX_WINDOW_SAMPLES >= FFT_N, "Window frame must contain at least FFT_N samples");

// Create sliding window instance for 3-axis motion data
SlidingWindow<3, MAX_WINDOW_SAMPLES> motion_window;
float accX_frame[MAX_WINDOW_SAMPLES];
float accY_frame[MAX_WINDOW_SAMPLES];
float accZ_frame[MAX_WINDOW_SAMPLES];

// Create FFT instance with boxcar window
SingleSidedFFT<FFT_N> FFT(boxcar_128_lut, FREQUENCY_HZ);

// Buffers to hold FFT magnitudes for each axis
float fft_mag_x[FFT_BINS];
float fft_mag_y[FFT_BINS];
float fft_mag_z[FFT_BINS];

// Total features: 6 spectral features per axis * 3 axes
constexpr size_t TOTAL_FEATURES = 3 * SPECTRAL_FEATURES_PER_AXIS;

// Array to hold extracted features for classification
float features[TOTAL_FEATURES];

// Create scaler instance
StandardScaler scaler;

// Array to hold scaled features
float features_scaled[TOTAL_FEATURES];

// Define an array for class labels
const char *classes[] = { "clockwise", "horizontal", "idle", "vertical" };

// Array to hold prediction probabilities
float proba[TOTAL_FEATURES];

void setup() {
  // Initialize serial communication for debugging and CSV output
  Serial.begin(115200);
  while (!Serial)
    ;

  // Initialize the IMU sensor
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  // Initialize IIR filters and check for configuration errors
  EmlError iir_err_x = iir_x.init();
  EmlError iir_err_y = iir_y.init();
  EmlError iir_err_z = iir_z.init();

  if (iir_err_x != EmlOk || iir_err_y != EmlOk || iir_err_z != EmlOk) {
    Serial.println("IIR filter configuration error!");
    if (iir_err_x != EmlOk) {
      Serial.print("X error code: ");
      Serial.print((int)iir_err_x);
      Serial.print(" (");
      Serial.print(EmlIIRFilter<IIR_ORDER, IIR_STAGES>::errorName(iir_err_x));
      Serial.println(")");
    }
    if (iir_err_y != EmlOk) {
      Serial.print("Y error code: ");
      Serial.print((int)iir_err_y);
      Serial.print(" (");
      Serial.print(EmlIIRFilter<IIR_ORDER, IIR_STAGES>::errorName(iir_err_y));
      Serial.println(")");
    }
    if (iir_err_z != EmlOk) {
      Serial.print("Z error code: ");
      Serial.print((int)iir_err_z);
      Serial.print(" (");
      Serial.print(EmlIIRFilter<IIR_ORDER, IIR_STAGES>::errorName(iir_err_z));
      Serial.println(")");
    }
    while (1)
      ;
  }
  Serial.println("IIR filters initialized successfully.");

  // Initialize sliding window for motion data
  if (!motion_window.begin(FREQUENCY_HZ, WINDOW_FRAME_SIZE_MS, WINDOW_FRAME_STRIDE_MS)) {
    Serial.println("Sliding window configuration error!");
    while (1)
      ;
  }
  Serial.println("Sliding window initialized successfully.");

  // Initialize FFT and check for configuration errors
  EmlError fft_init_err = FFT.begin();
  if (fft_init_err != EmlOk) {
    Serial.print("FFT initialization error: ");
    Serial.print((int)fft_init_err);
    Serial.print(" (");
    Serial.print(SingleSidedFFT<FFT_N>::errorName(fft_init_err));
    Serial.println(")");
    while (1)
      ;
  }
  Serial.println("FFT initialized successfully.");
}

void loop() {
  // Variables to hold raw and filtered acceleration values
  float x, y, z, filt_x, filt_y, filt_z;

  // Read sensor values and print in CSV format
  if (millis() > last_interval_ms + INTERVAL_MS) {
    // Read raw acceleration values from the IMU
    IMU.readAcceleration(x, y, z);

    // Apply IIR filters to the raw acceleration data
    filt_x = iir_x.run(x * CONVERT_G_TO_MS2);
    filt_y = iir_y.run(y * CONVERT_G_TO_MS2);
    filt_z = iir_z.run(z * CONVERT_G_TO_MS2);

    // Push filtered 3-axis sample into sliding window.
    if (motion_window.pushSample(filt_x, filt_y, filt_z)) {
      // Frame layout is separated by axis for downstream processing.
      motion_window.windowFrame(accX_frame, accY_frame, accZ_frame);

      // Match notebook behavior: use the first FFT_N samples of each frame.
      const size_t fft_start = 0;

      EmlError fft_err_x = FFT.single_sided_FFT(accX_frame + fft_start, fft_mag_x);
      EmlError fft_err_y = FFT.single_sided_FFT(accY_frame + fft_start, fft_mag_y);
      EmlError fft_err_z = FFT.single_sided_FFT(accZ_frame + fft_start, fft_mag_z);

      if (fft_err_x != EmlOk || fft_err_y != EmlOk || fft_err_z != EmlOk) {
        Serial.println("FFT processing error!");
        if (fft_err_x != EmlOk) {
          Serial.print("FFT X error: ");
          Serial.print((int)fft_err_x);
          Serial.print(" (");
          Serial.print(SingleSidedFFT<FFT_N>::errorName(fft_err_x));
          Serial.println(")");
        }
        if (fft_err_y != EmlOk) {
          Serial.print("FFT Y error: ");
          Serial.print((int)fft_err_y);
          Serial.print(" (");
          Serial.print(SingleSidedFFT<FFT_N>::errorName(fft_err_y));
          Serial.println(")");
        }
        if (fft_err_z != EmlOk) {
          Serial.print("FFT Z error: ");
          Serial.print((int)fft_err_z);
          Serial.print(" (");
          Serial.print(SingleSidedFFT<FFT_N>::errorName(fft_err_z));
          Serial.println(")");
        }
        while (1)
          ;
      }

      // Extract spectral features (i.e., peak, mean, rms, psd, energy, std) from FFT magnitudes for each axis
      SpectralFeatureExtractor<FFT_BINS>::extractTo(fft_mag_x, features + 0 * SPECTRAL_FEATURES_PER_AXIS);
      SpectralFeatureExtractor<FFT_BINS>::extractTo(fft_mag_y, features + 1 * SPECTRAL_FEATURES_PER_AXIS);
      SpectralFeatureExtractor<FFT_BINS>::extractTo(fft_mag_z, features + 2 * SPECTRAL_FEATURES_PER_AXIS);

      // Scale the raw features using StandardScaler
      scaler.transform(features, features_scaled);

      // Pass scaled features to classifier to make prediction
      int32_t y_pred = NeuralNetworkClassifier_predict(features_scaled, StandardScaler::n_features);

      // Get prediction probabilities
      EmlError err = eml_net_predict_proba(&NeuralNetworkClassifier, features_scaled, StandardScaler::n_features, proba, 4);
      if (err == EmlOk) {
        // Print prediction
        Serial.print("Predicted Label: ");
        Serial.print(classes[y_pred]);
        Serial.print("\t Probability: ");
        Serial.print(proba[y_pred] * 100, 2);
        Serial.println("%");
      }
    }
    // Update interval timer after processing to maintain consistent timing regardless of processing duration
    // This ensures that the next sample is read at the correct interval even if processing takes some time.
    last_interval_ms = millis();
  }
}