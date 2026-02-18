#include <stdio.h>

/*
 * Read a set of values from the user.
 * Store the sum in the sum variable and return the number of values read.
 */

/* 
 * You CANNOT declare any global variables.
 * DO NOT change the definition of the read_values function when it comes to 
 * adding/removing function parameters, or changing its return type. You may, 
 * however, modify the single function parameter and the body of the function if 
 * you wish. 

 * Use GDB or LLDB to discover and fix errors.
 */


/*
 * Process 33281 launched: '/Users/hongzhe/Code/CSE031/lab_02/average' (arm64)
 * Enter input values (enter 0 to finish):
 * 8
 * 9
 * Process 33281 stopped
 * * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x8)
 * frame #0: 0x0000000187aa1fc8 libsystem_c.dylib`__svfscanf_l + 5584
 * libsystem_c.dylib`__svfscanf_l:
 * ->  0x187aa1fc8 <+5584>: str    w24, [x25]
 * 0x187aa1fcc <+5588>: b      0x187aa2378    ; <+6528>
 * 0x187aa1fd0 <+5592>: ldr    x8, [x21, #0x20]
 * 0x187aa1fd4 <+5596>: cbz    x8, 0x187aa201c ; <+5668>
 * Target 0: (average) stopped.
 * (lldb)
 */


//
int read_values(double *sum) {
    int values = 0, input = 0;
    *sum = 0;
    printf("Enter input values (enter 0 to finish):\n");
    scanf("%d", &input);
    while (input != 0) {
        values++;
        *sum += input;
        scanf("%d", &input);
        /* the scanf messing a &
         * scanf direct going to the memory
         */
    }
    return values;
}

int main() {
    double sum = 0;
    int values;
    values = read_values(&sum);
    printf("\nAverage: %g\n", sum / values); // Hint: How do we ensure that sum is updated here
    // AFTER read_values() manipulates it?
    // Make sure to use GDB or LLDB for this.
    return 0;
}
