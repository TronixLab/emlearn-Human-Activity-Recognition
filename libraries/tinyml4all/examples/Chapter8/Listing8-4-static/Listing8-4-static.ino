/**
* Listing 8-4: Classify continuous motion using LSTM model
*
* Required hardware:
*/
#include "./MotionLSTM.h"
#include "./sample.h"
// ARENA is the amount of memory to reserve for the model
// larger models needs more memory, but there's not a
// formula to calculate the optimal value
// is a trial-and-error process
#define ARENA 20000
tinyml4all::LSTM<ARENA> lstm;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("TensorFlow LSTM demo");
    lstm.begin();
}

void loop() {
    // run classification
    if (!lstm.predict(sample)) {
        Serial.println(lstm.error());
        return;
    }

    // lstm.label holds the name of the predicted class
    // lstm.idx holds the numeric id of the predicted class
    // lstm .value holds the numeric output (for regression tasks only)
    // lstm.confidence is the probability of the prediction
    // (from 0 to 1)
    // lstm.confidences is an array with the confidences of all the classes
    // (one for each class for classification)
    // lstm.outputsAsString returns each class' score, from
    // 0 to 1 (classification only)
    Serial.println("Expected label is 3");
    Serial.print("Predicted class ");
    Serial.print(lstm.label);
    Serial.print(" with confidence ");
    Serial.println(lstm.confidence);
    Serial.print(" > Scores: ");
    Serial.println(lstm.outputsAsString());
    delay(1000);
}