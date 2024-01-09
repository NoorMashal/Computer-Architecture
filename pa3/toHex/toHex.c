#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);
    // print hexs; you will see this kind of for loop often in this assignment
    for ( int hex=3; hex>=0 ; hex--) {
        size_t hex_val = (0xF) & input>>4*hex; // shift and mask
        // char character = hex_val ? '1' : '0';
        if (hex_val > 9)
        {
            char character_val = hex_val + 55;
            printf("%c", character_val);
            continue;
        }
        printf("%ld",hex_val);
        
    }
    printf("\n");

    return EXIT_SUCCESS;

}