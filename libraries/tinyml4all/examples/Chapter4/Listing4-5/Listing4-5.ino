/**
* Listing 4-5: Run Edge Impulse model on IMU data
*
* Required hardware: Arduino Nano BLE Sense
*/
// next line *must* match with the window increase value in the Impulse Design page from EI Studio
#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW (1000 / 400)
#include <continuous-motion_inferencing.h>
#include <Arduino_LSM9DS1.h>
#include <tinyml4all.h>

using tinyml4all::printCSV;

tinyml4all::LSM9DS1 imu;
tinyml4all::Impulse impulse;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Classify motion with Edge Impulse");
    imu.begin();
    
    // init EI model (will throw an error on failure)
    impulse.begin();
    impulse.verbose(false);
}

void loop() {
    // read accelerometer and gyroscope
    imu.readAcceleration();
    imu.readGyroscope();
    // queue data
    impulse.queue(
      imu.ax, imu.ay, imu.az,
      imu.gx, imu.gy, imu.gz
    );

    // when window of data is full, run prediction
    // otherwise return
    if (!impulse.isReady())
        return;

    Serial.print("Running prediction... ");

    // run inference
    if (!impulse.run()) {
        Serial.println(impulse.error());
        return;
    }

    // print results
    Serial.print("Predicted motion is ");
    Serial.print(impulse.label());
    Serial.print(" with confidence ");
    Serial.println(impulse.confidence());
}