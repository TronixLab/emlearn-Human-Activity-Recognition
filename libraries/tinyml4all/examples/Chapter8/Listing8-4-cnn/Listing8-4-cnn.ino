/**
* Listing 8-4: Classify continuous motion using cnn model
*
* Required hardware:
*/
#include "./MotionCNN.h"
#include "./sample.h"
// ARENA is the amount of memory to reserve for the model
// larger models needs more memory, but there's not a
// formula to calculate the optimal value
// is a trial-and-error process
#define ARENA 20000
tinyml4all::CNN1D<ARENA> cnn;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("TensorFlow CNN1D demo");
    cnn.begin();
}

void loop() {
    // run classification
    if (!cnn.predict(sample)) {
        Serial.println(cnn.error());
        return;
    }

    // cnn.label holds the name of the predicted class
    // cnn.idx holds the numeric id of the predicted class
    // cnn .value holds the numeric output (for regression tasks only)
    // cnn.confidence is the probability of the prediction
    // (from 0 to 1)
    // cnn.confidences is an array with the confidences of all the classes
    // (one for each class for classification)
    // cnn.outputsAsString returns each class' score, from
    // 0 to 1 (classification only)
    Serial.println("Expected label is 3");
    Serial.print("Predicted class ");
    Serial.print(cnn.label);
    Serial.print(" with confidence ");
    Serial.println(cnn.confidence);
    Serial.print(" > Scores: ");
    Serial.println(cnn.outputsAsString());
    delay(1000);
}