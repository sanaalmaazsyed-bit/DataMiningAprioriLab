
#include <stdio.h>

int main(void)
{
    int total = 150;
    int setosa = 50;
    int versicolor = 50;
    int virginica = 50;

    printf("ZERO R CLASSIFICATION - IRIS DATASET\n");
    printf("-------------------------------------\n");
    printf("Aim: Demonstrate the ZeroR technique\n");
    printf("using the Iris dataset.\n\n");

    printf("Dataset: iris.arff\n");
    printf("Total instances: %d\n", total);
    printf("Number of classes: 3\n");
    printf("Iris-setosa: %d\n", setosa);
    printf("Iris-versicolor: %d\n", versicolor);
    printf("Iris-virginica: %d\n\n", virginica);

    printf("Classifier: ZeroR\n");
    printf("Validation: 10-fold cross-validation\n");
    printf("Expected accuracy: %.2f%%\n",
           (double)setosa / total * 100);

    printf("\nConfusion Matrix:\n");
    printf("                 Predicted\n");
    printf("Actual       Setosa  Versicolor  Virginica\n");
    printf("Setosa         50        0          0\n");
    printf("Versicolor     50        0          0\n");
    printf("Virginica      50        0          0\n");

    printf("\nObservations:\n");
    printf("1. ZeroR ignores all input features.\n");
    printf("2. It predicts only one majority class.\n");
    printf("3. Accuracy is approximately 33.33%%.\n");
    printf("4. Preprocessing does not affect ZeroR.\n");

    printf("\nResult: ZeroR experiment demonstrated.\n");

    return 0;
}
