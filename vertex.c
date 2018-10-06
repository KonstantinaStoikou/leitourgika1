#include <stdlib.h>
#include "vertex.h"

/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
//add at beginning of list, complexity: O(1)
void add_vertex(Vertex** head_ref, char *name)
{
    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name  = name;
    new_vertex->next = (*head_ref);
    new_vertex->head_edge = NULL;

    // Change head pointer as new node is added at the beginning
    (*head_ref) = new_vertex;
}
