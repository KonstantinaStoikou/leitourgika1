#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "edge.h"


Graph * initialize_graph(void) {
    Graph *graph = NULL;
    graph = malloc(sizeof(Graph));

    graph->head = NULL;
    // graph->head = malloc(sizeof(Vertex));

    return graph;
}


//Add vertex to the start of vertex list: complexity O(1)
void add_vertex(Graph **graph, char *name) {
    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name  = name;
    new_vertex->next = (*graph)->head;
    new_vertex->head_edge = NULL;
    // new_vertex->head_edge = malloc(sizeof(Edge));

    // Change head pointer as new node is added at the beginning
    (*graph)->head = new_vertex;
}


//Add edge to the adjecency list of the vertex given (start_name)
void add_edge(Graph **graph, char *start_name, char *direction_name, int weight) {
    //check if given vertices exists in the graph and create them if they don't
    Vertex *starting_vertex = search_for_vertex(*graph, start_name);
    if (starting_vertex == NULL) {
        add_vertex(graph, start_name);
        starting_vertex = (*graph)->head;
    }
    Vertex *directed_vertex = search_for_vertex(*graph, direction_name);
    if (directed_vertex == NULL) {
        add_vertex(graph, direction_name);
        directed_vertex = (*graph)->head;
    }

    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->weight = weight;
    new_edge->directed_vertex = directed_vertex;
    new_edge->next = starting_vertex->head_edge;
    starting_vertex->head_edge = new_edge;
}


//Find if a vertex with the given name exists and return it else return null
Vertex * search_for_vertex(Graph *graph, char *name) {
    //if graph is empty return null
    if (graph->head == NULL) {
        return NULL;
    }

    Vertex *current = graph->head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void print_vertices(Graph *graph) {
    Vertex *current = graph->head;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}


void print_edges(Graph *graph, char *name) {
    Vertex *vertex = search_for_vertex(graph, name);
    Edge *current = vertex->head_edge;

    while (current != NULL) {
        printf("%s %d\n", current->directed_vertex->name, current->weight);
        current = current->next;
    }
}
