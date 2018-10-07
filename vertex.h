#ifndef VERTEX_HEADER
#define VERTEX_HEADER

typedef struct Vertex {
    char *name;
    struct Edge *head_edge;
    struct Vertex *next;
} Vertex;

#endif
