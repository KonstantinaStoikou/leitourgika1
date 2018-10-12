#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "main_functions.h"

int main(int argc, char const *argv[]) {

    Graph *graph = initialize_graph();

    //read input file if given and insert new vertices and edges
    read_input_file(argc, argv, &graph);

    //ask for user input until user enters "exit"
    char prompt[50];
    do {
        printf("Please enter a command: ");
        scanf ("%s", prompt);
        execute_prompt(prompt, &graph);
    } while(strcmp(prompt, "e") != 0);

    printf("\nALL VERTICES\n");
    print_vertices(graph);
    printf("ALL VERTICES\n\n");



    return 0;


}
