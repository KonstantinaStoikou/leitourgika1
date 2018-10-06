#ifndef VERTEX_HEADER
#define VERTEX_HEADER

#include "edge.h"

typedef struct Vertex {
    char *name;
    struct Vertex *next; //i struct node* next
    struct Edge *head_edge;
} Vertex;

Vertex * initialize_list(char *name);
void add_vertex(Vertex **head_ref, char *name);

#endif
