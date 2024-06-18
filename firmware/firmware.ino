/**
 * Run a TensorFlow model to predict the IRIS dataset
 * For a complete guide, visit
 * https://eloquentarduino.com/tensorflow-lite-esp32
 */

// replace with your own model
// include BEFORE <eloquent_tinyml.h>!
#include "model.h"
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

// this is trial-and-error process
// when developing a new model, start with a high value
// (e.g. 10000), then decrease until the model stops
// working as expected
#define ARENA_SIZE 2000

Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

float x0[4] = {0.22222222222f, 0.62500000000f, 0.06779661017f, 0.04166666667f};
float x1[4] = {0.75000000000f, 0.50000000000f, 0.62711864407f, 0.54166666667f};
float x2[4] = {0.55555555556f, 0.54166666667f, 0.84745762712f, 1.00000000000f};

/**
 * 
 */
void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__TENSORFLOW IRIS__");
    
    /*  configure input/output
        (not mandatory if you generated the .h model using the everywhereml Python package)
    */
    // tf.setNumInputs(4);
    // tf.setNumOutputs(3);
    
    /*  add required ops
        (not mandatory if you generated the .h model using the everywhereml Python package)
    */
    // tf.resolver.AddFullyConnected();
    // tf.resolver.AddSoftmax();
    
    while (!tf.begin(irisModel).isOk())
        Serial.println(tf.exception.toString());
}


void loop() {
    
    // classify sample from class 0
    if (!tf.predict(x0).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    
    Serial.print("expcted class 0, predicted class ");
    Serial.println(tf.classification);
    
    // classify sample from class 1
    if (!tf.predict(x1).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    
    Serial.print("expcted class 1, predicted class ");
    Serial.println(tf.classification);
    
    // classify sample from class 2
    if (!tf.predict(x2).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    
    Serial.print("expcted class 2, predicted class ");
    Serial.println(tf.classification);
    
    // how long does it take to run a single prediction?
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");
    
    delay(5000);
}