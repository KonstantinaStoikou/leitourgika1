#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_functions.h"


//Functions that checks if flag "-i" was given as input and if yes then reads
//the given file line by line and adds the vertices and edges given on the file
void read_input_file(int argc, char const *argv[], Graph **graph) {
    printf("hii\n");
    for (int i = 1; i < argc; i++) {
        //check if flag "-i" was given as input
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

                add_edge(graph, tokens[0], tokens[1], atoi(tokens[2]));
            }

            fclose(ifile);
            ifile = NULL;
            if (line) {
                free(line);
            }
        }
    }
}
