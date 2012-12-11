
#include "isomorphism.h"



int find_contradiction(graph G1, graph G2, int *iso, int *iso_inv, int vertex)
// find if the new matching vertex -> iso(vertex) leads to a contradiction : if contradictions found return 1 else 0
{
  int size = G1.size;
  int *edges1 = malloc(size*sizeof(int));
  int *edges2 = malloc(size*sizeof(int));
  int i;
  
  for(i=0 ; i<size ; i++)
  {
    edges1[i] = 0;
    edges2[i] = 0;
  }

  list neighbors = G1.neighbors[vertex];
  while(neighbors != NULL)
  {
    if(iso[neighbors->head] != -1)
      edges1[neighbors->head] = 1;
    neighbors = neighbors->tail;
  }
  neighbors = G2.neighbors[iso[vertex]];
  while(neighbors != NULL)
  {    
    if(iso_inv[neighbors->head] != -1)
      edges2[iso_inv[neighbors->head]] = 1;
    neighbors = neighbors->tail;
  }

  for(i=0 ; i<size ; i++)
    if(edges1[i] != edges2[i])
    {
      free(edges1);
      free(edges2);
      return 1; // the given isomorphism leads to a contradiction
    }      

  free(edges1);
  free(edges2);
  return 0; // the given isomorphism is correct for now

}

int vertex_to_match(int *colors1, int *iso, int *V, int size)
{
  int vertex = -1;
  int i;
  int colormin = size+1;

  for(i=0 ; i<size ; i++)
  {
    if((iso[i] == -1) && (V[colors1[i]] < colormin))
    {
      vertex = i;
      colormin = V[colors1[i]];
    }
  }

  return vertex;
}






int weisfeiler_lehman1(graph G1, graph G2, int *iso)
{

  int size = G1.size;
  if(size != G2.size)
  {    // printf("different number of vertices ! STOP NOW !\n");
    return 0;
  }
  
  int edges1 = 0;
  int edges2 = 0;
  int i, j;
  for(i=0 ; i<size ; i++)
  {
    list neighbors = G1.neighbors[i];
    while(neighbors != NULL)
    {
      edges1++;
      neighbors = neighbors->tail;
    }
    neighbors = G2.neighbors[i];
    while(neighbors != NULL)
    {
      edges2++;
      neighbors = neighbors->tail;
    }
  }
  if(edges1 != edges2)
  {      // printf("different number of edges ! STOP NOW !\n");
    return 0;
  }

  int *iso_inv = malloc(size*sizeof(int));

  int *colors1 = malloc(size*sizeof(int));
  int *colors2 = malloc(size*sizeof(int));
  big_color *bc1 = malloc(size*sizeof(big_color));
  big_color *bc2 = malloc(size*sizeof(big_color));
  int *V = malloc(size*sizeof(int)); // gives the number of UNMATCHED vertices for each color (in G1)
  int stable = 0; // this boolean gets TRUE (1) if the coloration is stable

  int matched = 0; // number of matched vertices with the isomorphism 'iso'
  int *stack = malloc(size*sizeof(int)); // this stack contains the vertices matched with 'iso' ('matched' is the stack pointer)
  int **history = malloc(size*sizeof(int*));;
  // initialization
  for(i=0 ; i<size ; i++)
  {
    iso[i] = -1;
    iso_inv[i] = -1;
    colors1[i] = 0;
    colors2[i] = 0;
    for(j=0 ; j<size ; j++)
    {
      bc1[j] = new_big_color(size);
      bc2[j] = new_big_color(size);
    }
    V[i] = 0;
    stack[i] = -1;
    history[i] = malloc(size*sizeof(int));
    for(j=0 ; j<size ; j++)
      history[i][j] = -1;
  }
  V[0] = size;

  int vertex, vertex_img;
  int loop_counter = 0;


  while((matched >= 0) && (matched < size))
    {       // printf("%d\n", loop_counter); loop_counter++;

    vertex = vertex_to_match(colors1, iso, V, size);
    if((!stable) && (V[colors1[vertex]] > 1)) // coloration step
    {
      refine_coloration(G1, colors1, bc1);
      refine_coloration(G2, colors2, bc2);
      int flag = match_colors(bc1, bc2, colors1, colors2, iso, V, size);
      if(flag == 0)
      {        // printf("colorations prouve that G1 and G2 are not isomorph ! STOP NOW !\n");
        matched = -1;
        break; // G1 and G2 are not isomorph, that is sure and we stop now !
      }
      if(flag == 2)
	stable = 1;
      vertex = vertex_to_match(colors1, iso, V, size);
    }
              // printf("trying to match %d\n", vertex);
    for(i=history[matched][vertex]+1 ; i<size ; i++)
      if((iso_inv[i] == -1) && (colors2[i]  == colors1[vertex]))
      {
        vertex_img = i;
        break;
      }

    if(i == size) // no possibility for 'vertex' : it's time to backtrack !
    {            // printf("no more possibility for matching %d\n", vertex);
      for(j=0 ; j<size ; j++)
        history[matched][j] = -1; // cleaning history
      matched--;
      if(matched == -1)
        break;
      else
      {       // printf("<- %d(%d)\n", stack[matched], iso[stack[matched]]);
        iso_inv[iso[stack[matched]]] = -1;
        iso[stack[matched]] = -1;
        V[colors1[stack[matched]]]++;
        stack[matched] = -1;
      }
    }

    else // 'vertex' (in G1) and 'vertex_img' (in G2) have same color
    {          // printf("matching %d with %d ? ...   ", vertex, vertex_img);
      iso[vertex] = vertex_img;
      iso_inv[vertex_img] = vertex;
      if(find_contradiction(G1, G2, iso, iso_inv, vertex)) // but 'vertex' -> 'vertex_img' leads to a contradiction
      {          // printf("sorry, there is a contradiction !\n");
        iso[vertex] = -1;
        iso_inv[vertex_img] = -1;
        history[matched][vertex] = vertex_img;
      }
      else // for now, 'vertex' -> 'vertex_img' is OK. So, assume iso(vertex)=vertex_img
      {     // printf("ok, no contradiction for now !\n-> %d(%d)\n", vertex, vertex_img);
	V[colors1[vertex]]--;
	history[matched][vertex] = vertex_img;
	stack[matched] = vertex;
	matched++;
      }
    }

  }


  free(iso_inv);
  free(colors1);
  free(colors2);
  for(i=0 ; i<size ; i++)
  {
    delete_big_color(bc1[i]);
    delete_big_color(bc2[i]);
  }
  free(bc1);
  free(bc2);
  free(V);
  free(stack);
  for(i=0 ; i<size ; i++)
    free(history[i]);
  free(history);

  return (matched == size);

}





int isomorphism_naive(graph G1, graph G2, int *iso)
{
  int size = G1.size;
  if(size != G2.size)
    return 0;

  int *iso_inv = malloc(size*sizeof(int));
  int i;
  for(i=0 ; i<size ; i++)
  {
    iso[i] = -1;
    iso_inv[i] = -1;
  }

  int vertex = 0;

  while((vertex>=0) && (vertex<size))
  {
    do
      iso[vertex]++;
    while((iso[vertex] < size) && (iso_inv[iso[vertex]] != -1));

    if(iso[vertex] == size)
    { //if(vertex>=1) printf("<- %d(%d)\n", vertex-1, iso[vertex-1]); else printf("STOP !\n"); 
      iso[vertex] = -1;
      vertex--;
      if(vertex >= 0) iso_inv[iso[vertex]] = -1;
    }
    else
    { //printf("trying %d(%d) ...   ", vertex, iso[vertex]);
      iso_inv[iso[vertex]] = vertex;
      if(find_contradiction(G1, G2, iso, iso_inv, vertex))
      { //printf("no !\n");
        iso_inv[iso[vertex]] = -1;
      }
      else
      { //printf("yes !\n-> %d(%d)\n", vertex, iso[vertex]);
	vertex++;
      }  
    }
  }

  free(iso_inv);

  return (vertex == size);

}





































