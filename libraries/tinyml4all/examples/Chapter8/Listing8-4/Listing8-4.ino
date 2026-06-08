/**
* Listing 8-4: Classify continuous motion using LSTM model
*
* Required hardware: Arduino Nano BLE Sense
*/
#include "./MotionLSTM.h"
#include <Arduino_LSM9DS1.h>
#include <tinyml4all.h>
// ARENA is the amount of memory to reserve for the model
// larger models needs more memory, but there's not a
// formula to calculate the optimal value
// is a trial-and-error process
#define ARENA 20000
tinyml4all::LSTM<ARENA> lstm;
tinyml4all::LSM9DS1 imu;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("TensorFlow LSTM demo");
    imu.begin();
    lstm.begin();
}
void loop() {
    // read accelerometer and gyroscope
    imu.readAcceleration();
    imu.readGyroscope();
    // append readings to internal RNN queue
    lstm.append(imu.ax, imu.ay, imu.az, imu.gx, imu.gy, imu.gz);
    // await until queue is full
    if (!lstm.isReady())
        return;

    // run classification
    if (!lstm.predict()) {
        Serial.println(lstm.error());
        return;
    }
    // lstm.label holds the name of the predicted class
    // lstm.idx holds the numeric id of the predicted class
    // lstm .value holds the numeric output (for regression tasks only)
    // lstm.confidence is the probability of the prediction
    // (from 0 to 1)
    // lstm.confidences is an array with the confidences of all the classes
    // (one for each class for classification)
    // lstm.outputsAsString returns each class' score, from
    // 0 to 1 (classification only)
    Serial.print("Predicted class ");
    Serial.print(lstm.label);
    Serial.print(" with confidence ");
    Serial.println(lstm.confidence);
    Serial.print(" > Scores: ");
    Serial.println(lstm.outputsAsString());
    delay(1000);
}