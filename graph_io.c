
#include "graph_io.h"


list lecture_ligne(FILE *file)
//-----To read a line of a graph-file and build the neibourhood associated---
{
  int i,j;
  fscanf(file, "%d ",&i);
  if(i>1) {
    list l;
    l=malloc(sizeof(struct cons));
    l->tail=NULL;
    list loc;
    fscanf(file,"%d ",&(l->head));
    for (j=1;j<i-1;j++) {
      loc=malloc(sizeof(struct cons));
      fscanf(file,"%d ",&(loc->head));
      loc->tail=l;
      l=loc;
    }
    loc=malloc(sizeof(struct cons));
    fscanf(file,"%d\n",&(loc->head));
    loc->tail=l;
    l=loc;
    return l;
  }
  else {
    if(i==1) {
      list l;
      l=malloc(sizeof(struct cons));
      l->tail=NULL;
      fscanf(file,"%d\n",&(l->head));
      return l;
    }
  
    else{fscanf(file,"\n");return NULL;}
  }
}



graph graph_from_file(FILE *file)
{
  graph G;
  fscanf(file, "%d\n", &G.size);
  G.neighbors= malloc(G.size*sizeof(list));
  int k;
  for (k=0 ; k<G.size ; k++) {
    G.neighbors[k] = lecture_ligne(file);
  }

  return G;
}




void fast_print_graph(graph G) 
{
  int size = G.size;
  printf("size: %d\n", size);
  int i;
  for(i=0 ; i<size ; i++) {
    printf("%d: ", i);
    list neighbors = G.neighbors[i];
    while(neighbors != NULL) {
      printf("%d, ", neighbors->head);
      neighbors = neighbors->tail;
    }
    printf("\n");
  }

}
