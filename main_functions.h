#ifndef MAIN_FUNCTIONS_HEADER
#define MAIN_FUNCTIONS_HEADER

#include "graph.h"

void read_input_file(int argc, char const *argv[], Graph **graph);
void write_output_file();
void execute_prompt(char *prompt, Graph **graph);

#endif
