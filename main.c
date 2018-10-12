#include <stdio.h>
#include "graph.h"
#include "main_functions.h"

int main(int argc, char const *argv[]) {

    Graph *graph = initialize_graph();

    //read input file if given and insert new vertices and edges
    read_input_file(argc, argv, &graph);

    printf("\nALL VERTICES\n");
    print_vertices(graph);
    printf("ALL VERTICES\n\n");



    return 0;


}
