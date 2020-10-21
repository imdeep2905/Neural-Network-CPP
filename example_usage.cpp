#include "nn.hpp"
#include <iostream>
#include <cassert>

/**
 * Function to test neural network
 * @returns none
 */
static void test() {
    // Creating network with 3 layers for "iris.csv"
    machine_learning::neural_network::NeuralNetwork myNN =
        machine_learning::neural_network::NeuralNetwork({
            {4, "none"},  // First layer with 3 neurons and "none" as activation
            {6,
             "relu"},  // Second layer with 6 neurons and "relu" as activation
            {3, "sigmoid"}  // Third layer with 3 neurons and "sigmoid" as
                            // activation
        });
    // Printing summary of model
    myNN.summary();
    // Training Model
    myNN.fit_from_csv("iris.csv", true, 100, 0.3, false, 2, 32, true);
    // Testing predictions of model
    assert(machine_learning::argmax(
               myNN.single_predict({{5, 3.4, 1.6, 0.4}})) == 0);
    assert(machine_learning::argmax(
               myNN.single_predict({{6.4, 2.9, 4.3, 1.3}})) == 1);
    assert(machine_learning::argmax(
               myNN.single_predict({{6.2, 3.4, 5.4, 2.3}})) == 2);
    return;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing
    test();
    return 0;
}
