/**
* Listing 3-1
* Collect RGB + distance data in CSV format (unattended).
*
* Required hardware: Arduino Nano BLE Sense.
* Required hardware: Ultrasonic distance sensor (HC-SR04)
*/
#include <Arduino_APDS9960.h>
#include <tinyml4all.h>

#define ECHO 2
#define TRIG 3

using tinyml4all::printCSV;
using tinyml4all::ultrasonicDistance;

tinyml4all::APDS9960 sensor;
tinyml4all::Ultrasonic ultrasonic(ECHO, TRIG);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Collect RGB + distance as CSV");
    // init color and distance sensors
    sensor.begin();
    ultrasonic.begin();
}

void loop() {
    // read R, G, B
    sensor.readColor();
    // read distance in millimeters
    uint16_t distance = ultrasonic.millimiters();// print data as CSV
    printCSV(sensor.r, sensor.g, sensor.b, distance);
    delay(1000);
}