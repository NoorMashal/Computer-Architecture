#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../matMul/matMul.h"

unsigned int cost (
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes
) {
    if ( matrixCount==1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {

        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)

        unsigned int costs[numPossibleSplits];
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            assert ( colSizes[split] == rowSizes[split+1] );
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        unsigned int minCost = costs[0];
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) {
            if ( costs[split]<minCost ) {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

void recursive_matMul(
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes,
    int*** matrices,
    int** matChainMulProduct
) {
    if (matrixCount==1) {// Base case.
        for (unsigned int i=0; i<rowSizes[0]; i++) {     //initialize and fill the rows of the product matrix 
            for (unsigned int j =0; j<colSizes[0]; j++) {
                matChainMulProduct[i][j] = matrices[0][i][j];
            }
        }                                
        
    } else {
        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)

        unsigned int costs[numPossibleSplits];
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            assert ( colSizes[split] == rowSizes[split+1] );
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        // Now that we have the costs array for each time we need to split, we can get the index of the minimum from the costs array and store it as our split.
        unsigned int minCost = costs[0];
        int number = 0;
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) {
            if ( costs[split]<minCost ) {
                number = split;
                minCost = costs[split];
            }
        }

        int breh = number+1;
        
        int** leftSide = (int**) malloc(sizeof(int*) * rowSizes[0]);
        for (unsigned int i=0; i<rowSizes[0]; i++) {     //initialize and populate the rows of the product matrix 
            leftSide[i] = (int*) malloc(sizeof(int)*colSizes[number]);
        }
        recursive_matMul(breh, rowSizes, colSizes, matrices, leftSide);

        int** rightSide = (int**) malloc(sizeof(int*) * rowSizes[breh]); 
        for (unsigned int i=0; i<rowSizes[breh]; i++) {     //initialize and populate the rows of the product matrix 
            rightSide[i] = (int*) malloc(sizeof(int)*colSizes[matrixCount-1]);
        }
        recursive_matMul(matrixCount-breh, rowSizes+breh, colSizes+breh, matrices+breh, rightSide);

        unsigned int l = rowSizes[0]; // number of rows in Matrix a
        unsigned int m = colSizes[breh-1]; // number of cols in Matrix A and number of rows of Matrix B       
        unsigned int n = colSizes[matrixCount-1]; // number of cols in Matrix b
        
        matMul(l, m, n, leftSide, rightSide, matChainMulProduct);
        
        // Freeing memory
        
        for (unsigned int i=0; i<rowSizes[0]; i++) {
            free(leftSide[i]);
        }
        free(leftSide);
        
        for (unsigned int i=0; i<rowSizes[breh]; i++) {
            free(rightSide[i]);
        }
        free(rightSide);
    }
}

int main(int argc, char* argv[]) {
    unsigned int matrixCount;
    unsigned int* rowSizes;
    unsigned int* colSizes;
    int*** matrices;
    int** product;

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount)) {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }

    rowSizes = calloc( matrixCount, sizeof(int) );
    colSizes = calloc( matrixCount, sizeof(int) );
    matrices = calloc( matrixCount, sizeof(int**) );

    for (unsigned int matIndex=0; matIndex<matrixCount; matIndex++) {

        unsigned int rows, cols;
        if (!fscanf(fp, "%d %d\n", &rows, &cols)) {
            perror("reading the dimensions of matrix failed");
            exit(EXIT_FAILURE);
        }
        rowSizes[matIndex] = rows;
        colSizes[matIndex] = cols;

        matrices[matIndex] = calloc( rows, sizeof(int*) );
        for ( unsigned int i=0; i<rows; i++ ) {
            matrices[matIndex][i] = calloc( cols, sizeof(int) );
            for ( unsigned int k=0; k<cols; k++ ) {
                int element;
                if (!fscanf(fp, "%d ", &element)) {
                    perror("reading the element of matrix failed");
                    exit(EXIT_FAILURE);
                }
                matrices[matIndex][i][k] = element;
            }
        }
    }

    // allocate memory for the product matrix
    product = (int**) malloc(sizeof(int*)*rowSizes[0]);
    
    for (unsigned int i = 0; i < rowSizes[0]; i++) {
        product[i] = (int*) malloc(sizeof(int)*(colSizes[matrixCount-1]));
    }

    // recursively multiply the matrices
    recursive_matMul(matrixCount, rowSizes, colSizes, matrices, product);

    for (unsigned int i=0; i<rowSizes[0]; i++) {
        for (unsigned int j=0; j<colSizes[matrixCount-1]; j++) {
            printf("%d ", product[i][j]);
        }
        printf("\n");
    }

    // frees product matrix
    for (unsigned int i = 0; i < rowSizes[0]; i++) {
        free(product[i]);
    }
    free(product);

    // frees the matrices 
    for (unsigned int m = 0; m < matrixCount; m++) {
        for (unsigned int i = 0; i < rowSizes[m]; i++) {
            free(matrices[m][i]);
        }
        free(matrices[m]);
    }
    free(matrices);

    free(colSizes);
    free(rowSizes);
    fclose(fp);

    exit(EXIT_SUCCESS);
}