#include <tinyml4all.h>
#include <Arduino_BMI270_BMM150.h>

using tinyml4all::promptString;
using tinyml4all::promptInt;
using tinyml4all::printCSV;

const float CONVERT_G_TO_MS2 = 9.80665f;
const int FREQUENCY_HZ = 100;
const int INTERVAL_MS = (1000 / (FREQUENCY_HZ + 1));
static unsigned long last_interval_ms = 0;
static unsigned long prev_interval_ms = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
}

void loop() {
  String motion = promptString("Which Motion is this?");
  int time_frame_min = promptInt("How many samples to capture in minutes?");

  uint32_t n_samples = time_frame_min * 60 * FREQUENCY_HZ;

  Serial.println("timestamp,accX,accY,accZ,motion");
  float x, y, z;
  prev_interval_ms = millis();
  while (true) {
    // read sensor values and print in CSV format
    if (millis() > last_interval_ms + INTERVAL_MS) {
      last_interval_ms = millis();
      IMU.readAcceleration(x, y, z);
      printCSV(last_interval_ms - prev_interval_ms, x * CONVERT_G_TO_MS2, y * CONVERT_G_TO_MS2, z * CONVERT_G_TO_MS2, motion);

      if ((last_interval_ms - prev_interval_ms) >= (time_frame_min * 60 * 1000)) {
        break;
      }
    }
  }
}
