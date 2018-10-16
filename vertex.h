#ifndef VERTEX_HEADER
#define VERTEX_HEADER

typedef struct Vertex {
    int id;
    char *name;
    struct Edge *head_edge;
    struct Vertex *next;
} Vertex;

#endif
