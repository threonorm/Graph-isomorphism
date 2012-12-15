#include <stdlib.h>
#include <stdio.h>

#include "structs.h"

#ifndef __CONNEXITY_H__
#define __CONNEXITY_H__


int DFS(graph G, int vertex, int no, int *table);


int connexity(graph G, int *cards);


// display the number of connected components of G and the distribution by size
void study_connexity(graph G);





#endif
