#include <stdio.h>
#include <stdlib.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {
    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;

    printf("Value of head:              %p\n", (void *) head);
    printf("Address of head itself:     %p\n", (void *) &head);
    printf("Address of head->iValue:    %p, value: %d\n", (void *) &(head->iValue), head->iValue);
    printf("Address of head->fValue:    %p, value: %.2f\n", (void *) &(head->fValue), head->fValue);
    printf("Address of head->next:      %p, value: %p\n", (void *) &(head->next), (void *) head->next);
    printf("Size of struct Node:        %lu bytes\n", sizeof(struct Node));

    free(head);

    return 0;
}
