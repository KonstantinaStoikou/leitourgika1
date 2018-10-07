#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "edge.h"

Graph * initialize_graph(void) {
    Graph *graph = NULL;
    graph = malloc(sizeof(Graph));

    // graph->head = NULL;
    // graph->head = malloc(sizeof(Vertex));

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

void add_edge(Graph **graph, char *start_name, char *direction_name, int weight) {
    //check if given vertices exists in the graph and create them if they don't
    if (search_for_vertex(*graph, start_name) == 0) {
        add_vertex(graph, start_name);
    }
    if (search_for_vertex(*graph, direction_name) == 0) {
        add_vertex(graph, direction_name);
    }
}

//find if a vertex with the given name exists and return it else return null
Vertex * search_for_vertex(Graph *graph, char *name) {
    Vertex * current = graph->head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("found\n");
            return current;
        }
        current = current->next;
    }
    printf("not found\n");
    return NULL;
}

void print_vertices(Graph *graph) {
    Vertex * current = graph->head;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}
