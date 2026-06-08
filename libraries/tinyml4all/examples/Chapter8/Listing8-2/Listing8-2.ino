#include "./IrisMLP.h"
// ARENA is the amount of memory to reserve for the model.
// larger models need more memory, but there's not a
// formula to calculate the optimal value,
// is a trial-and-error process
#define ARENA 20000

tinyml4all::MLP<ARENA> mlp;

float setosa[] = {5.1, 3.5, 1.4, 0.2};
float virginica[] = {7.6, 3.0, 6.6, 2.1};
float versicolor[] = {6.8, 2.8, 4.8, 1.4};

void setup() {
  delay(3000);
    Serial.begin(115200);
    while (!Serial);

    Serial.println("TensorFlow MLP demo");
    // init network
    mlp.begin();
}

void loop() {
    // run network on given sample
    if (!mlp.predict(setosa)) {
        Serial.println(mlp.error());
        return;
    }
    // mlp.label holds the name of the predicted class
    // mlp.idx holds the numeric id of the predicted class
    // mlp .value holds the numeric output (for regression tasks only)
    // mlp.confidence is the probability of the prediction
    // (from 0 to 1)
    // mlp .confidences is an array with the confidences of all the classes
    // (one for each class for classification)
    // mlp.outputsAsString returns each class' score, from
    // 0 to 1 (classification only)
    Serial.print("Predicted class ");
    Serial.print(mlp.label);
    Serial.print(" with confidence ");
    Serial.println(mlp.confidence);
    Serial.print(" > Scores: ");
    Serial.println(mlp.outputsAsString());
    delay(3000);
}