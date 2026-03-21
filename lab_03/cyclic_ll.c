#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} node;

int has_cycle(node *head) {
    // Empty list or single node without cycle
    if (head == NULL)
        return 0;

    // 1. Start with two pointers at the head
    node *slow = head;
    node *fast = head;

    // 2. On each iteration, move slow by 1 and fast by 2
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; // move 1 step
        fast = fast->next->next; // move 2 steps

        // 3a. fast caught up to slow
        if (fast == slow)
            return 1;

        // 3b. fast's next node is slow
        if (fast != NULL && fast->next == slow)
            return 1;
    }

    // fast hit NULL, so there's an end → no cycle
    return 0;
}

void test_has_cycle(void) {
    int i;
    node nodes[25]; //enough to run our tests
    for (i = 0; i < sizeof(nodes) / sizeof(node); i++) {
        nodes[i].next = 0;
        nodes[i].value = 0;
    }
    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[3];
    printf("Checking first list for cycles. There should be none, has_cycle says it has %s cycle\n",
           has_cycle(&nodes[0]) ? "a" : "no");

    nodes[4].next = &nodes[5];
    nodes[5].next = &nodes[6];
    nodes[6].next = &nodes[7];
    nodes[7].next = &nodes[8];
    nodes[8].next = &nodes[9];
    nodes[9].next = &nodes[10];
    nodes[10].next = &nodes[4];
    printf("Checking second list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
           has_cycle(&nodes[4]) ? "a" : "no");

    nodes[11].next = &nodes[12];
    nodes[12].next = &nodes[13];
    nodes[13].next = &nodes[14];
    nodes[14].next = &nodes[15];
    nodes[15].next = &nodes[16];
    nodes[16].next = &nodes[17];
    nodes[17].next = &nodes[14];
    printf("Checking third list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
           has_cycle(&nodes[11]) ? "a" : "no");

    nodes[18].next = &nodes[18];
    printf("Checking fourth list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
           has_cycle(&nodes[18]) ? "a" : "no");

    nodes[19].next = &nodes[20];
    nodes[20].next = &nodes[21];
    nodes[21].next = &nodes[22];
    nodes[22].next = &nodes[23];
    printf("Checking fifth list for cycles. There should be none, has_cycle says it has %s cycle\n",
           has_cycle(&nodes[19]) ? "a" : "no");

    printf("Checking length-zero list for cycles. There should be none, has_cycle says it has %s cycle\n",
           has_cycle(NULL) ? "a" : "no");
}

int main(void) {
    test_has_cycle();
    return 0;
}
