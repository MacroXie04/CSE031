#include <stdio.h>

int main()
{
    int repetition_count;
    int typo_line;
    int i;

    printf("Enter the repetition count for the punishment phrase: ");
    scanf("%d", &repetition_count);

    while (repetition_count <= 0) {
        printf("You entered an invalid value for the repetition count! Please re-enter: ");
        scanf("%d", &repetition_count);
    }

    printf("Enter the line where you want to insert the typo: ");
    scanf("%d", &typo_line);

    while (typo_line <= 0 || typo_line > repetition_count) {
        printf("You entered an invalid value for the typo placement! Please re-enter: ");
        scanf("%d", &typo_line);
    }

    for (i = 1; i <= repetition_count; i++) {
        if (i == typo_line) {
            printf("Cading wiht is C avesone!\n");
        } else {
            printf("Coding with C is awesome!\n");
        }
    }

    return 0;
}
