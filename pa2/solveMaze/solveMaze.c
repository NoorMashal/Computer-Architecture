#include "../graphutils.h" // header for functions to load and free adjacencyList
#include "../queue/queue.h" // header for queue

// A program to solve a maze that may contain cycles using BFS

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */
        FILE* fp1 = fopen(argv[2], "r");
    if (!fp1) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t source = 0;
    size_t target = 0;

    fscanf(fp1, "%ld", &source);
    fscanf(fp1, "%ld", &target);

    fclose(fp1);

    //
    AdjacencyListNode* adjacencyList = NULL;

    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST

    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }

    /* ... */
    parents[source] = source;
    // enqueue(&queue, &adjacencyList[source]);
    
    int current = source;
    while ( current != target ) 
    {
        
            AdjacencyListNode* temp = &adjacencyList[current];
            while (temp)
            {
                if(parents[temp->graphNode] == -1)
                {
                    enqueue(&queue, temp);
                    parents[temp->graphNode] = current;
                }
                temp = temp->next;
            }

    
        AdjacencyListNode* currentNode = dequeue(&queue);
        current = currentNode->graphNode;

        // so long as we haven't found the target node yet, iterate through the adjacency list

        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */

    // Visit the next node at the front of the queue of nodes to visit
        // Visit the next node at the front of the queue of nodes to visit
        /* ... */
    
    }


    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */
    graphNode_t path = target;
    while (path != source)
    {
        printf("%ld %ld\n", path, parents[path]);
        path = parents[path];
    }
    printf("%ld", source);


    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) 
    {
        dequeue(&queue);
    }
    
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}
