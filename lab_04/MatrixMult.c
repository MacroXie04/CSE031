#include <stdio.h>
#include <stdlib.h>

int **matMult(int **a, int **b, int size) {
    // (4) Implement matrix multiplication
    int i, j, k;
    int **result = (int **)malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        *(result + i) = (int *)malloc(size * sizeof(int));
        for (j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
            for (k = 0; k < size; k++) {
                *(*(result + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
            }
        }
    }
    return result;
}

void printArray(int **arr, int n) {
    // (2) Implement printArray function
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int i, j;
    int n = 5;
    int **matA, **matB, **matC;
    // (1) Define 2 (n x n) arrays (matrices).
    matA = (int **) malloc(n * sizeof(int *));
    matB = (int **) malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {
        *(matA + i) = (int *) malloc(n * sizeof(int));
        *(matB + i) = (int *) malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            *(*(matA + i) + j) = i + j + 1;
            *(*(matB + i) + j) = (i == j) ? 1 : 0;
        }
    }

    // (3) Call printArray to print out the 2 arrays
    printf("Matrix A\n");
    printArray(matA, n);
    printf("Matrix B\n");
    printArray(matB, n);

    // (5) Call matMult to multiply the 2 arrays
    matC = matMult(matA, matB, n);

    // (6) Call printArray to print out resulting array
    printf("Matrix A * B\n");
    printArray(matC, n);

    // free memory
    for (i = 0; i < n; i++) {
        free(*(matA + i));
        free(*(matB + i));
        free(*(matC + i));
    }
    free(matA);
    free(matB);
    free(matC);

    return 0;
}
