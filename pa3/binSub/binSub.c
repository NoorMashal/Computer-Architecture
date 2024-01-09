#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>

int main(int argc, char *argv[]) 
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) 
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP
    char buff;

    // first, read the minuend (number to be subtracted from)
    bool minuend[CHAR_BIT]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=CHAR_BIT-1; 0<=i; i--) 
    { // read MSB first as that is what comes first in the file
        if (fscanf(fp, "%c", &buff) == 1) 
        {
            minuend[i] = (buff == '1');
        }
    }

    // Move to the next line to read the next input
    fscanf(fp, "\n"); 

    // notice that you are reading two different lines; caution with reading
    /* ... */

    // second, read the subtrahend (number to subtract)
    bool subtrahend[CHAR_BIT]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=CHAR_BIT-1; 0<=i; i--) 
    { // read MSB first as that is what comes first in the file
        if (fscanf(fp, "%c", &buff) == 1) 
        {
            subtrahend[i] = (buff == '1');
        }    
    }
    // switch the symbols
    for (int i=0; i<CHAR_BIT; i++) 
    {
        subtrahend[i] = !subtrahend[i];
    }

    // +1
    bool c = true; // do binary addition with carry 
    for (int i=0; i<CHAR_BIT; i++) 
    { // iterate from LSB to MSB
        bool temp = subtrahend[i];

        subtrahend[i] = temp ^ c; //operation XOR
        c = temp & c; //operation AND     
    }

    // Add the minuend and the negated subtrahend
    bool diff[CHAR_BIT];
    c = false;
    
    for (int i=0; i<CHAR_BIT; i++) 
    {
        bool subTemp = subtrahend[i];
        bool minuendTemp = minuend[i];

        diff[i] = (minuendTemp ^ subTemp) ^ c; // bitwise XOR operation
        c = (minuendTemp & subTemp) | (subTemp & c) | (c & minuendTemp); // bitwise OR operation    
    }

    // print the difference bit string
    for (int i=CHAR_BIT-1; 0<=i; i--)
        printf("%d",diff[i]);

    return EXIT_SUCCESS;
}