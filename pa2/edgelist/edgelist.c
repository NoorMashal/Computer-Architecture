#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    size_t numNodes = adjMatrixToList(argv[1], &adjacencyList);
    printf("%ld\n", numNodes);

    for(int i = 0; i < numNodes; i++)
    {
        AdjacencyListNode* temp = adjacencyList[i].next;
        while (temp)
        {
            printf("%d %ld\n", i, temp->graphNode);
            temp = temp->next;
        }
    }

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h

    // NOW, BE SURE TO FREE THE ADJACENCY LIST

freeAdjList(numNodes,adjacencyList);
    return EXIT_SUCCESS;
}
