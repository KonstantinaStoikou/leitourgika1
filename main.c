#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char const *argv[]) {

    Graph *graph = initialize_graph();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            FILE *ifile;
            char *line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + 1], "r");

            if (ifile == NULL) {
                printf("%s\n", "Input file could not be opened \n");
                exit(EXIT_FAILURE);
            }

            while (getline(&line, &len, ifile) != -1) {
                //split line to three words (2 vertices and weight of edge)
                //and insert new edge to graph
                char *tokens[3];              //array that will store the three infos of each line (2 vertices and weight)
                int count = 0;
                char *token = strtok(line, " \t");  //split line by whitespaces
                while (token) {
                    tokens[count] = token;
                    count++;
                    token = strtok(NULL, " \t");
                }

                add_edge(&graph, tokens[0], tokens[1], atoi(tokens[2]));
            }

            fclose(ifile);
            ifile = NULL;
            if (line) {
                free(line);
            }
        }
    }

    // print_edges(graph, "Irene_Weaver");
    printf("\nALL VERTICES\n");
    print_vertices(graph);
    printf("ALL VERTICES\n\n");
    // printf("%d\n", search_for_edge(graph, "Irene_Weaver", "Shawn_Ford", 596)->weight);
    // modify_weight_in_edge(graph, "Irene_Weaver", "Shawn_Ford", 596, 900);
    // printf("%d\n", search_for_edge(graph, "Irene_Weaver", "Shawn_Ford", 900)->weight);
    // delete_edge(graph, "Irene_Weaver", "Janie", 568);
    // printf("headdd %s\n", search_for_vertex(graph, "Irene_Weaver")->head_edge->directed_vertex->name);
    // delete_edge(graph, "Irene_Weaver", "Maria", 668);
    // print_edges(graph, "Irene_Weaver");
    // printf("headdd %s\n", search_for_vertex(graph, "Irene_Weaver")->head_edge->directed_vertex->name);
    // print_edges(graph, "sad");
    // print_edges(graph, "bbb");


    return 0;


}
