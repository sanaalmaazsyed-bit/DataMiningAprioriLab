#include <stdio.h>
#include <math.h>

#define N 14

void calculateEntropy() {
    float yes = 9.0 / 14.0;
    float no = 5.0 / 14.0;

    float entropy =
        -(yes * log2(yes) + no * log2(no));

    printf("\n--- WEATHER DATASET ---\n");
    printf("Instances: 14\n");
    printf("Attributes: 5\n");
    printf("Class: play\n");
    printf("Play = Yes: 9\n");
    printf("Play = No : 5\n");
    printf("Root Entropy: %.4f\n", entropy);
}

void weatherRules() {
    printf("\nJ48 IF-THEN RULES:\n");
    printf("1. IF outlook=overcast THEN play=yes\n");
    printf("2. IF outlook=sunny AND humidity=high");
    printf(" THEN play=no\n");
    printf("3. IF outlook=sunny AND humidity=normal");
    printf(" THEN play=yes\n");
    printf("4. IF outlook=rainy AND windy=TRUE");
    printf(" THEN play=no\n");
    printf("5. IF outlook=rainy AND windy=FALSE");
    printf(" THEN play=yes\n");
}

void irisInfo() {
    printf("\n--- IRIS DATASET ---\n");
    printf("Instances: 150\n");
    printf("Attributes: 5\n");
    printf("Classes: 3\n");
    printf("Iris-setosa: 50\n");
    printf("Iris-versicolor: 50\n");
    printf("Iris-virginica: 50\n");
    printf("Numeric features: Sepal length, Sepal width,");
    printf(" Petal length, Petal width\n");
}

void glassInfo() {
    printf("\n--- GLASS DATASET ---\n");
    printf("Instances: 214\n");
    printf("Attributes: 10\n");
    printf("Features: Refractive index and 8 chemical");
    printf(" composition attributes\n");
    printf("Target: Glass type\n");
}

void classifierList() {
    printf("\n--- CLASSIFIERS TO TEST IN WEKA ---\n");
    printf("1. ID3 Decision Tree\n");
    printf("2. J48 Decision Tree\n");
    printf("3. Naive Bayes\n");
    printf("4. IBk (k-NN), k=3\n");
    printf("\nEvaluation methods:\n");
    printf("- 10-fold cross-validation\n");
    printf("- Accuracy and Kappa statistic\n");
    printf("- Confusion matrix\n");
    printf("- Precision, Recall, F-measure\n");
    printf("- ROC curve and AUC\n");
}

int main() {
    int choice;

    printf("CLASSIFICATION ON DATASETS\n");
    printf("1. Weather dataset and entropy\n");
    printf("2. Iris dataset details\n");
    printf("3. Glass dataset details\n");
    printf("4. J48 classification rules\n");
    printf("5. Classifier evaluation checklist\n");
    printf("6. Display all\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            calculateEntropy();
            break;
        case 2:
            irisInfo();
            break;
        case 3:
            glassInfo();
            break;
        case 4:
            weatherRules();
            break;
        case 5:
            classifierList();
            break;
        case 6:
            calculateEntropy();
            weatherRules();
            irisInfo();
            glassInfo();
            classifierList();
            break;
        default:
            printf("Invalid choice.\n");
    }

    printf("\nProgram completed.\n");
    return 0;
}
