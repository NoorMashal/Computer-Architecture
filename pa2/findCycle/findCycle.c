#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
/* ... */
void dfs(size_t graphNodeCount, AdjacencyListNode* adjacencyList, int nodeInput, int* cycle, int counter, bool* isCyclic, bool* found, int* cycleNodes) {
    cycle[counter] = nodeInput;
    counter++;
    AdjacencyListNode* node = &adjacencyList[nodeInput];

    while (node->next != NULL) {
        int nextNode = node->next->graphNode;
        bool visited = false;
        for (int i = 0; i < counter; i++) {
            if (cycle[i] == nextNode) {
                visited = true;
                *isCyclic = true; 
                if (!(*found)) {
                    for (int j = i; j < counter; j++) {
                        printf("%d ", cycle[j]);
                        cycleNodes[j-i] = cycle[j];
                    }
                    printf("\n");
                    *found = true;
                }
                break;
            }
        }
        if (!visited && !(*isCyclic)) { 
            dfs(graphNodeCount, adjacencyList, nextNode, cycle, counter, isCyclic, found, cycleNodes);
        }
        node = node->next;
    }
}
int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    /* ... */
    
    
    bool isCyclic = false;
    bool found = false;
    int cycleNodes[graphNodeCount];

    
    for (unsigned source = 0; source < graphNodeCount; source++) {
        int cycle[graphNodeCount];
        dfs(graphNodeCount, adjacencyList, source, cycle, 0, &isCyclic, &found, cycleNodes); 
        if (found) { // If a cycle is detected, we can stop exploring further
            break;
        }
    }
    if (!isCyclic) { printf("DAG\n"); }
    
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}