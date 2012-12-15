
#ifndef __COLORS_H__
#define __COLORS_H__


#include <stdlib.h>


#include "structs.h"


void refine_coloration(graph G, int *old_colors, big_color *new_colors);
// returns a big_color set that is a more refined coloration of graph G


int match_colors(big_color *bc1, big_color *bc2, int *colors1, int *colors2, int *V, int *iso, int size);
// renumerate colors in G1 and G2, find a possible mismatch and if not, puts in V the number of vertices for each color                                                                           
// at the end, V contains the number of vertices (in G1, but that's the same in G2) for each color                                                                                                
// 0 = non comptatible  1 = compatible  2 = compatible and stable 



#endif
