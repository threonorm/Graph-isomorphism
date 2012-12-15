
#include "graph_gen.h"


graph matrix_to_graph(int **matrix, int size)
{
  graph G;
  G.size = size;
  G.neighbors = malloc(size*sizeof(list));

  int i, j;

  for(i=0 ; i<size ; i++) {
    G.neighbors[i] = NULL;
    for(j=0 ; j<size ; j++)
      if(matrix[i][j] == 1)
	G.neighbors[i] = push(j, G.neighbors[i]);
  }

  return G;
}



int *rand_permut(int n)
{
  int *permut = malloc(n*sizeof(int));
  int i, j;
  int random;
  for(i=0 ; i<n ; i++)
    permut[i] = -1;
  for(i=0 ; i<n ; i++) {
    random = rand() % (n-i);
    j = 0;
    while(1) {
      if(permut[j] != -1)
        j++;
      else if(random == 0) {
        permut[j] = i;
        break;
      }
      else {
        j++;
        random--;
      }
    }
  }

  return permut;
}



graph permut_graph(graph G1, int *permut)
{
  int size = G1.size;
  graph G2;
  G2.size = G1.size;
  G2.neighbors = malloc(size*sizeof(list));
  int i;
  for(i=0 ; i<size ; i++) {
    G2.neighbors[permut[i]] = NULL;
    list neighbors = G1.neighbors[i];
    while(neighbors != NULL) {
      G2.neighbors[permut[i]] = push(permut[neighbors->head], G2.neighbors[permut[i]]);
      neighbors = neighbors->tail;
    }
  }

  return G2;
}




graph rand_connected_graph(int size, int edges)
{

  assert((edges>=size-1) && (edges<=size*(size-1)/2));

  int i, j;

  int **matrix = malloc(size*sizeof(int*));
  for(i=0 ; i<size ; i++) {
    matrix[i] = malloc(size*sizeof(int));
    for(j=0 ; j<size ; j++)
      matrix[i][j] = 0;
  }

  for(i=1 ; i<size ; i++) {
    int random = rand() % i;
    matrix[i][random] = 1;
    matrix[random][i] = 1;
    edges--;
  }

  int free_edges = size*(size-1)/2 - (size-1);

  while(edges > 0) {

    int random = rand() % free_edges;
    int flag = 1;
    for(i=0 ; i<size ; i++)
      for(j=0 ; j<i ; j++)
	if((flag) && (matrix[i][j] == 0))
	  if(random == 0) {
	    matrix[i][j] = 1;
	    matrix[j][i] = 1;
	    free_edges--;
	    edges--;
	    flag = 0;
	  }
	  else if(flag)
	    random--;
  }

  graph G0 = matrix_to_graph(matrix, size);

  int *permut = rand_permut(size);
  graph G = permut_graph(G0, permut);

  free(permut);
  for(i=0 ; i<size ; i++)
    free(matrix[i]);
  free(matrix);
  free_graph(G0);

  return G;

}




