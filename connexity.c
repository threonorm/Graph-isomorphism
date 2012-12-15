
#include "connexity.h"


int DFS(graph G, int vertex, int no, int *table)
// returns the size of the connex comp
{
  table[vertex] = no;
  int res = 1;
  list neighbors = G.neighbors[vertex];
  while(neighbors != NULL)  {
    if(table[neighbors->head] == 0)
      res += DFS(G, neighbors->head, no, table);
    neighbors = neighbors->tail;
  }
  return res;
}


int connexity(graph G, int *cards)
// at the ends, cards[i] = number of connex comp with size = i+1
{
  int size = G.size;
  int *table = malloc(size*sizeof(int));
  int i;
  for(i=0 ; i<size ; i++) {
    cards[i] = 0;
    table[i] = 0;
  }
  int no = 0;

  for(i=0 ; i<size ; i++)
    if(table[i] == 0) {
      no++;
      int n = DFS(G, i, no, table);
      cards[n-1]++;
    }

  free(table);
  return no;
}



void study_connexity(graph G)
{
  int size = G.size;
  int edges = 0;
  int i;
  for(i=0 ; i<size ; i++) {
    list neighbors = G.neighbors[i];
    while(neighbors != NULL) {
      edges++;
      neighbors = neighbors->tail;
    }
  }

  printf("number of vertices: %d\n", size);
  printf("number of edges: %d\n", edges/2);

  int *cards = malloc(size*sizeof(int));
  int nb_comp_connex = connexity(G, cards);
  printf("number of connected components: %d\n", nb_comp_connex);

  for(i=0 ; i<size ; i++)
    if(cards[i] > 0)
      printf("%d: %d\n", i+1, cards[i]);
  free(cards);
}
