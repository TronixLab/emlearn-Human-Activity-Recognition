/**
* Listing 2-2
* Collect RGB data in CSV format without user prompt.
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

    Serial.println("Collect fruits colors as CSV");
    // init sensor (will throw an error if it fails)
    sensor.begin();
}

void loop() {
    // read sensor values and print in CSV format
    // without user intervention
    sensor.readColor();
    printCSV(sensor.r, sensor.g, sensor.b);
    delay(1000);
}