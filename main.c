#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"

int main(int argc, char const *argv[]) {

    //check arguments given

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            FILE * ifile;
            char * line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + i], "r");
            // ifile = fopen("InputFile-Small.csv", "r");
            printf("%s\n", argv[i+1]);

            if (ifile == NULL) {
                printf("%s\n", "an input file \n");
                // exit(EXIT_FAILURE);
            }

            while (getline(&line, &len, ifile) != -1) {
                printf("%s", line);
            }

            fclose(ifile);
            // if (line) {
            //     free(line);
            // }
        }
        if (strcmp(argv[i], "-o") == 0) {
            //anoigo to arxeio argv i+1 gia na grapse
        }
    }

    //allocate memory for pointer that will point to head of vertex list
    Vertex *head = NULL;
    head = malloc(sizeof(Vertex));

    char *str = "hello";
    add_vertex(&head, str);
    char *str1 = "happy";
    add_vertex(&head, str1);
    char *str2 = "sad";
    add_vertex(&head, str2);

    //iterate through linked list
    Vertex *temp = head;
    while (temp->next !=NULL){
        printf("%s\n", temp->name);
        temp = temp->next; // get the next element
    }


    return 0;


}
