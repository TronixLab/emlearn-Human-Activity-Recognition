/**
* Listing 2-1
* Collect RGB data in CSV format from user prompt.
*
* Required hardware: Arduino Nano BLE Sense.
*/
#include <Arduino_APDS9960.h>
#include <tinyml4all.h>

using tinyml4all::promptString;
using tinyml4all::promptInt;
using tinyml4all::printCSV;

tinyml4all::APDS9960 sensor;


void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Collect RGB values as CSV");
    // init sensor (will throw an error if it fails)
    sensor.begin();
}

void loop() {
    // get fruit name and number of samples from user
    String fruit = promptString("Which fruit is this?");
    int numSamples = promptInt("How many samples to capture?");

    for (int i = 0; i < numSamples; i++) {
        // read sensor values and print in CSV format
        sensor.readColor();
        printCSV(sensor.r, sensor.g, sensor.b, fruit);
        delay(1000);
    }
}