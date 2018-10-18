#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include "vertex.h"
#include "edge.h"

//Graph is actually a pointer that points to head of vertex list
typedef struct Graph {
    Vertex * head;
    int last_id;
} Graph;

Graph * initialize_graph(void);

int add_vertex(Graph **graph, char *name);
Vertex * search_for_vertex(Graph *graph, char *name);
void print_vertices(Graph *graph);
int delete_vertex(Graph **graph, char *name);
int print_receiving(Graph *graph, char *name);
int print_simple_circles(Graph *graph, char *name);
void DFS(struct Graph* graph, Vertex *vertex, int **visited, char **results, int initial_id);

void add_edge(Graph **graph, char *start_name, char *direction_name, int weight);
int modify_weight_in_edge(Graph *graph, char *start_name, char *direction_name, int weight, int new_weight);
Edge * search_for_edge(Graph *graph, char *start_name, char *direction_name, int weight, int *error);
void print_edges(Graph *graph, char *name);
int delete_edge(Graph *graph, char *start_name, char *direction_name, int weight);
int delete_edges(Graph *graph, char *start_name, char *direction_name);
void delete_edges_without_search(Graph *graph, Vertex **vertex, char *direction_name);

void print_to_file(Graph *graph, FILE *ofile);
void release_memory(Graph **graph);

#endif
