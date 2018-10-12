#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_functions.h"


//Functions that checks if flag "-i" was given as input and if yes then reads
//the given file line by line and adds the vertices and edges given on the file
void read_input_file(int argc, char const *argv[], Graph **graph) {
    for (int i = 1; i < argc; i++) {
        //check if flag "-i" was given as input
        if (strcmp(argv[i], "-i") == 0) {
            FILE *ifile;
            char *line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + 1], "r");

            if (ifile == NULL) {
                printf("Input file could not be opened \n");
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


//Functions that checks if flag "-o" was given as input and if yes then writes
//to the given file the final state of the graph (when user exits the program)
void write_output_file(int argc, char const *argv[], Graph *graph) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            FILE *ofile = fopen(argv[i + 1], "w");
            if (ofile == NULL) {
                printf("Output file could not be opened \n");
                exit(EXIT_FAILURE);
            }

            print_to_file(graph, ofile);
        }
    }
}


void execute_prompt(char *prompt, Graph **graph) {
    //break prompt into words
    char *words[5];         //maximum number of words for a prompt is 5
    int count = 0;
    char *word = strtok(prompt, " ");  //split prompt by spaces
    while (word) {
        words[count] = word;
        count++;
        word = strtok(NULL, " ");
    }

    if (strcmp(words[0], "i") == 0) {
        //i(nsert) Ni
        add_vertex(graph, words[1]);
    } else if (strcmp(words[0], "n") == 0) {
        //(i)n(sert) Ni Nj weight
        add_edge(graph, words[1], words[2], atoi(words[3]));
    } else if (strcmp(words[0], "d") == 0) {
        //d(elete) Ni
        /* code */
    } else if (strcmp(words[0], "l") == 0) {
        //(de)l(ete) Ni Nj weight
        //check if weight has been given as input
        if (words[3] != NULL) {
            delete_edge(*graph, words[1], words[2], atoi(words[3]));
        } else {
            delete_edges(*graph, words[1], words[2]);
        }
    } else if (strcmp(words[0], "m") == 0) {
        //m(odify) Ni Nj weight nweight
        modify_weight_in_edge(*graph, words[1], words[2], atoi(words[3]), atoi(words[4]));
    } else if (strcmp(words[0], "r") == 0) {
        //r(eceiving) Ni
        /* code */
    } else if (strcmp(words[0], "c") == 0) {
        //c(irclefind) Ni
        /* code */
    } else if (strcmp(words[0], "f") == 0) {
        //f(indcircles) Ni k
        /* code */
    } else if (strcmp(words[0], "t") == 0) {
        //t(raceflow) Ni Nj l
        /* code */
    } else if (strcmp(words[0], "e") == 0) {
        //e(xit)
    //EXTRA PROMPTS FOR DEBUGGING:
    } else if (strcmp(words[0], "pe") == 0) {
        //print edges: pe Ni
        print_edges(*graph, words[1]);
    } else if (strcmp(words[0], "pv") == 0) {
        //print vertices: pv
        print_vertices(*graph);
    } else {
        printf("There is no such command\n");
    }

    printf("\n");
}
