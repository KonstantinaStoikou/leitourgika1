#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

int main(int argc, char const *argv[]) {
    char *str = "hello";
    Vertex *ptr = (Vertex *)malloc(sizeof(Vertex));
    ptr = initialize_list(str);
    printf("%s\n", ptr->name);
    char *str1 = "happy";
    add_vertex(&ptr, str1);
    printf("%s\n", ptr->name);
    return 0;
}
