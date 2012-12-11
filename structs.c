#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


int free_list(list l)
{
    list aux1=l;
    list aux2=l;
    while(aux2 != NULL)
    {
        aux1=aux2->tail;
        free(aux2);
        aux2=aux1;
    }
    return 0;
}


list lecture_ligne(FILE *graph)
//-----To read a line of a graph-file and build the neibourhood associated---
{ 
  int i,j;
  fscanf(graph, "%d ",&i);
  if(i>1)
  {
  list l;
  l=malloc(sizeof(struct cons));
  l->tail=NULL;
  list loc;
  fscanf(graph,"%d ",&(l->head)); 
  for (j=1;j<i-1;j++)
  {
    loc=malloc(sizeof(struct cons));
    fscanf(graph,"%d ",&(loc->head));
    loc->tail=l;
    l=loc;
  }
  loc=malloc(sizeof(struct cons));
  fscanf(graph,"%d\n",&(loc->head));
  loc->tail=l;
  l=loc;
  return l;
  }
  else
  {
  if(i==1)
  {
  list l;
  l=malloc(sizeof(struct cons));
  l->tail=NULL;
  fscanf(graph,"%d\n",&(l->head));
  return l;
  }
  
  else{fscanf(graph,"\n");return NULL;}
  }
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
  else
  {
    int i;
    for(i=0 ; i<size ; i++)
      if(bc1.mult[i] != bc2.mult[i])
	return 0;
    return 1;
  }
}
