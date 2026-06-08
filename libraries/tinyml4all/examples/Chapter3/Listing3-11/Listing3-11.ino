/**
* Listing 3-11
* Predict distance from RGB
*
* Required hardware: Arduino Nano BLE Sense.
* Optional hardware: Ultrasonic distance sensor (HC-SR04)
*/
#include <Arduino_APDS9960.h>
#include <tinyml4all.h>
// this is the file generated in Listing 3-10
#include "./DistanceChain.h"

// replace with your own pins, if different
#define ECHO 2
#define TRIG 3

using tinyml4all::printCSV;

tinyml4all::APDS9960 sensor;
tinyml4all::Ultrasonic ultrasonic(ECHO, TRIG);
tinyml4all::DistanceChain chain;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Predict distance from RGB");
    // init sensors
    // will throw an error if something goes wrong
    sensor.begin();
    ultrasonic.begin();
}

void loop() {
    // read R, G, B
    sensor.readColor();
    // feed data to the regression chain
    // should always return true
    if (!chain(sensor.r, sensor.g, sensor.b))
        return;

    // the chain output is in output.regression.value
    Serial.print("Predicted distance: ");
    Serial.print(chain.output.regression.value);
    Serial.print(" mm");
    // if a distance sensor is available,
    // print the error between measured and predicted
    uint16_t distance = ultrasonic.millimiters();
    uint16_t error = chain.output.regression.value - distance;
    Serial.print(" (");
    Serial.print(error);
    Serial.print(" mm off)");
    Serial.println();
    delay(1000);
}