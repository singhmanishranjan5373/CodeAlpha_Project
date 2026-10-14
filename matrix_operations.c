#include <stdio.h>

#define MAX 10

void readMatrix(int m[MAX][MAX], int r, int c, const char *name) {
    printf("Enter elements of matrix %s (%d x %d):\n", name, r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &m[i][j]);
}

void printMatrix(int m[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%5d ", m[i][j]);
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX],
                      int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
    }
}

void transposeMatrix(int a[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[j][i] = a[i][j];
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX];
    int r1, c1, r2, c2, choice;

    do {
        printf("\n--- Matrix Operations ---\n");
        printf("1. Addition\n2. Multiplication\n3. Transpose\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter rows and columns (max %d): ", MAX);
                scanf("%d %d", &r1, &c1);
                if (r1 < 1 || c1 < 1 || r1 > MAX || c1 > MAX) {
                    printf("Invalid size.\n");
                    break;
                }
                readMatrix(a, r1, c1, "A");
                readMatrix(b, r1, c1, "B");
                addMatrices(a, b, res, r1, c1);
                printf("\nA + B =\n");
                printMatrix(res, r1, c1);
                break;

            case 2:
                printf("Enter rows and columns of A (max %d): ", MAX);
                scanf("%d %d", &r1, &c1);
                printf("Enter rows and columns of B (max %d): ", MAX);
                scanf("%d %d", &r2, &c2);
                if (r1 < 1 || c1 < 1 || r2 < 1 || c2 < 1 ||
                    r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX) {
                    printf("Invalid size.\n");
                    break;
                }
                if (c1 != r2) {
                    printf("Multiplication not possible: columns of A must equal rows of B.\n");
                    break;
                }
                readMatrix(a, r1, c1, "A");
                readMatrix(b, r2, c2, "B");
                multiplyMatrices(a, b, res, r1, c1, c2);
                printf("\nA x B =\n");
                printMatrix(res, r1, c2);
                break;

            case 3:
                printf("Enter rows and columns (max %d): ", MAX);
                scanf("%d %d", &r1, &c1);
                if (r1 < 1 || c1 < 1 || r1 > MAX || c1 > MAX) {
                    printf("Invalid size.\n");
                    break;
                }
                readMatrix(a, r1, c1, "A");
                transposeMatrix(a, res, r1, c1);
                printf("\nTranspose of A =\n");
                printMatrix(res, c1, r1);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
