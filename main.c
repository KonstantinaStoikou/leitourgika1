#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char const *argv[]) {

    Graph *graph = initialize_graph();
/*
    //check arguments given
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            FILE *ifile;
            char *line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + i], "r");
            // ifile = fopen("InputFile-Small.csv", "r");
            // printf("%s\n", argv[i+1]);

            if (ifile == NULL) {
                // printf("%s\n", "an input file \n");
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
                printf("head is %s\n", graph->head->name);
                print_vertices(graph);
                // print_edges(graph, tokens[0]);
                printf("\n\n" );
            }

            //me tin fclose mallon iparxei provlima
            // fclose(ifile);
            ifile = NULL;
            if (line) {
                free(line);
            }
        }
        // if (strcmp(argv[i], "-o") == 0) {
            //anoigo to arxeio argv i+1 gia na grapse
        // }
    }

*/

    // char *str = "hello";
    // add_vertex(&graph, str);
    // char *str1 = "happy";
    // add_vertex(&graph, str1);
    // char *str2 = "sad";
    // add_vertex(&graph, str2);
    // char *str3 = "oui";
    // add_vertex(&graph, str3);

    // printf("head is %s\n", graph->head->name);
    add_edge(&graph, "Marion_Beck", "Jim_Johnston", 95);
    add_edge(&graph, "Irene_Weaver", "Shawn_Ford", 596);
    add_edge(&graph, "Irene_Weaver", "Shawn_Ford", 598);
    add_edge(&graph, "Jack_Hawkins", "Shawn_Ford", 368);
    add_edge(&graph, "Jeffery_Walters", "Tom_Casey", 119);
    add_edge(&graph, "Shawn_Ford", "Bernice_Gross", 889);
    add_edge(&graph, "Ola_Rios", "Janie_Warner", 967);
    add_edge(&graph, "Irene_Weaver", "Janie", 568);
    add_edge(&graph, "Leonard_Reeves", "Myra_Burke", 867);

    print_edges(graph, "Irene_Weaver");
    printf("ALL VERTICES\n");
    print_vertices(graph);
    // print_edges(graph, "sad");
    // print_edges(graph, "bbb");


    return 0;


}
