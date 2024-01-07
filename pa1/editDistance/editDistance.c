#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min ( size_t x, size_t y ) {
    return x<y ? x : y;
}
size_t levenshtein_iteratively ( char* source, char* target ) 
{
    int matrix[strlen(source)+1][strlen(target)+1];
    for ( int i = 0; i <= strlen(source); i++)
    {
        for ( int j = 0; j <= strlen(target); j++)
        {
            if (i==0) 
            {
                matrix[i][j] = j;
            }
            else if (j==0) 
            {
                matrix[i][j] = i;
            }
            else if (source[i-1]==target[j-1]) 
            {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else 
            {
                int ins =  matrix[i][j-1];
                int del =  matrix[i-1][j];
                int sub =  matrix[i-1][j-1];
                matrix[i][j] = 1 + min( min(ins,del), sub );
            }
        }
    }
    return matrix[strlen(source)][strlen(target)];
    for (int i = 0; i < strlen(target); i++)
    {
        free(matrix[i]);
    }

    free(matrix);

}
int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf (inputFile, "%s\n%s", source, target);

    printf("%ld\n", levenshtein_iteratively ( source, target ));

    return EXIT_SUCCESS;

}
