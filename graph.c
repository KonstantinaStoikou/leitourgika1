#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"


//Allocate memory for graph struct
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

    new_vertex->name = malloc(strlen(name)+1);
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


//Print all vertices
void print_vertices(Graph *graph) {
    Vertex *current = graph->head;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}


//Delete given vertex and all edges starting from and directed to this vertex
void delete_vertex(Graph **graph, char *name) {
    Vertex *vertex = search_for_vertex(*graph, name);

    //firstly delete all edges directed to given vertex
    Vertex *cur_vertex = (*graph)->head;

    while (cur_vertex != NULL) {
        delete_edges_without_search(*graph, &cur_vertex, name);
        cur_vertex = cur_vertex->next;
    }

    //then delete all edges starting from given vertex
    Edge *cur_edge = vertex->head_edge;
    Edge *next_edge;
    while (cur_edge != NULL) {
        next_edge = cur_edge->next;
        free(cur_edge);
        cur_edge = next_edge;
    }

    vertex->head_edge = NULL;

    //finally delete the vertex
    //when vertex to be deleted is the head vertex
    if(strcmp((*graph)->head->name, name) == 0) {
        //if there is only one vertex in the graph make graph head point to null and free vertex
        if((*graph)->head->next == NULL) {
            Vertex *v = (*graph)->head;
            (*graph)->head = NULL;
            free(v->name);
            free(v);
            return;
        }

        Vertex *v = (*graph)->head;
        (*graph)->head = v->next;
        free(v->name);
        free(v);

        return;
    }

    //when not head vertex, follow the normal deletion process:
    //find the previous node
    Vertex *prev = (*graph)->head;
    while(prev->next != NULL) {
        if (strcmp(prev->next->name, name) == 0) {
            break;
        }
        prev = prev->next;
    }

    Vertex *v = prev->next;        //the vertex to be deleted
    //check if vertex really exists in graph (because prev pointer might have reached end of list)
    if(prev->next == NULL) {
        printf("Given vertex could not be found\n");
        return;
    }

    //remove vertex from graph and make previous vertex point to the next one of the deleted
    prev->next = v->next;
    free(v->name);
    free(v);

}


//Delete edge between one given vertex towards another given vertex with certain weight
void delete_edge(Graph *graph, char *start_name, char *direction_name, int weight) {
    Vertex *vertex = search_for_vertex(graph, start_name);

    //when edge to be deleted is head edge
    if(strcmp(vertex->head_edge->directed_vertex->name, direction_name) == 0 && vertex->head_edge->weight == weight) {
        //if there is only one edge in the list make head_edge in vertex point to null and free edge
        if(vertex->head_edge->next == NULL) {
            Edge *edge = vertex->head_edge;
            vertex->head_edge = NULL;
            free(edge);
            return;
        }

        Edge *edge = vertex->head_edge;
        vertex->head_edge = vertex->head_edge->next;
        free(edge);

        return;
    }

    //when not first node, follow the normal deletion process:
    //find the previous node
    Edge *prev = vertex->head_edge;
    while(prev->next != NULL) {
        if (strcmp(prev->next->directed_vertex->name, direction_name) == 0 && prev->next->weight == weight) {
            break;
        }
        prev = prev->next;
    }

    Edge *edge = prev->next;        //the edge to be deleted
    //check if edge really exists in adjacency list (because prev pointer might have reached end of list)
    if(prev->next == NULL) {
        printf("Given edge could not be found\n");
        return;
    }

    //remove edge from adjacency list and make previous edge point to the next one of the deleted
    prev->next = edge->next;
    free(edge);
}


//Delete all edges between one given vertex towards another given vertex
void delete_edges(Graph *graph, char *start_name, char *direction_name) {
    Vertex *vertex = search_for_vertex(graph, start_name);

    delete_edges_without_search(graph, &vertex, direction_name);
}


//Delete edges between a given vertex towards another
//it does not require a search by name for the starting vertex because it is already passed as struct Vertex
void delete_edges_without_search(Graph *graph, Vertex **vertex, char *direction_name) {
    Vertex *vptr = *vertex;
    //if there are no edges stop
    if (vptr->head_edge == NULL) {
        return;
    }

    //if the edge to be deleted is the only one edge in the list make head_edge in vertex point to null and free edge
    if(vptr->head_edge->next == NULL && strcmp(vptr->head_edge->directed_vertex->name, direction_name) == 0) {
        Edge *edge = vptr->head_edge;
        (*vertex)->head_edge = NULL;
        free(edge);
        return;     //stop because list is empty
    }

    Edge *prev = vptr->head_edge;

    while (prev->next != NULL) {
        //when one of the edges to be deleted is head edge
        if(strcmp(vptr->head_edge->directed_vertex->name, direction_name) == 0) {
            Edge *edge = vptr->head_edge;
            (*vertex)->head_edge = vptr->head_edge->next;
            free(edge);
        //when not first node, follow the normal deletion process:
        } else {
            //find the previous node
            if (strcmp(prev->next->directed_vertex->name, direction_name) == 0) {
                Edge *edge = prev->next;        //the edge to be deleted
                //remove edge from adjacency list and make previous edge point to the next one of the deleted
                prev->next = edge->next;
                // Free memory
                free(edge);
            }
            else {
                prev = prev->next;
            }
        }
    }
}


//Add edge to the adjacency list of the given vertex towards another given vertex
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


//Modify weight in an edge between a given vertex towards another given vertex
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


//Print all edges starting from a given vertex
void print_edges(Graph *graph, char *name) {
    Vertex *vertex = search_for_vertex(graph, name);
    Edge *current = vertex->head_edge;

    while (current != NULL) {
        printf("%s %d\n", current->directed_vertex->name, current->weight);
        current = current->next;
    }
}


//Print all vertices and edges of the given graph to an opened file
void print_to_file(Graph *graph, FILE *ofile) {
    Vertex *cur_vertex = graph->head;

    while (cur_vertex != NULL) {
        fprintf(ofile, "|%s|\n", cur_vertex->name);

        Edge *cur_edge = cur_vertex->head_edge;
        while (cur_edge != NULL) {
            fprintf(ofile, "\t-%d -> |%s|\n", cur_edge->weight, cur_edge->directed_vertex->name);
            cur_edge= cur_edge->next;
        }
        fprintf(ofile, "\n");
        cur_vertex = cur_vertex->next;
    }
}


//Delete all edges and vertices and free allocated memory
void release_memory(Graph **graph) {
    Vertex* cur_vertex = (*graph)->head;
    Vertex* next_vertex;

    while (cur_vertex != NULL) {
       next_vertex = cur_vertex->next;

       Edge *cur_edge = cur_vertex->head_edge;
       Edge *next_edge;
       while (cur_edge != NULL) {
           next_edge = cur_edge->next;
           free(cur_edge);
           cur_edge = next_edge;
       }

       free(cur_vertex->name);
       free(cur_vertex);
       cur_vertex = next_vertex;
    }

    free(*graph);
}
