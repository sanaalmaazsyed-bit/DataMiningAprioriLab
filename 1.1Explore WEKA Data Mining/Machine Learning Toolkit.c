#include <stdio.h>
#include <string.h>

void weatherDataset() {
    int yes = 9, no = 5;

    printf("\n--- WEATHER.NOMINAL DATASET ---\n");
    printf("Number of Instances: 14\n");
    printf("Number of Attributes: 5\n\n");

    printf("Attributes and Types:\n");
    printf("1. outlook     : Nominal\n");
    printf("2. temperature : Nominal\n");
    printf("3. humidity    : Nominal\n");
    printf("4. windy       : Nominal\n");
    printf("5. play        : Nominal (Class)\n");

    printf("\nClass Distribution:\n");
    printf("Play Yes: %d\n", yes);
    printf("Play No : %d\n", no);

    printf("\nARFF Format Example:\n");
    printf("@relation weather\n");
    printf("@attribute outlook {sunny,overcast,rainy}\n");
    printf("@attribute temperature {hot,mild,cool}\n");
    printf("@attribute humidity {high,normal}\n");
    printf("@attribute windy {TRUE,FALSE}\n");
    printf("@attribute play {yes,no}\n");
    printf("@data\n");
    printf("sunny,hot,high,FALSE,no\n");
}

void irisDataset() {
    printf("\n--- IRIS DATASET ---\n");
    printf("Number of Instances: 150\n");
    printf("Number of Attributes: 5\n\n");

    printf("Attributes and Types:\n");
    printf("1. sepallength : Numeric\n");
    printf("2. sepalwidth  : Numeric\n");
    printf("3. petallength : Numeric\n");
    printf("4. petalwidth  : Numeric\n");
    printf("5. class       : Nominal (Class)\n");

    printf("\nClass Distribution:\n");
    printf("Iris-setosa     : 50\n");
    printf("Iris-versicolor : 50\n");
    printf("Iris-virginica  : 50\n");

    printf("\nVisualization:\n");
    printf("Petal measurements help distinguish the three classes.\n");
}

int main() {
    int choice;

    printf("WEKA DATA MINING TOOLKIT DEMONSTRATION\n");
    printf("1. Weather Dataset\n");
    printf("2. Iris Dataset\n");
    printf("3. Display Both Datasets\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            weatherDataset();
            break;
        case 2:
            irisDataset();
            break;
        case 3:
            weatherDataset();
            irisDataset();
            break;
        default:
            printf("Invalid choice.\n");
    }

    printf("\nExperiment completed successfully.\n");
    return 0;
}
