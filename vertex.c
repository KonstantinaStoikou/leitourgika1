#include <stdlib.h>
#include "vertex.h"
#include "edge.h"

//mporei na min to xreiazomai
Vertex * initialize_list(char *name) {
    Vertex *head = NULL;
    head = malloc(sizeof(Vertex));
    head->name = name;
    head->next = NULL;
    head->head_edge = NULL;
    return head;
}

/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
//add at beginning of list, complexity: O(1)
void add_vertex(Vertex** head, char *name)
{
    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name  = name;
    new_vertex->next = *head;
    new_vertex->head_edge = NULL;
    new_vertex->head_edge = malloc(sizeof(Edge));

    // Change head pointer as new node is added at the beginning
    *head = new_vertex;
}
