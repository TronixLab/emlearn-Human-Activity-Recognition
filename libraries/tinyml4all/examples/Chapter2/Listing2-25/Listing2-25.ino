/**
* Listing 2-2530 AQ4
* Predict fruit from RGB color components.
*
* Required hardware: Arduino Nano BLE Sense.
*/
#include <Arduino_APDS9960.h>
#include <tinyml4all.h>
// put the generated file from Python inside the Arduino
// sketch folder!
#include "./FruitChain.h"

tinyml4all::APDS9960 sensor;
tinyml4all::FruitChain chain;


void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Fruits classification example");
    sensor.begin();
}

void loop() {
    sensor.readColor();
    // chain(input) will return true on success
    // false on error
    if (!chain(sensor.r, sensor.g, sensor.b))
        return;

    // the predicted human-readable label is in
    // chain.output.classification.label
    // the numeric output (0, 1, 2, ...) is in
    // chain.output.classification.idx
    Serial.print("I think this is ");
    Serial.println(chain.output.classification.label);
    delay(1000);
}