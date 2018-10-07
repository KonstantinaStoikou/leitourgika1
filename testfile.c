#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char const *argv[]) {

    //check arguments given
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            FILE *ifile;
            char *line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + i], "r");
            // ifile = fopen("InputFile-Small.csv", "r");
            printf("%s\n", argv[i+1]);

            if (ifile == NULL) {
                printf("%s\n", "an input file \n");
                exit(EXIT_FAILURE);
            }

            while (getline(&line, &len, ifile) != -1) {
                printf("%s", line);
            }

            fclose(ifile);
            ifile = NULL;
            if (line) {
                free(line);
            }
        }

    }



    return 0;


}
