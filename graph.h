#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include "vertex.h"
#include "edge.h"

//Graph is actually a pointer that points to head of vertex list
typedef struct Graph {
    Vertex * head;
} Graph;

Graph * initialize_graph(void);

void add_vertex(Graph **graph, char *name);
Vertex * search_for_vertex(Graph *graph, char *name);
void print_vertices(Graph *graph);
void delete_vertex(Graph **graph, char *name);

void add_edge(Graph **graph, char *start_name, char *direction_name, int weight);
void modify_weight_in_edge(Graph *graph, char *start_name, char *direction_name, int weight, int new_weight);
Edge * search_for_edge(Graph *graph, char *start_name, char *direction_name, int weight);
void print_edges(Graph *graph, char *name);
void delete_edge(Graph *graph, char *start_name, char *direction_name, int weight);
void delete_edges(Graph *graph, char *start_name, char *direction_name);
void delete_edges_without_search(Graph *graph, Vertex **vertex, char *direction_name);

void print_to_file(Graph *graph, FILE *ofile);
void release_memory(Graph **graph);

#endif
