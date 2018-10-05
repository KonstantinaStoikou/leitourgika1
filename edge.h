#ifndef EDGE_HEADER
#define EDGE_HEADER

#include "vertex.h"

//check if i need this include here and in vertex.h

typedef struct Edge {
    int weight;
    Vertex *directed_vertex;
    Vertex *start; //see if i need this
} Edge;

#endif
