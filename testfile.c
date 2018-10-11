#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    //check arguments given (except argv[0] which is the program name)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            printf("%s\n", argv[i+1]);
            FILE *ifile;
            char *line = NULL;
            size_t len = 0;

            //open file that comes right after "-i" in the command line arguments
            ifile = fopen(argv[i + 1], "r");

            if (ifile == NULL) {
                printf("%s\n", "Input file could ot be opened \n");
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
