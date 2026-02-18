#include <stdio.h>

int main() {
    int x, y, *px, *py;
    /* prompt 1:
     * the x and y are the variable which type is int
     * *px and *py initialize as a pointer
     */


    int arr[10];
    /* prompt 2:
     * the Array initialize with no value apply
     * will be meaning less value
     */

    int arr_init[10] = {0};
    /* prompt 3:
     * initialize with some value
     */

    printf("address of x: %p\n", (void *) &x);
    printf("address of y: %p\n", (void *) &y);
    printf("\n");
    /* prompt 4:
     * print the memory address
     * &x -> get memory address
     * %p -> print the memory address
     */

    px = &x;
    py = &y;
    printf("value of px(address of x): %p\n", (void *) px);
    printf("value of py(address of y): %p\n", (void *) py);
    printf("address of x: %p\n", (void *) &x);
    printf("address of y: %p\n", (void *) &y);
    printf("\n");
    /* prompt 5:
     * get memory value of x and give it to px
     * print memory address
     */

    printf("the value of array arr_init");
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: ", i+1);
        printf("%d", *(arr_init + i));
        printf("\n");
    }

    printf("\n");

    printf("the value of array arr: ");
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: ", i+1);
        printf("%d", *(arr + i));
        printf("\n");
    }

    printf("\n");

    printf("the value of array arr: ");
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: ", i+1);
        printf("%d", arr[i]);
        printf("\n");
    }
    /* prompt 7
     * arr[i] = *(arr + i)
     */

    printf("\n");

    printf("address of arr: %p", (void*)&arr);
    /* prompt 8
     * print the memory address of arr
     */
    return 0;
}
