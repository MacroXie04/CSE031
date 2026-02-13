#include <stdio.h>

int main() {
    // Q3: Initialize variables to prevent unexpected values
    int x = 0, y = 0, *px, *py;
    int arr[10];
    int i;

    // Q3: Initialize array contents
    for (i = 0; i < 10; i++) {
        arr[i] = 0;
    }

    // Q2: Print values of x, y, and arr[0]
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("arr[0] = %d\n", arr[0]);

    // Q4: Print addresses of x and y
    printf("Address of x: %p\n", (void *)&x);
    printf("Address of y: %p\n", (void *)&y);

    // Q5: px points to x, py points to y
    px = &x;
    py = &y;
    printf("Value of px: %p\n", (void *)px);
    printf("Address of px: %p\n", (void *)&px);
    printf("Value of py: %p\n", (void *)py);
    printf("Address of py: %p\n", (void *)&py);

    // Q6: Output contents of arr using arr as a pointer (no [] notation)
    printf("Contents of arr: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // Q7: Verify arr points to address of arr[0]
    printf("arr = %p\n", (void *)arr);
    printf("&arr[0] = %p\n", (void *)&arr[0]);

    // Q8: Print address of arr
    printf("&arr = %p\n", (void *)&arr);

    return 0;
}
