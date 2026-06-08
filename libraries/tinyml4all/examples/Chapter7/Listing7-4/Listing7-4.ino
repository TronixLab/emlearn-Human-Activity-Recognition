/**
* Listing 7-4: Debug object detection results
*
* Required hardware: ESP32 camera
*
* Notes: when using ESP32 boards, don't forget
* to enable PSRAM from the Tools menu!
*/
#include <object-detection_inferencing.h>
#include <tinyml4all.h>

tinyml4all::Camera camera;
tinyml4all::Impulse impulse;


void setup() {
    Serial.begin(115200 * 2);
    while (!Serial);

    delay(3000);
    ESP_LOGI("App", "Running...");
    Serial.println("Run Edge Impulse Object Detection");
    // choose model from list
    //camera.promptModel();
    // next times, you can set it directly by name
    // camera.setModel("wroom-s3");
    // configure camera for inference mode
    camera.inferencing();
    // init camera
    camera.begin();
    // init Edge Impulse model
    impulse.begin();
}

void loop() {
    // gran new frame
    if (!camera.grab()) {
        Serial.println("Can't grab new frame");
        return;
    }

    // print frame
    camera.print();

    // run impulse
    // !!! will overwrite original frame !!!
    if (!impulse.run(camera)) {
        Serial.println(impulse.error());
        return;
    }

    // print how many objects have been detected
    Serial.print("Found ");
    Serial.print(impulse.count());
    Serial.println(" object(s)");

    // print objects with coordinates
    for (int i = 0; i < impulse.count(); i++) {
        auto object = impulse.object(i);
        Serial.print(" > ");
        Serial.print(object.label);
        Serial.print(" at coordinates ");
        // cx, cy are the coordinates of the
        // center of the object
        Serial.print(object.cx);
        Serial.print(", ");
        Serial.print(object.cy);
        Serial.print(" (confidence ");
        Serial.print(object.confidence);
        Serial.println(")");
    }
}