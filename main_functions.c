#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_functions.h"


//Function that checks if flag "-i" was given as input and if yes then reads
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


//Function that checks if flag "-o" was given as input and if yes then writes
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

            fclose(ofile);
            ofile = NULL;
        }
    }
}


//Function that calls graph functions based on input prompt and print success
//or failure messages
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

    //i(nsert) Ni
    if (strcmp(words[0], "i") == 0) {
        if (add_vertex(graph, words[1]) == 0) {
            printf("- Inserted |%s|\n", words[1]);
        } else {
            printf("- Node |%s| exists\n", words[1]);
        }
    }
    //(i)n(sert) Ni Nj weight
    else if (strcmp(words[0], "n") == 0) {
        add_edge(graph, words[1], words[2], atoi(words[3]));
        printf("- Inserted |%s|->%s->|%s|\n", words[1], words[3], words[2]);
    }
    //d(elete) Ni
    else if (strcmp(words[0], "d") == 0) {
        if (delete_vertex(graph, words[1]) == 0) {
            printf("- Deleted |%s|\n", words[1]);
        } else {
            printf("- Node |%s| does not exist - abort-d;\n", words[1]);
        }
    }
    //(de)l(ete) Ni Nj weight
    else if (strcmp(words[0], "l") == 0) {
        //check if weight has been given as input
        if (words[3] != NULL) {
            int error = delete_edge(*graph, words[1], words[2], atoi(words[3]));
            if (error == 1) {
                printf("- |%s| does not exist - abort-l;\n", words[1]);
            } else if (error == 2) {
                printf("- |%s| does not exist - abort-l;\n", words[2]);
            } else if (error == 3) {
                printf("- |%s|->%s->|%s| does not exist - abort-l;\n", words[1], words[3], words[2]);
            } else {
                printf("- Del-vertex |%s|->%s->|%s|\n", words[1], words[3], words[2]);
            }
        } else {
            int error = delete_edges(*graph, words[1], words[2]);
            if (error == 1) {
                printf("- |%s| does not exist - abort-l;\n", words[1]);
            } else if (error == 2) {
                printf("- |%s| does not exist - abort-l;\n", words[3]);
            } else {
                printf("- Del-vertices |%s|->|%s|\n", words[1], words[2]);
            }
        }
    }
    //m(odify) Ni Nj weight nweight
    else if (strcmp(words[0], "m") == 0) {
        int error = modify_weight_in_edge(*graph, words[1], words[2], atoi(words[3]), atoi(words[4]));
        if (error == 1) {
            printf("- |%s| does not exist - abort-m;\n", words[1]);
        } else if (error == 2) {
            printf("- |%s| does not exist - abort-m;\n", words[3]);
        } else if (error == 3) {
            printf("- |%s|->%s->|%s| does not exist - abort-m;\n", words[1], words[3], words[2]);
        } else {
            printf("- Mod-vertex |%s|->%s->|%s|\n", words[1], words[4], words[2]);
        }
    }
    //r(eceiving) Ni
    else if (strcmp(words[0], "r") == 0) {
        if (print_receiving(*graph, words[1]) == 1) {
            printf("- |%s| does not exist - abort-r;\n", words[1]);
        }
    }
    //c(irclefind) Ni
    else if (strcmp(words[0], "c") == 0) {
        /* code */
    }
    //f(indcircles) Ni k
    else if (strcmp(words[0], "f") == 0) {
        /* code */
    }
    //t(raceflow) Ni Nj l
    else if (strcmp(words[0], "t") == 0) {
        /* code */
    }
    //e(xit)
    else if (strcmp(words[0], "e") == 0) {
        printf("- exit program\n");
    }
    //EXTRA PROMPTS FOR DEBUGGING:
    //print edges: pe Ni
    else if (strcmp(words[0], "pe") == 0) {
        print_edges(*graph, words[1]);
    }
    //print vertices: pv
    else if (strcmp(words[0], "pv") == 0) {
        print_vertices(*graph);
    }
    else {
        printf("There is no such command\n");
    }

    printf("\n");
}
