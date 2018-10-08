#ifndef EDGE_HEADER
#define EDGE_HEADER

typedef struct Edge {
    int weight;
    struct Vertex *directed_vertex;
    struct Edge *next;
} Edge;

#endif
