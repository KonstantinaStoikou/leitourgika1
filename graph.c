#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "graph.h"

//Create a new graph with the given name for the first vertex
Vertex * create_graph(char *name) {
    Vertex *head = NULL;
    head = malloc(sizeof(Vertex));
    head->name = name;
    head->next = NULL;
    head->head_edge = NULL;
    return head;
}
