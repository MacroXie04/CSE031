#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);

    four_c = (char*)four_ints;

	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.

    // (3) Print four_ints[0] in hex
    printf("four_ints[0] = %x\n", four_ints[0]);

    // (4) Print four_ints[1] in hex
    printf("four_ints[1] = %x\n", four_ints[1]);

    // (5c) Print addresses of four_ints and four_c
    printf("four_ints = %p\n", (void*)four_ints);
    printf("four_c    = %p\n", (void*)four_c);

    // (6) Print addresses and values of all elements of four_ints
    printf("\nfour_ints elements:\n");
    for(i = 0; i < 4; i++)
        printf("Address: %p, Value: %x\n", (void*)&four_ints[i], four_ints[i]);

    // (8) Print addresses and values of all elements of four_c
    printf("\nfour_c elements:\n");
    for(i = 0; i < 16; i++)
        printf("Address: %p, Value: %x\n", (void*)&four_c[i], four_c[i] & 0xff);

	return 0;
}
