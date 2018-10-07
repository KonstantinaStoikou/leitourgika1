#ifndef EDGE_HEADER
#define EDGE_HEADER

#include "vertex.h"

//check if i need this include here and in vertex.h

typedef struct Edge {
    int weight;
    struct Vertex *directed_vertex;
    struct Edge *next;
} Edge;

#endif
