#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "edge.h"

Graph * initialize_graph(void) {
    Graph *graph = NULL;
    graph = malloc(sizeof(Graph));

    Vertex *head = NULL;
    head = malloc(sizeof(Vertex));

    return graph;
}

void add_vertex(Graph **graph, char *name) {
    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name  = name;
    new_vertex->next = (*graph)->head;
    new_vertex->head_edge = NULL;
    new_vertex->head_edge = malloc(sizeof(Edge));

    // Change head pointer as new node is added at the beginning
    (*graph)->head = new_vertex;
}

void add_edge(Graph **graph, Vertex *start, Vertex *direction, int weight) {

}

bool search_for_vertex(Graph *graph, char *name) {
    Vertex * current = graph->head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void print_vertices(Graph *graph) {
    Vertex * current = graph->head;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}
