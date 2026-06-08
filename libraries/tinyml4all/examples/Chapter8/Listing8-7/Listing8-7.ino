/**
 * Listing 8-7: Image classification using TensorFLow
 */
#include "./PetsCNN2D.h"
#include "./cat.h"
// ARENA is the amount of memory to reserve for the model
// larger models needs more memory, but there's not a
// formula to calculate the optimal value
// is a trial-and-error process
#define ARENA 80000

tinyml4all::CNN2D<ARENA> cnn;

void setup() {
  delay(3000);
    Serial.begin(115200);
    while (!Serial);

    Serial.println("TensorFlow 2D CNN demo");
    cnn.begin();
}

void loop() {
    // run classification on cat
    if (!cnn.predict(cat)) {
        Serial.println(cnn.error());
        return;
    }
    // .label holds the name of the predicted class
    // .output holds the numeric output (for regression)
    // or class id (for classification)
    // .outputs in an array with all the outputs
    // (one for each class for classification)
    // .runtime_ms holds the duration of predictions
    // outputsAsString returns each class' score, from
    // 0 to 1 (classification only)
    Serial.print("Expected 1 (cat), predicted ");
    Serial.print(cnn.label);
    Serial.print(" with confidence ");
    Serial.println(cnn.confidence);
    Serial.print(" > Scores: ");
    Serial.println(cnn.outputsAsString());
    delay(1000);
}