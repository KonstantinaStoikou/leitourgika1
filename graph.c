#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

//Allocate memory for graph struct
Graph * initialize_graph(void) {
    Graph *graph = NULL;
    graph = malloc(sizeof(Graph));

    graph->head = NULL;

    //last_id is a graph member that is incremented by 1 everytime a new vertex is add_edge
    //and it is used as an id for each added vertex (ids start from 0)
    graph->last_id = 0;

    return graph;
}


//Add vertex to the start of vertex list
int add_vertex(Graph **graph, char *name) {
    //check if given vertex exists
    if (search_for_vertex(*graph, name) != NULL) {
        return 1;
    }

    // Allocate memory for node
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));

    new_vertex->name = malloc(strlen(name)+1);
    strcpy(new_vertex->name, name);

    new_vertex->next = (*graph)->head;
    new_vertex->head_edge = NULL;
    new_vertex->id = (*graph)->last_id;

    //increase last_id by 1 to use as id for the next inserted node
    (*graph)->last_id++;

    // Change head pointer as new node is added at the beginning
    (*graph)->head = new_vertex;

    return 0;
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
int delete_vertex(Graph **graph, char *name) {
    Vertex *vertex = search_for_vertex(*graph, name);

    //check if given vertex exists
    if (vertex == NULL) {
        return 1;
    }

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
            return 0;
        }

        Vertex *v = (*graph)->head;
        (*graph)->head = v->next;
        free(v->name);
        free(v);

        return 0;
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
        return 1;
    }

    //remove vertex from graph and make previous vertex point to the next one of the deleted
    prev->next = v->next;
    free(v->name);
    free(v);

    return 0;

}


//Print edges that are directed at the given vertex
int print_receiving(Graph *graph, char *name) {
    //check if given vertex exists
    if (search_for_vertex(graph, name) == NULL) {
        return 1;
    }

    Vertex *cur_vertex = graph->head;
    int flag = 0;   //flag will be set to 1 if at least one edge is printed

    while (cur_vertex != NULL) {
        Edge *cur_edge = cur_vertex->head_edge;

        while (cur_edge != NULL) {
            if (strcmp(cur_edge->directed_vertex->name, name) == 0) {
                //the message "- Rec-edges" will be printed only the first time a receiving edge is found
                if (flag == 0) {
                    printf("- Rec-edges\n");
                    flag = 1;
                }
                printf("\t|%s|->%d->|%s|\n", cur_vertex->name, cur_edge->weight, name);
            }
            cur_edge = cur_edge->next;
        }
        cur_vertex = cur_vertex->next;
    }
    //if no edge was printed, print a message
    if (flag == 0) {
        printf("- No-rec-edges %s\n", name);
    }

    return 0;
}


int print_simple_circles(Graph *graph, char *name) {
    Vertex *vertex = search_for_vertex(graph, name);

    //check if given vertex exists
    if (vertex == NULL) {
        return 1;
    }

    //create an array with the size of the graph until this moment (the last_id
    //of graph shows the number of vertices in the graph) and use it to indicate
    //which vertex has been visited while make Depth-First Search
    int *visited = (int*) malloc((graph->last_id) * sizeof(int));
    //initialize array to 0 (because none of the vertices has been visited yet)
    for (int i = 0; i < graph->last_id; i++) {
        visited[i] = 0;
    }

    char *circles = malloc(sizeof(char));
    // char *circles = malloc(strlen(vertex->name) + 1);
    circles[0] = '\0';
    // strcpy(circles, vertex->name);
    DFS(graph, vertex, &visited, &circles, vertex->id);
    // printf("RESULTS ARE %s\n", results);

    return 0;
}


int DFS(struct Graph* graph, Vertex *vertex, int **visited, char **results, int initial_id) {

    Vertex *cur_vertex = vertex;
    Edge *cur_edge = cur_vertex->head_edge;
    //mark as visited the vertex that is currently being searched
    (*visited)[cur_vertex->id] = 1;
    int flag = 0;

    //while there are still edges to iterate in this vertex's adjacency list
    while (cur_edge != NULL) {

        Vertex *directed_vertex = cur_edge->directed_vertex;

        //if the current edge is pointing to a vertex that hasnt been visited call DFS for this vertex
        if ((*visited)[cur_edge->directed_vertex->id] == 0) {
            // if (cur_edge == vertex->head_edge) {
            //     printf("in if\n");
                *results = realloc(*results, strlen(*results) + strlen(cur_vertex->name) + 2);
                strcat(*results, "->");
                strcat(*results, cur_vertex->name);
            // }

            printf("results is %s\n", *results);

            char *temp = malloc(strlen(*results) + 1);
            strcpy(temp, *results);
            printf("temp is %s\n", temp);
            // DFS(graph, directed_vertex, visited, &temp, initial_id);
            if (DFS(graph, directed_vertex, visited, &temp, initial_id) == 1) {
                printf("hiii\n");
            // DFS(graph, directed_vertex, visited, &temp, initial_id);
                *results = realloc(*results, sizeof(char));
                *results[0] = '\0';
                // strcpy(*results, "nbc");
                printf("after dfs temp is %s\n", temp);
            }

        }
        //if this edge is pointing to the initial vertex a circle has happened
        else if (cur_edge->directed_vertex->id == initial_id) {
            *results = realloc(*results, strlen(*results) + strlen(cur_vertex->name) + strlen(cur_edge->directed_vertex->name) + 2);
            strcat(*results, "->");
            strcat(*results, cur_vertex->name);
            strcat(*results, "->");
            strcat(*results, cur_edge->directed_vertex->name);
            printf("Reached a circle: %s\n", *results);
            *results = realloc(*results, sizeof(char));
            *results[0] = '\0';
            flag = 1;
            //mark as visited the vertex that was initially passed
            (*visited)[initial_id] = 1;

        }
        //move to next edge
        cur_edge = cur_edge->next;
    }
    //when the vertex that is currently being searched has no other edges to call dfs mark it as unvisited
    (*visited)[cur_vertex->id] = 0;
    return flag;
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
int modify_weight_in_edge(Graph *graph, char *start_name, char *direction_name, int weight, int new_weight) {
    int error;
    Edge *edge = search_for_edge(graph, start_name, direction_name, weight, &error);
    if (edge == NULL) {
        return error;
    }

    edge->weight = new_weight;
    return 0;
}


//Find if an edge with the given weight exists in the adjacency list of the
//given vertex and return it else return null
//if multiple edges exists with the same weight and vertices return the first one found
Edge * search_for_edge(Graph *graph, char *start_name, char *direction_name, int weight, int *error) {
    Vertex *starting_vertex = search_for_vertex(graph, start_name);
    //check if start vertex exists
    if (starting_vertex == NULL) {
        *error = 1;
        return NULL;
    }
    //check if direction vertex exists
    if (search_for_vertex(graph, direction_name) == NULL) {
        *error = 2;
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
    *error = 3;
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


//Delete edge between one given vertex towards another given vertex with certain weight
int delete_edge(Graph *graph, char *start_name, char *direction_name, int weight) {
    Vertex *vertex = search_for_vertex(graph, start_name);

    //check if start vertex exists
    if (vertex == NULL) {
        return 1;
    }
    //check if direction vertex exists
    if (search_for_vertex(graph, direction_name) == NULL) {
        return 2;
    }

    //when edge to be deleted is head edge
    if(strcmp(vertex->head_edge->directed_vertex->name, direction_name) == 0 && vertex->head_edge->weight == weight) {
        //if there is only one edge in the list make head_edge in vertex point to null and free edge
        if(vertex->head_edge->next == NULL) {
            Edge *edge = vertex->head_edge;
            vertex->head_edge = NULL;
            free(edge);
            return 0;
        }

        Edge *edge = vertex->head_edge;
        vertex->head_edge = vertex->head_edge->next;
        free(edge);

        return 0;
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
        return 3;
    }

    //remove edge from adjacency list and make previous edge point to the next one of the deleted
    prev->next = edge->next;
    free(edge);

    return 0;
}


//Delete all edges between one given vertex towards another given vertex
int delete_edges(Graph *graph, char *start_name, char *direction_name) {
    Vertex *vertex = search_for_vertex(graph, start_name);

    //check if start vertex exists
    if (vertex == NULL) {
        return 1;
    }
    //check if direction vertex exists
    if (search_for_vertex(graph, direction_name) == NULL) {
        return 2;
    }

    delete_edges_without_search(graph, &vertex, direction_name);
    return 0;
}


//Delete edges between a given vertex towards another
//it does not require a search by name for the starting vertex because it is already passed as struct Vertex
void delete_edges_without_search(Graph *graph, Vertex **vertex, char *direction_name) {
    //if there are no edges stop
    if ((*vertex)->head_edge == NULL) {
        return;
    }

    //if the edge to be deleted is the only one edge in the list make head_edge in vertex point to null and free edge
    if((*vertex)->head_edge->next == NULL && strcmp((*vertex)->head_edge->directed_vertex->name, direction_name) == 0) {
        Edge *edge = (*vertex)->head_edge;
        (*vertex)->head_edge = NULL;
        free(edge);
        return;     //stop because list is empty
    }

    Edge *prev = (*vertex)->head_edge;

    while (prev->next != NULL) {
        //when one of the edges to be deleted is head edge
        if(strcmp((*vertex)->head_edge->directed_vertex->name, direction_name) == 0) {
            Edge *edge = (*vertex)->head_edge;
            (*vertex)->head_edge = (*vertex)->head_edge->next;
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


//Print all vertices and edges of the given graph to an opened file
void print_to_file(Graph *graph, FILE *ofile) {
    Vertex *cur_vertex = graph->head;

    while (cur_vertex != NULL) {
        fprintf(ofile, "|%s|\n", cur_vertex->name);

        Edge *cur_edge = cur_vertex->head_edge;
        while (cur_edge != NULL) {
            fprintf(ofile, "\t-%d->|%s|\n", cur_edge->weight, cur_edge->directed_vertex->name);
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
