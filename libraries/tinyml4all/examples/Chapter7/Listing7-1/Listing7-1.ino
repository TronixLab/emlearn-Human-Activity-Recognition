/**
* Listing 7-1: Collect images from camera
*
* Required hardware: ESP32 camera
*/
#include <tinyml4all.h>

tinyml4all::Camera camera;

void setup() {
    // increase Serial speed for fast data transmission
    Serial.begin(115200 * 2);
    while (!Serial);

    Serial.println("Collect images");
    // choose model from list
    camera.promptModel();
    // next times, you can set it directly by name
    //camera.setModel("aithinker");
    // configure camera for collection mode
    camera.collecting();
    // init camera (will throw an error on failure)
    camera.begin();
}

void loop() {
    // grab a new frame
    if (!camera.grab()) {
        Serial.println("Can't grab new frame");
        return;
    }

    // print frame to Serial (to be read from Python)
    camera.print();
    delay(300);
}