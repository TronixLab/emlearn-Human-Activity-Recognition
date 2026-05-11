#ifndef SPECTRAL_FEATURES_H
#define SPECTRAL_FEATURES_H

#include <math.h>
#include <stddef.h>

// Holds one set of spectral features for a single FFT magnitude vector.
// Field order matches Python notebook extract_spectral_features() output:
// peak, mean, rms, psd, energy, std_dev
struct SpectralFeatures {
  float peak;     // Maximum magnitude value
  float mean;     // Mean magnitude value
  float rms;      // Root Mean Square: sqrt(mean(mag^2))
  float psd;      // Power Spectral Density: sum(mag^2) / N
  float energy;   // Spectral Energy: sum(mag^2)
  float std_dev;  // Population Standard Deviation: sqrt(psd - mean^2)
};

// Number of scalar values packed per axis in a flat feature array.
constexpr size_t SPECTRAL_FEATURES_PER_AXIS = 6;
template <size_t N>
class SpectralFeatureExtractor {
public:
  // Extract spectral features from an FFT magnitude array of length N.
  // Returns a SpectralFeatures struct with all six features computed.
  static SpectralFeatures extract(const float *fft_mag) {
    float sum = 0.0f;
    float sum_sq = 0.0f;
    float peak = fft_mag[0];

    for (size_t i = 0; i < N; i++) {
      const float v = fft_mag[i];
      if (v > peak) peak = v;
      sum += v;
      sum_sq += v * v;
    }

    const float inv_N = 1.0f / (float)N;
    const float mean_val = sum * inv_N;           // mean(mag)
    const float energy = sum_sq;                  // sum(mag^2)
    const float psd = sum_sq * inv_N;             // sum(mag^2) / N
    const float rms = sqrtf(psd);                 // sqrt(mean(mag^2))
    const float variance = psd - (mean_val * mean_val);  // population variance
    const float std_dev = sqrtf(variance > 0.0f ? variance : 0.0f);

    SpectralFeatures f;
    f.peak = peak;
    f.mean = mean_val;
    f.rms = rms;
    f.psd = psd;
    f.energy = energy;
    f.std_dev = std_dev;
    return f;
  }

  // Extract features and write to a flat float array of length SPECTRAL_FEATURES_PER_AXIS (6).
  // Output order: [peak, mean, rms, psd, energy, std_dev]
  // Use with an offset into a larger feature buffer, e.g.:
  //   extractTo(fft_mag_x, features + 0 * SPECTRAL_FEATURES_PER_AXIS);
  //   extractTo(fft_mag_y, features + 1 * SPECTRAL_FEATURES_PER_AXIS);
  //   extractTo(fft_mag_z, features + 2 * SPECTRAL_FEATURES_PER_AXIS);
  static void extractTo(const float *fft_mag, float *out) {
    const SpectralFeatures f = extract(fft_mag);
    out[0] = f.peak;
    out[1] = f.mean;
    out[2] = f.rms;
    out[3] = f.psd;
    out[4] = f.energy;
    out[5] = f.std_dev;
  }
};

#endif  // SPECTRAL_FEATURES_H