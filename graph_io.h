
#ifndef __GRAPH_IO_H__
#define __GRAPH_IO_H__

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"


list lecture_ligne(FILE *file);
//-----To read a line of a graph-file and build the neibourhood associated---  


graph graph_from_file(FILE *file);
//-----To read a graph from a graph-file


void fast_print_graph(graph G);
// a basic display for the graph G


#endif
