
#ifndef __ISOMORPHISM_H__
#define __ISOMORPHISM_H__


#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "colors.h"


int find_contradiction(graph G1, graph G2, int *iso, int *iso_inv, int vertex);
// find if the new matching vertex -> iso(vertex) leads to a contradiction : if contradictions found return 1 else 0 

int vertex_to_match(int *colors1, int *iso, int *V, int size);

int weisfeiler_lehman1(graph G1, graph G2, int *iso);

int isomorphism_naive(graph G1, graph G2, int *iso);




#endif
