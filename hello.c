#include <stdio.h>

#define TRANSACTIONS 5
#define ITEMS 4
#define MAX_ITEMSET 16

/*
 Experiment 7.1:
 Generate frequent itemsets and association rules using Apriori.
 Items: A, B, C, D
 Transactions are represented as 1 (present) or 0 (absent).
*/

int data[TRANSACTIONS][ITEMS] = {
    {1, 1, 0, 1},  /* A, B, D */
    {1, 1, 1, 0},  /* A, B, C */
    {1, 0, 1, 1},  /* A, C, D */
    {0, 1, 1, 1},  /* B, C, D */
    {1, 1, 1, 1}   /* A, B, C, D */
};

char itemName[ITEMS] = {'A', 'B', 'C', 'D'};
double minSupport = 0.40;
double minConfidence = 0.60;

int containsItemset(int transaction, int mask) {
    int i;
    for (i = 0; i < ITEMS; i++) {
        if ((mask & (1 << i)) && data[transaction][i] == 0)
            return 0;
    }
    return 1;
}

int supportCount(int mask) {
    int t, count = 0;
    for (t = 0; t < TRANSACTIONS; t++) {
        if (containsItemset(t, mask))
            count++;
    }
    return count;
}

int itemCount(int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

void printItemset(int mask) {
    int i, first = 1;
    printf("{");
    for (i = 0; i < ITEMS; i++) {
        if (mask & (1 << i)) {
            if (!first) printf(", ");
            printf("%c", itemName[i]);
            first = 0;
        }
    }
    printf("}");
}

int main(void) {
    int mask, sub, count, size;
    int frequent[MAX_ITEMSET] = {0};

    printf("APRIORI ALGORITHM - FREQUENT ITEMSETS AND ASSOCIATION RULES\n");
    printf("Minimum support: %.0f%%\n", minSupport * 100);
    printf("Minimum confidence: %.0f%%\n\n", minConfidence * 100);

    printf("Frequent itemsets:\n");
    printf("------------------\n");

    for (size = 1; size <= ITEMS; size++) {
        for (mask = 1; mask < (1 << ITEMS); mask++) {
            if (itemCount(mask) != size)
                continue;

            count = supportCount(mask);
            if ((double)count / TRANSACTIONS >= minSupport) {
                frequent[mask] = 1;
                printItemset(mask);
                printf("  Support count = %d, Support = %.2f\n",
                       count, (double)count / TRANSACTIONS);
            }
        }
    }

    printf("\nAssociation rules:\n");
    printf("------------------\n");

    for (mask = 1; mask < (1 << ITEMS); mask++) {
        if (!frequent[mask] || itemCount(mask) < 2)
            continue;

        /* Every non-empty proper subset is a possible rule antecedent. */
        for (sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int rhs = mask ^ sub;
            int unionCount, lhsCount;
            double confidence;

            if (rhs == 0 || !frequent[sub])
                continue;

            unionCount = supportCount(mask);
            lhsCount = supportCount(sub);
            if (lhsCount == 0)
                continue;

            confidence = (double)unionCount / lhsCount;
            if (confidence >= minConfidence) {
                printItemset(sub);
                printf(" -> ");
                printItemset(rhs);
                printf("  Support = %.2f, Confidence = %.2f\n",
                       (double)unionCount / TRANSACTIONS, confidence);
            }
        }
    }

    printf("\nDone.\n");
    return 0;
}
