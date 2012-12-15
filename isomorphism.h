
#ifndef __ISOMORPHISM_H__
#define __ISOMORPHISM_H__


#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "colors.h"


int find_contradiction(graph G1, graph G2, int *iso, int *iso_inv, int vertex);
// find if the new matching vertex -> iso(vertex) leads to a contradiction : if contradictions found return 1 else 0 


int vertex_to_match(graph G1, int *colors1, int *iso, int *V, int *vertex, int size);
// stores in vertex which vertex seems to be the easiest to match, returns 1 if it is the only one in this color, 0 otherwise  


int weisfeiler_lehman1(graph G1, graph G2, int *iso);
// iso must be allocated before calling this function. At the end, iso contains the isomorphism if G1 and G2 are isomorph


int isomorphism_naive(graph G1, graph G2, int *iso);
// a very naive backtracking algorithm for the ismorphism problem. Just for comparison ^^


int iso_check(graph G1, graph G2, int *iso);
// check wether the given isomorphism 'iso' between G1 and G2 is correct



#endif
