#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "main_functions.h"

int main(int argc, char const *argv[]) {

    Graph *graph = initialize_graph();

    //read input file if given and insert new vertices and edges
    read_input_file(argc, argv, &graph);

    //ask for user input until user enters "exit"
    char prompt[100];
    do {
        //empty prompt array before asking for new user input
        memset(prompt, 0, 100);
        printf("Please enter a command: ");
        fgets(prompt, 100, stdin);
        //remove newline character from prompt string
        prompt[strcspn(prompt, "\r\n")] = 0;
        //call function to execute prompts given on the graph
        execute_prompt(prompt, &graph);
    } while(strcmp(prompt, "e") != 0);

    write_output_file(argc, argv, graph);

    return 0;
}
