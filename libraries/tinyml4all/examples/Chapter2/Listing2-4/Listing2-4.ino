/**
* Listing 2-4
* Collect RGB data in CSV format and store on SD card.
*
* Required hardware: Arduino Nano BLE Sense.
* Required hardware: SPI SD card reader
*/
#include <SPI.h>
#include <SD.h>
#include <Arduino_APDS9960.h>
#include <tinyml4all.h>

tinyml4all::APDS9960 sensor;
tinyml4all::SDCard card;

// replace with the correct pin!
// see the SD card reader module datasheet to find this value
const uint8_t CS_PIN = 4;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("Collect fruits colors as CSV on SD card");
    // init sensor and SD card
    // then open file for writing
    // will throw an error if something goes wrong
    sensor.begin();
    card.begin(CS_PIN);
    card.writing("fruits.csv");
}

void loop() {
    // read sensor values and print in CSV format
    sensor.readColor();
    card.println(sensor.r, sensor.g, sensor.b);
    delay(1000);
}