#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int charMatch(char a, char b);
int dfs(char** arr, char* word, int pos, int wordLen, int row, int col, int** path);

// Main function, DO NOT MODIFY
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);

    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);

    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);

    return 0;
}

// Case insensitive character comparison (no library functions)
int charMatch(char a, char b) {
    if (a >= 'A' && a <= 'Z') a = a + 32;
    if (b >= 'A' && b <= 'Z') b = b + 32;
    return a == b;
}

// DFS backtracking search for word starting at (row, col) at position pos
int dfs(char** arr, char* word, int pos, int wordLen, int row, int col, int** path) {
    if (pos == wordLen) return 1;
    if (row < 0 || row >= bSize || col < 0 || col >= bSize) return 0;
    if (!charMatch(*(*(arr + row) + col), *(word + pos))) return 0;

    // Calculate multiplier to append step number
    int step = pos + 1;
    int mult = 1;
    int temp = step;
    while (temp > 0) {
        mult *= 10;
        temp /= 10;
    }

    // Mark this cell with the step number
    *(*(path + row) + col) = *(*(path + row) + col) * mult + step;

    // Try all 8 adjacent directions
    int dr, dc;
    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            if (dfs(arr, word, pos + 1, wordLen, row + dr, col + dc, path))
                return 1;
        }
    }

    // Backtrack: remove step from this cell
    *(*(path + row) + col) = (*(*(path + row) + col) - step) / mult;
    return 0;
}

void printPuzzle(char** arr) {
    int i, j;
    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            if (j > 0) printf(" ");
            printf("%c", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, char* word) {
    int wordLen = strlen(word);
    int i, j;

    // Allocate path grid initialized to 0
    int** path = (int**)malloc(bSize * sizeof(int*));
    for (i = 0; i < bSize; i++) {
        *(path + i) = (int*)malloc(bSize * sizeof(int));
        for (j = 0; j < bSize; j++) {
            *(*(path + i) + j) = 0;
        }
    }

    // Search from every cell (bonus: finds all paths from different starting positions)
    int found = 0;
    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            if (dfs(arr, word, 0, wordLen, i, j, path)) {
                found = 1;
            }
        }
    }

    if (found) {
        printf("\nWord found!\n");
        printf("Printing the search path:\n");
        for (i = 0; i < bSize; i++) {
            for (j = 0; j < bSize; j++) {
                printf("%d\t", *(*(path + i) + j));
            }
            printf("\n");
        }
    } else {
        printf("\nWord not found!\n");
    }

    // Free path grid
    for (i = 0; i < bSize; i++) {
        free(*(path + i));
    }
    free(path);
}