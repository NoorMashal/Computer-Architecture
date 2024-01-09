#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) 
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) 
    { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        if (buff == '0')
        {
            binary += 0;
        }
        else
        {
            binary += 1 << i;
        }
    }


    /* ... */
    bool sign = (0b001) & binary >> 31; // IF NEGATIVE (TRUE) ELSE POSTIVE (FALSE)

    // E
    /* ... */
    int e = ((binary >> FRAC_SZ) & ((1 << EXP_SZ) - 1)) - ((1 << (EXP_SZ - 1)) - 1);

    // M
    /* ... */
    int mask = (1 << FRAC_SZ) - 1;
    int man = mask & binary;
    man += 1 << FRAC_SZ;
    double m = (double)man / (double)(1 << FRAC_SZ);
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
