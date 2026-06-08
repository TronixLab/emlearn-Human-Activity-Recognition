/**
* Listing 4-1: Read accelerometer + gyroscope data
*
* Required hardware: Arduino Nano BLE Sense.
*/
#include <Arduino_LSM9DS1.h>
#include <tinyml4all.h>

using tinyml4all::printCSV;

tinyml4all::LSM9DS1 imu;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Collect acc+gyro data as CSV");
    // init IMU sensor (will throw an error on failure)
    imu.begin();
}
void loop() {
    // read accelerometer and gyroscope
    imu.readAcceleration();
    imu.readGyroscope();
    printCSV(millis(), imu.ax, imu.ay, imu.az, imu.gx, imu.gy, imu.gz);
    // no manual delay, default sample rate is ~100 Hz
}