#ifndef VERTEX_HEADER
#define VERTEX_HEADER

typedef struct Vertex {
    char *name;
    struct Edge *head_edge;
    struct Vertex *next;
} Vertex;

Vertex * initialize_list(char *name);
void add_vertex(Vertex **head_ref, char *name);

#endif
