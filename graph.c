#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"


Graph * initialize_graph(void) {
    Graph *graph = NULL;
    graph = malloc(sizeof(Graph));

    graph->head = NULL;

    return graph;
}


//Add vertex to the start of vertex list: complexity O(1)
void add_vertex(Graph **graph, char *name) {
    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name = malloc(sizeof(name));
    strcpy(new_vertex->name, name);

    new_vertex->next = (*graph)->head;
    new_vertex->head_edge = NULL;

    // Change head pointer as new node is added at the beginning
    (*graph)->head = new_vertex;
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


void delete_edge(Graph *graph, char *start_name, char *direction_name, int weight) {
    Vertex *vertex = search_for_vertex(graph, start_name);

    //when edge to be deleted is head edge
    if(strcmp(vertex->head_edge->directed_vertex->name, direction_name) == 0 && vertex->head_edge->weight == weight) {
        //if there is only one edge make head_edge in vertex point to null and free edge
        if(vertex->head_edge->next == NULL) {
            Edge *edge = vertex->head_edge;
            vertex->head_edge = NULL;
            free(edge);
            return;
        }

        Edge *edge = vertex->head_edge;
        vertex->head_edge = vertex->head_edge->next;
        // Free memory
        free(edge);

        return;
    }

    //when not first node, follow the normal deletion process:
    //find the previous node
    Edge *prev = vertex->head_edge;
    while(prev->next != NULL && strcmp(prev->next->directed_vertex->name, direction_name) != 0) {
        prev = prev->next;
    }

    Edge *edge = prev->next;        //the edge to be deleted
    printf("edge is %s\n", edge->directed_vertex->name);
    printf("previous is %s\n", prev->directed_vertex->name);

    //check if edge really exists in adjacency list (prev->next = given edge)
    //and if it has the weight given
    if(prev->next == NULL || prev->next->weight != weight) {
        printf("Given edge could not be found\n");
        return;
    }

    //remove edge from adjacency list and make previous edge point to the next one of the deleted
    prev->next = edge->next;
    // Free memory
    free(edge);
}


//Delete all edges between given vertices
void delete_edges(Graph *graph, char *start_name, char *direction_name) {

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

void modify_weight_in_edge(Graph *graph, char *start_name, char *direction_name, int weight, int new_weight) {
    Edge *edge = search_for_edge(graph, start_name, direction_name, weight);
    if (edge ==NULL) {
        printf("Given edge could not be found\n");
        return;
    }

    edge->weight = new_weight;
}


//Find if an edge with the given weight exists in the adjacency list of the
//given vertex and return it else return null
//if multiple edges exists with the same weight and vertices return the first one found
Edge * search_for_edge(Graph *graph, char *start_name, char *direction_name, int weight) {
    Vertex *starting_vertex = search_for_vertex(graph, start_name);
    if (starting_vertex == NULL) {
        return NULL;
    }

    Edge *current = starting_vertex->head_edge;

    while (current != NULL) {
        if (strcmp(current->directed_vertex->name, direction_name) == 0) {
            if (current->weight == weight) {
                return current;
            }
        }
        current = current->next;
    }
    return NULL;
}


void print_edges(Graph *graph, char *name) {
    Vertex *vertex = search_for_vertex(graph, name);
    Edge *current = vertex->head_edge;

    while (current != NULL) {
        printf("%s %d\n", current->directed_vertex->name, current->weight);
        current = current->next;
    }
}






void print_to_file(Graph *graph, FILE *ofile) {
    Vertex *cur_vertex = graph->head;

    while (cur_vertex != NULL) {
        fprintf(ofile, "|%s|\n", cur_vertex->name);

        Edge *cur_edge = cur_vertex->head_edge;
        while (cur_edge != NULL) {
            fprintf(ofile, "\t-%d -> |%s|\n", cur_edge->weight, cur_edge->directed_vertex->name);
            cur_edge= cur_edge->next;
        }

        cur_vertex = cur_vertex->next;
    }


}
