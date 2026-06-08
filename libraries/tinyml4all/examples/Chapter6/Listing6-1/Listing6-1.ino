/**
 * Listing 6-1: Collect audio data from PDM microphone.
 *
 * Required hardware: Arduino Nano BLE Sense
 * Required hardware: or any board with a PDM microphone
 *
 * (e.g., Nano RP2040 Connect)
*/
#include <PDM.h>
#include <tinyml4all.h>

tinyml4all::PDMicrophone mic;

void setup() {
// increase Serial speed
    Serial.begin(115200 * 2);
    while (!Serial);

    Serial.println("Collect audio data");
    // refer to the board datasheet for the mic frequency
    // (Nano RP2040 Connect frequency is 21kHz, for example)
    mic.frequency("16 khz");
    // volume goes from 0 to 100
    mic.volume(30);
    // configure microphone
    mic.begin();
}

void loop() {
    // await data to be available
    mic.await();
    // send over Serial
    mic.print();
}