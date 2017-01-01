#include "../src/std_includes.h"
#include "../src/matrix.h"
#include "../src/functions.h"
#include "../src/layer.h"
#include "../src/network.h"
#include "../src/optimizer.h"

int main(){
    // test on XOR (0 1 ordering)
    int i, j;
    double** data = (double**)malloc(sizeof(double*) * 100);
    for (i = 0; i < 100; i++){
        data[i] = (double*)malloc(sizeof(double) * 2);
        data[i][0] = i % 2;
        data[i][1] = (i * 3) % 2;
    }
    Matrix* trainingData = createMatrix(100, 2, data);
    double** classes = (double**)malloc(sizeof(double*) * 100);
    for (i = 0; i < 100; i++){
        classes[i] = (double*)malloc(sizeof(double) * 2);
        classes[i][0] = (data[i][0] == 0 || data[i][1] == 0) || (data[i][0] == 1 && data[i][1] == 1) ? 1 : 0;
        classes[i][1] = classes[i][0] == 1 ? 0 : 1;
    }
    Matrix* trainingClasses = createMatrix(100, 2, classes);

    int hiddenSize[] = {3, 5};
    void (*hiddenActivations[])(Matrix*) = {sigmoid, relu};
    Network* network = createNetwork(2, 1, hiddenSize, hiddenActivations, 2, softmax);

    batchGradientDescent(network, trainingData, trainingClasses, .1, 1000, 1);
    
    destroyMatrix(trainingData);
    destroyMatrix(trainingClasses);
    destroyNetwork(network);

    return 0;
}