#include <stdio.h>
#include <stdlib.h>

int main() {
    int num;
    int *ptr;
    int **handle;

    num = 14;
    ptr = (int *) malloc(2 * sizeof(int));
    *ptr = num;
    handle = (int **) malloc(1 * sizeof(int *));
    *handle = ptr;

    printf("Stack variables\n");
    printf("Address of num:    %p, value: %d\n", (void*)&num, num);
    printf("Address of ptr:    %p, value: %p\n", (void*)&ptr, (void*)ptr);
    printf("Address of handle: %p, value: %p\n", (void*)&handle, (void*)handle);

    printf("\nHeap memory\n");
    printf("ptr points to:     %p, value there: %d\n", (void*)ptr, *ptr);
    printf("handle points to:  %p, value there: %p\n", (void*)handle, (void*)*handle);
    printf("*handle points to: %p, value there: %d\n", (void*)*handle, **handle);

    free(ptr);
    free(handle);

    return 0;
}
