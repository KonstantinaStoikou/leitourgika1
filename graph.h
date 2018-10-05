#ifndef VERTEX_HEADER
#define VERTEX_HEADER

#include "vertex.h"

typedef struct Node {
    Vertex vertex;
    //koitao an thelei pointer o vertex
    struct Node * next;
} Node;

#endif
