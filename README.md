# tinyML-esp32

Practical exemple of the usage of TinyML with ESP32 module. In this example, we will create and train a Neural Network model using Python. Then, we will use the [everywhereml](https://github.com/eloquentarduino/everywhereml) library to convert the model to a C++ file that we will use do deploy our model to the ESP32 module. 

## Create and train the NN model

For this example, we will use the [iris dataset](https://scikit-learn.org/1.5/auto_examples/datasets/plot_iris_dataset.html). 

The ```train-tensorflow-model-for-embedded-ml.ipynb``` file is a [Jupyter Notebook](https://jupyter.org/) containing all the steps to create, train and convert our model for deploy on ESP32.

After run all steps, the Notebook will generate a String containing a C source-code of the model.

## Configuring the Arduino environment

In order to programming the firmware we will need:

* Arduino IDE installed;
* ESP32 board configured;
* The following libraries:
    * [tflm_esp32](https://www.arduino.cc/reference/en/libraries/tflm_esp32/)
    * [EloquentTinyML](https://github.com/eloquentarduino/EloquentTinyML)

## Using the trained model

After run all the steps of the Jupyter Notebook, copy the C++ source-code printed by the last step:

```
"""
Export NN to C++
Copy-paste the generated code inside a file named model.h or irisModel.h
in your Arduino project
"""
from everywhereml.code_generators.tensorflow import convert_model


c_header = convert_model(model, X, y, model_name='irisModel')
print(c_header)
```
Now, create a file called ```model.h``` (for example) and paste the C++ source-code on it (See [model.h](./firmware/model.h) for reference)

With this steps ok, we can now use the ```eloquent_tinyml``` to do predictions based on our model (See [firmware.ino](./firmware/firmware.ino)) 

## Compiling and Using

Now, you can use the Arduino IDE to Compile and Upload the [firmware.ino](./firmware/firmware.ino) to the ESP32 module. 

Open the Serial Monitor to see the results of the predictions 