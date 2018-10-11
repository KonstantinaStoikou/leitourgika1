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
                printf("\nALL VERTICES\n");
                print_vertices(graph);
                printf("ALL VERTICES\n\n");
                printf("line is %s", line);
                //split line to three words (2 vertices and weight of edge)
                //and insert new edge to graph
                char *tokens[3];              //array that will store the three infos of each line (2 vertices and weight)
                int count = 0;
                char *token = strtok(line, " \t");  //split line by whitespaces
                while (token) {
                    tokens[count] = token;
                    printf("token is \"%s\"\n", token);
                    count++;
                    token = strtok(NULL, " \t");
                }
                // printf("%s\n", tokens[0]);
                // printf("%s\n", tokens[1]);
                // printf("\"%d\"\n", atoi(tokens[2]));
                char *name1 = tokens[0];
                printf("name1 is \"%s\"\n", name1);
                char *name2 = tokens[1];
                printf("name2 is \"%s\"\n", name2);
                int num = atoi(tokens[2]);
                printf("number is \"%d\"\n", atoi(tokens[2]));
                add_edge(&graph, name1, name2, num);

                // add_edge(&graph, tokens[0], tokens[1], atoi(tokens[2]));
                printf("Vertices till now : \n");
                print_vertices(graph);
                printf("\n\n" );
            }

            fclose(ifile);
            ifile = NULL;
            if (line) {
                free(line);
            }
        }
    }


    // char *str = "hello";
    // add_vertex(&graph, str);
    // char *str1 = "happy";
    // add_vertex(&graph, str1);
    // char *strs = "sad";
    // add_vertex(&graph, str2);
    // char *str3 = "oui";
    // add_vertex(&graph, str3);

    // printf("head is %s\n", graph->head->name);
    // add_edge(&graph, "Marion_Beck", "Jim_Johnston", 95);
    // add_edge(&graph, "Irene_Weaver", "Shawn_Ford", 596);
    // add_edge(&graph, "Irene_Weaver", "Tom_Casey", 598);
    // add_edge(&graph, "Jack_Hawkins", "Tom_Casey", 368);
    // add_edge(&graph, "Jeffery_Walters", "Tom_Casey", 119);
    // add_edge(&graph, "Shawn_Ford", "Bernice_Gross", 889);
    // add_edge(&graph, "Ola_Rios", "Janie_Warner", 967);
    // add_edge(&graph, "Irene_Weaver", "Janie", 568);
    // add_edge(&graph, "Irene_Weaver", "Maria", 668);
    // add_edge(&graph, "Leonard_Reeves", "Myra_Burke", 867);

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
