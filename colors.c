
#include "colors.h"






// refine coloration of G with big_colors. The new coloration is stored in table 'new_colors', which has to be allocated before calling this function !
void refine_coloration(graph G, int *old_colors, big_color *new_colors)
{
  int size = G.size;
  int i, j;

  for(i=0 ; i<G.size ; i++) {
    new_colors[i].fix = old_colors[i];
    for(j=0 ; j<size ; j++)
      new_colors[i].mult[j] = 0;
    list neighbors = G.neighbors[i];
    while(neighbors != NULL) {
      new_colors[i].mult[old_colors[neighbors->head]]++;
      neighbors = neighbors->tail;
    }
  }

}






int match_colors(big_color *bc1, big_color *bc2, int *colors1, int *colors2, int *iso, int *V, int size)
// renumerate colors in G1 and G2, find a possible mismatch and if not, puts in V the number of vertices for each color
// at the end, V contains the number of vertices (in G1, but that's the same in G2) for each color
// 0 = non comptatible  1 = compatible  2 = compatible and stable
{
  int *old_colors1 = malloc(size*sizeof(int));
  int *old_colors2 = malloc(size*sizeof(int));
  int *V2 = malloc(size*sizeof(int));
  int i;
  for(i=0 ; i<size ; i++) {
    old_colors1[i] = colors1[i];
    old_colors2[i] = colors2[i];
    colors1[i] = -1;
    colors2[i] = -1;
    V[i] = 0;
    V2[i] = 0;
  }

  // compressing colors in G1
  int color_max = -1;

  for(i=0 ; i<size ; i++) {
    int j;
    for(j=0 ; j<i ; j++)
      if(comp_big_colors(bc1[i],bc1[j],size)) {
        colors1[i] = colors1[j]; // already existing color
        break;
      }
    if(colors1[i] == -1)
      colors1[i] = (++color_max); // new color
    V[colors1[i]]++;
  }

  // compressing colors in G2 and checking if no new color (not in G1) appears in G2
  for(i=0 ; i<size ; i++) {
    int j;
    for(j=0 ; j<size ; j++)
      if(comp_big_colors(bc2[i],bc1[j],size)) {
        colors2[i] = colors1[j]; // found the same color in G1
        break;
      }
    if(colors2[i] == -1) { // no identical color in G1
      free(old_colors1);
      free(old_colors2);
      free(V2);
      return 0; // G1 and G2 are not isomorph
    }
    V2[colors2[i]]++;
  }

  // now whe should check that the distribution of colors in G1 and G2 are compatible

  for(i=0 ; i<size ; i++)
    if(V[i] != V2[i]) {
      free(V2);
      free(old_colors1);
      free(old_colors2);
      return 0;
    }

  // now we check if the coloration becomes stable
  int flag = 2;
  for(i=0 ; i<size ; i++)
    if(colors1[i] != old_colors1[i])
      flag = 1;

  free(old_colors1);
  free(old_colors2);
  free(V2);

  return flag;

}
