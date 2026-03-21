#include <stdio.h>
#include <stdlib.h>

void printArray(int**, int);

int main() {
	int i = 0, j = 0, n = 5;
	int **arr = (int**)malloc(n * sizeof(int*));

	// (3) Allocate and initialize the 2-D array with all 0s
	for (i = 0; i < n; i++) {
		*(arr + i) = (int*)malloc(n * sizeof(int));
		for (j = 0; j < n; j++) {
			*(*(arr + i) + j) = 0;
		}
	}

    // This will print out your array
	printArray(arr, n);

    // (6) Make arr a diagonal matrix
    for (i = 0; i < n; i++) {
        *(*(arr + i) + i) = i + 1;
    }

	// (7) Call printArray to print array
    printArray(arr, n);

	return 0;
}

void printArray(int ** array, int size) {
    // (5) Implement printArray
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d ", *(*(array + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}
