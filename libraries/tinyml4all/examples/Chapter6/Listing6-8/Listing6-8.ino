/**
* Listing 6-8: Audio wake word detection using Edge Impulse
*
* Required hardware: Arduino Nano BLE Sense
*/
// next line *must* match with the window increase value in the Impulse Design page from EI Studio
#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW (1000 / 250)
#include <PDM.h>
// replace with the correct name of the library
// downloaded from Edge Impulse Studio
#include <keyword_spotting_inferencing.h>
#include <tinyml4all.h>

tinyml4all::PDMicrophone mic;
tinyml4all::Impulse impulse;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Keyword spotting with Edge Impulse");
    // match the volume with the one used for data collection!
    mic.frequency("16 khz");
    mic.volume(30);
    mic.begin();
    // init Edge Impulse library
    impulse.begin();
    // while testing, you can enable verbose output by
    // setting this value to true
    impulse.verbose(false);
}

void loop() {
    // await for audio data to be ready
    mic.await();

    // feed data to the impulse queue
    if (!impulse.queue(mic)) {
        Serial.println(impulse.error());
        return;
    }

    // skip unknown words
    if (impulse.label() != "wakeword")
        return;

    Serial.print("Wake word detected with confidence ");
    Serial.println(impulse.confidence());
    // customize here with your own logic
}