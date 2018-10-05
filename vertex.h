#ifndef VERTEX_HEADER
#define VERTEX_HEADER

#include "edge.h"

typedef struct Vertex {
    char *name;
    Vertex *next; //i struct node* next
    //kai mia metavliti gia na sindeei me tin lista ton edges
} Vertex;

void add_vertex(char *name);

#endif
