#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char const *argv[]) {
    char *str = "hello";
    struct Vertex *ptr = (struct Vertex *)malloc(sizeof(struct Vertex));
    ptr = create_graph(str);
    printf("%s\n", ptr->name);
    return 0;
}
