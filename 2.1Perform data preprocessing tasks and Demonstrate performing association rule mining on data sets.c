
#include <stdio.h>
#include <string.h>

#define N 14
#define A 5
#define V 3

char *attributes[A] = {
    "outlook", "temperature", "humidity", "windy", "play"
};

char *data[N][A] = {
    {"sunny","hot","high","FALSE","no"},
    {"sunny","hot","high","TRUE","no"},
    {"overcast","hot","high","FALSE","yes"},
    {"rainy","mild","high","FALSE","yes"},
    {"rainy","cool","normal","FALSE","yes"},
    {"rainy","cool","normal","TRUE","no"},
    {"overcast","cool","normal","TRUE","yes"},
    {"sunny","mild","high","FALSE","no"},
    {"sunny","cool","normal","FALSE","yes"},
    {"rainy","mild","normal","FALSE","yes"},
    {"sunny","mild","normal","TRUE","yes"},
    {"overcast","mild","high","TRUE","yes"},
    {"overcast","hot","normal","FALSE","yes"},
    {"rainy","mild","high","TRUE","no"}
};

double support(int a, char *x, int b, char *y) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(data[i][a], x) == 0 &&
            strcmp(data[i][b], y) == 0)
            count++;
    }
    return (double)count / N;
}

double item_support(int a, char *x) {
    int count = 0;
    for (int i = 0; i < N; i++)
        if (strcmp(data[i][a], x) == 0)
            count++;
    return (double)count / N;
}

int main(void) {
    char *values[A][V] = {
        {"sunny", "overcast", "rainy"},
        {"hot", "mild", "cool"},
        {"high", "normal", ""},
        {"FALSE", "TRUE", ""},
        {"no", "yes", ""}
    };

    int sizes[A] = {3, 3, 2, 2, 2};
    double minSupport = 0.20;
    double minConfidence = 0.70;

    printf("ASSOCIATION RULE MINING - APRIORI DEMO\n");
    printf("Dataset: Weather\n");
    printf("Minimum Support: %.2f\n", minSupport);
    printf("Minimum Confidence: %.2f\n\n", minConfidence);

    printf("Frequent itemsets of size 1:\n");
    for (int a = 0; a < A; a++) {
        for (int v = 0; v < sizes[a]; v++) {
            double s = item_support(a, values[a][v]);
            if (s >= minSupport)
                printf("%s=%s  Support=%.3f\n",
                       attributes[a], values[a][v], s);
        }
    }

    printf("\nAssociation Rules:\n");
    printf("---------------------------------------------\n");

    for (int a = 0; a < A; a++) {
        for (int b = 0; b < A; b++) {
            if (a == b) continue;

            for (int x = 0; x < sizes[a]; x++) {
                for (int y = 0; y < sizes[b]; y++) {
                    double s = support(a, values[a][x],
                                       b, values[b][y]);
                    double sa = item_support(a, values[a][x]);

                    if (s >= minSupport && sa > 0) {
                        double confidence = s / sa;
                        double sb = item_support(b, values[b][y]);
                        double lift = sb > 0 ? confidence / sb : 0;

                        if (confidence >= minConfidence) {
                            printf("%s=%s => %s=%s\n",
                                attributes[a], values[a][x],
                                attributes[b], values[b][y]);
                            printf("Support=%.3f Confidence=%.3f Lift=%.3f\n\n",
                                s, confidence, lift);
                        }
                    }
                }
            }
        }
    }

    printf("Preprocessing note:\n");
    printf("Numeric Iris and Glass attributes must be discretized\n");
    printf("into intervals before applying categorical Apriori.\n");
    printf("Resampling can be performed before mining.\n");

    return 0;
}
