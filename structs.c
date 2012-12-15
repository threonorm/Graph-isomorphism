
#include "structs.h"





int free_list(list l)
{
  list aux1=l;
  list aux2=l;
  while(aux2 != NULL) {
    aux1=aux2->tail;
    free(aux2);
    aux2=aux1;
  }
  return 0;
}


list pop(list l)
{
  if(l == NULL)
    return NULL;
  else
    return l->tail;
}


list push(int n, list l)
{
  list new_l = malloc(sizeof(cons));
  new_l->head = n;
  new_l->tail = l;
  return new_l;
}


big_color new_big_color(int size)
{
  big_color bc;
  bc.fix = 0;
  bc.mult = malloc(size*sizeof(int));
  int i;
  for(i=0 ; i<size ; i++)
    bc.mult[i] = 0;
  return bc;
}


void delete_big_color(big_color bc)
{
  free(bc.mult);
};


int comp_big_colors(big_color bc1, big_color bc2, int size)
{
  if(bc1.fix != bc2.fix)
    return 0;
  else {
    int i;
    for(i=0 ; i<size ; i++)
      if(bc1.mult[i] != bc2.mult[i])
	return 0;
    return 1;
  }
}


void free_graph(graph G)
{
  int i;
  for(i=0 ; i<G.size ; i++)
    free_list(G.neighbors[i]);
  free(G.neighbors);
}
