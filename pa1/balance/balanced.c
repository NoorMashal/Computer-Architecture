#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct element
{
    char number;
    struct element* next;
};

// Append the new element to the start of the stack (called root)
// show what happens on the stack and on the heap
struct element* push (
    struct element* paramRoot,
    char number
) {
    struct element* newElement = malloc ( sizeof ( struct element ) );
    // (*newElement).number = number;
    newElement->number = number;
    newElement->next = paramRoot;
    return newElement;
}

// Remove element from the top of the stack
char pop (
    struct element** paramRoot
) 
{
    if ( (*paramRoot) != NULL ) 
    {
        struct element* temp = *paramRoot;
        char number = temp->number;
        *paramRoot = temp->next;
        free ( temp );
        return number;
    } 
    else 
    {
        return '\0';
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;

    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {

        switch(buff) {
            case '<' :
                root = push(root,'>');
            break;
                /* ... */
            case '(' :
                root = push(root, ')');
            break;
                /* ... */
            case '[' :
                root = push(root, ']');
            break;
                /* ... */
            case '{' :
                root = push(root, '}');
            break;
                /* ... */
            case '>' :
                if(pop(&root) != '>') balanced = false;
                break;
                /* ... */
            case ')' :
                if(pop(&root) != ')') balanced = false;
                break;
                /* ... */
            case ']' :
                if(pop(&root) != ']') balanced = false;
                break;
                /* ... */
            case '}' :
                if(pop(&root) != '}') balanced = false;
                break;
                /* ... */
            default :
                printf("Invalid character\n" );
        }
    }

    /* ... */
    if (root != NULL)
    balanced = false;
    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
