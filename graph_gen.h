
#ifndef __GRAPH_GEN_H__
#define __GRAPH_GEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "structs.h"



graph matrix_to_graph(int **matrix, int size);


int *rand_permut(int n);


graph permut_graph(graph G1, int *permut);


graph rand_connected_graph(int size, int edges);
// generate a random connected graph. Not sure that this generation method is uniform...



#endif
