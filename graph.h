#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <stdbool.h>
#include "vertex.h"

//Graph is actually a pointer that points to head of vertex list
typedef struct Graph {
    Vertex * head;
} Graph;

Graph * initialize_graph(void);
void add_vertex(Graph **graph, char *name);
Vertex * search_for_vertex(Graph *graph, char *name);
void print_vertices(Graph *graph);
void add_edge(Graph **graph, char *start_name, char *direction_name, int weight);
Edge * search_for_edge(Graph *graph, char *name, int weight);    //kai directed_vertex
void print_edges(Graph *graph, char *name);
//delete vertex(graph, vertex name)
//delete edge(graph, vertex name, directed vertex name, weight)
//modify weight (graph, vertex name, directed vertex name, weight)

#endif
