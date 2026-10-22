
#include <stdio.h>
#include <math.h>

#define N 10
#define D 2
#define MAXK 5

double data[N][D] = {
    {1,1}, {1.5,2}, {2,1.5}, {2.5,2},
    {8,8}, {8.5,9}, {9,8}, {9.5,9},
    {4,4}, {4.5,4.5}
};

double dist(double a[], double b[]) {
    return (a[0]-b[0])*(a[0]-b[0]) +
           (a[1]-b[1])*(a[1]-b[1]);
}

void kmeans(int k) {
    double c[MAXK][D];
    int group[N], count[MAXK];

    for (int j = 0; j < k; j++)
        for (int d = 0; d < D; d++)
            c[j][d] = data[j][d];

    for (int iter = 0; iter < 100; iter++) {
        for (int i = 0; i < N; i++) {
            int best = 0;
            double minimum = dist(data[i], c[0]);

            for (int j = 1; j < k; j++) {
                double x = dist(data[i], c[j]);
                if (x < minimum) {
                    minimum = x;
                    best = j;
                }
            }
            group[i] = best;
        }

        double sum[MAXK][D] = {0};

        for (int j = 0; j < k; j++)
            count[j] = 0;

        for (int i = 0; i < N; i++) {
            int g = group[i];
            count[g]++;
            for (int d = 0; d < D; d++)
                sum[g][d] += data[i][d];
        }

        for (int j = 0; j < k; j++)
            if (count[j] > 0)
                for (int d = 0; d < D; d++)
                    c[j][d] = sum[j][d] / count[j];
    }

    double sse = 0;

    for (int i = 0; i < N; i++)
        sse += dist(data[i], c[group[i]]);

    printf("\nK = %d\n", k);
    printf("SSE = %.3f\n", sse);

    for (int j = 0; j < k; j++)
        printf("Cluster %d centroid: %.2f, %.2f\n",
               j + 1, c[j][0], c[j][1]);

    printf("Cluster assignments:\n");
    for (int i = 0; i < N; i++)
        printf("Point %d -> Cluster %d\n", i + 1,
               group[i] + 1);
}

int main() {
    int choice;

    printf("DATASET CLUSTERING USING K-MEANS\n");
    printf("1. K = 2\n");
    printf("2. K = 3\n");
    printf("3. K = 4\n");
    printf("4. K = 5\n");
    printf("5. Run all values\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
        return 1;

    if (choice >= 1 && choice <= 4)
        kmeans(choice + 1);
    else if (choice == 5)
        for (int k = 2; k <= 5; k++)
            kmeans(k);
    else
        printf("Invalid choice\n");

    printf("\nClustering completed.\n");
    printf("Use WEKA for Iris, Glass, EM, DBSCAN,\n");
    printf("Apriori, J48, ROC and Knowledge Flow.\n");

    return 0;
}
