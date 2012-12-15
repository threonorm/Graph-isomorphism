
#include "isomorphism.h"



int find_contradiction(graph G1, graph G2, int *iso, int *iso_inv, int vertex)
// find if the new matching vertex -> iso(vertex) leads to a contradiction : if contradictions found return 1 else 0
{
  int size = G1.size;
  int *edges1 = malloc(size*sizeof(int));
  int *edges2 = malloc(size*sizeof(int));
  int i;
  
  for(i=0 ; i<size ; i++) {
    edges1[i] = 0;
    edges2[i] = 0;
  }

  list neighbors = G1.neighbors[vertex];
  while(neighbors != NULL) {
    if(iso[neighbors->head] != -1)
      edges1[neighbors->head] = 1;
    neighbors = neighbors->tail;
  }
  neighbors = G2.neighbors[iso[vertex]];
  while(neighbors != NULL) {    
    if(iso_inv[neighbors->head] != -1)
      edges2[iso_inv[neighbors->head]] = 1;
    neighbors = neighbors->tail;
  }

  for(i=0 ; i<size ; i++)
    if(edges1[i] != edges2[i]) {
      free(edges1);
      free(edges2);
      return 1; // the given isomorphism leads to a contradiction
    }      

  free(edges1);
  free(edges2);
  return 0; // the given isomorphism is correct for now

}



int vertex_to_match(graph G1, int *colors1, int *iso, int *V, int *vertex, int size)
// stores in vertex which vertex seems to be the easiest to match, returns 1 if it is the only one in this color, 0 otherwise 
{
  *vertex = -1;
  int i;
  int *V2 = malloc(size*sizeof(int)); // number of FREE vertices for each color
  for(i=0 ; i<size ; i++)
    V2[i] = 0;

  for(i=0 ; i<size ; i++)
    if(iso[i] == -1)
      V2[colors1[i]]++;

  int colormin = size+1;

  for(i=0 ; i<size ; i++)  {
    if((iso[i] == -1) && (V2[colors1[i]] < colormin)) {
      *vertex = i;
      colormin = V2[colors1[i]];
    }
  }
  int flag = (V2[colors1[*vertex]] == 1);
  free(V2);

  return flag;

}






int weisfeiler_lehman1(graph G1, graph G2, int *iso)
{
  int i, j;

  // G1 and G2 must have the same number of vertices
  int size = G1.size;
  if(size != G2.size) {  
    return 0;
  }
  
  // G1 and G2 must have the same number of edges
  int edges1 = 0;
  int edges2 = 0;
  for(i=0 ; i<size ; i++) {
    list neighbors = G1.neighbors[i];
    while(neighbors != NULL) {
      edges1++;
      neighbors = neighbors->tail;
    }
    neighbors = G2.neighbors[i];
    while(neighbors != NULL) {
      edges2++;
      neighbors = neighbors->tail;
    }
  }
  if(edges1 != edges2) {
    return 0;
  }

  // this vars and tables will be important for the main loop of this algorithm. (don't forget to free() :p )

  // the reciprocical isomorphism. usefull to keep it in memory
  int *iso_inv = malloc(size*sizeof(int));

  // the color (between 0 and size-1) for each vertex in G1 and G2
  int *colors1 = malloc(size*sizeof(int));
  int *colors2 = malloc(size*sizeof(int));

  // the big_colors for each vertex in G1 and G2 after a coloration step. direct translated into int with 'match_colors'
  big_color *bc1 = malloc(size*sizeof(big_color));
  big_color *bc2 = malloc(size*sizeof(big_color));

  // contains the number of vertices for each color (in G1)
  int *V = malloc(size*sizeof(int));

  // this boolean gets true when the coloration becomes stable
  int stable = 0;

  // number of matched vertices by 'iso'. also used as stack pointer in our backtracking main loop
  int matched = 0;

  // this stack contains the vertices chronologically matched by 'iso'
  int *stack = malloc(size*sizeof(int));

  // a table used as history for the backtracking. history[i] (for 0<=i<=matched) contains for each vertex in G1 the last candidate image in G2 tested before, at this step
  // so keep more information in memory about what we have already tested than the algo described in the paper (but erasing history[matched] when backtracking also keep time !
  int **history = malloc(size*sizeof(int*));;

  // receives the easiest vertex in G1 to match (see 'vertex_to_match') and the candidate image for it in G2
  int vertex, vertex_img; 

  // initialization loop
  for(i=0 ; i<size ; i++) {
    iso[i] = -1;
    iso_inv[i] = -1;
    colors1[i] = 0;
    colors2[i] = 0;
    bc1[i] = new_big_color(size);
    bc2[i] = new_big_color(size);
    V[i] = 0;
    stack[i] = -1;
    history[i] = malloc(size*sizeof(int));
    for(j=0 ; j<size ; j++)
      history[i][j] = -1;
  }
  V[0] = size;

  
  // the main loop of the weisfeiler-lehman heuristic.
  // Contrary to what was proposed in the paper, we have chosen an iterative method,
  // so we can do more checks and detect more contradictions and easily backtrack an arbitrary number of steps in case of contradiction.

  while((matched >= 0) && (matched < size)) {


    int match_flag  = vertex_to_match(G1, colors1, iso, V, &vertex, size);

    
    if((!stable) && (match_flag==0)) { // there is no free vertex alone in its color --> coloration step now !

      refine_coloration(G1, colors1, bc1);
      refine_coloration(G2, colors2, bc2);
      int flag = match_colors(bc1, bc2, colors1, colors2, iso, V, size);
      if(flag == 0) { 
        matched = -1;
        break; // G1 and G2 are not isomorph, that is sure and we stop now !
      }
      if(flag == 2)
	stable = 1;

      int errmin; // finds the possible first error in 'iso' detected by the new coloration
      for(errmin=0 ; errmin<matched ; errmin++)
	if(colors1[stack[errmin]] != colors2[iso[stack[errmin]]])
	  break;
      if(errmin < matched) { // a previous matching in 'iso' is no proved uncorrect !!
	for(i=matched-1 ; i>=errmin ; i--) {
	  for(j=0 ; j<size ; j++)
	    history[i+1][j] = -1; // cleaning history
	  iso_inv[iso[stack[i]]] = -1;
	  iso[stack[i]] = -1;
	  stack[i] = -1;
	}
	matched = errmin; // we have erased all choices made after the false matching
      }

      // after this new coloration, we determine the now easiest vertex to find
      vertex_to_match(G1, colors1, iso, V, &vertex, size);
    }
     
    // find next candidate image for 'vertex' in G2
    for(i=history[matched][vertex]+1 ; i<size ; i++)
      if((iso_inv[i] == -1) && (colors2[i]  == colors1[vertex])) {
        vertex_img = i;
        break;
      }

    if(i == size) { // no more possibility for 'vertex' : it's time to backtrack !!
      for(j=0 ; j<size ; j++)
        history[matched][j] = -1; // cleaning history
      matched--;
      if(matched == -1)
        break;
      else {       
        iso_inv[iso[stack[matched]]] = -1;
        iso[stack[matched]] = -1;
        stack[matched] = -1;
      }
    }

    else { // 'vertex' (in G1) and 'vertex_img' (in G2) have same color
      iso[vertex] = vertex_img;
      iso_inv[vertex_img] = vertex;
      if(find_contradiction(G1, G2, iso, iso_inv, vertex)) { // but 'vertex' -> 'vertex_img' leads to a contradiction
        iso[vertex] = -1;
        iso_inv[vertex_img] = -1;
        history[matched][vertex] = vertex_img; // storing this negative test in history
      }
      else { // for now, 'vertex' -> 'vertex_img' is OK. So, assume iso(vertex)=vertex_img
	history[matched][vertex] = vertex_img; // storing this possibility in history (it will be usefull if later we backtrack :) )
	stack[matched] = vertex;
	matched++;
      }
    }


  }



  free(iso_inv);
  free(colors1);
  free(colors2);
  for(i=0 ; i<size ; i++) {
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




// a very simple and naive backtracking algorithm
// we just try to match vertex 0 in G1, the vertex 1, vertex 2, etc...
// and backtrack in case of contradiction

int isomorphism_naive(graph G1, graph G2, int *iso) 
{
  int size = G1.size;
  if(size != G2.size)
    return 0;

  int *iso_inv = malloc(size*sizeof(int));
  int i;
  for(i=0 ; i<size ; i++) {
    iso[i] = -1;
    iso_inv[i] = -1;
  }

  int vertex = 0;

  while((vertex>=0) && (vertex<size)) {
    do
      iso[vertex]++;
    while((iso[vertex] < size) && (iso_inv[iso[vertex]] != -1));

    if(iso[vertex] == size) { 
      iso[vertex] = -1;
      vertex--;
      if(vertex >= 0) iso_inv[iso[vertex]] = -1;
    }
    else {
      iso_inv[iso[vertex]] = vertex;
      if(find_contradiction(G1, G2, iso, iso_inv, vertex)) 
        iso_inv[iso[vertex]] = -1;
      else
	vertex++;
    }
  }

  free(iso_inv);

  return (vertex == size);

}





int iso_check(graph G1, graph G2, int *iso)
{
  int size = G1.size;
  if(size != G2.size)
    return 0;

  int i, j;

  for(i=0 ; i<size ; i++) {
    for(j=0 ; j<size ; j++)
      if(iso[j] == i)
	break;
    if(j == size)
      return 0;
  }

  int *edges1 = malloc(size*sizeof(int));
  int *edges2 = malloc(size*sizeof(int));

  for(i=0 ; i<size ; i++) {

    for(j=0 ; j<size ; j++) {
      edges1[j] = 0;
      edges2[j] = 0;
    }

    list neighbors = G1.neighbors[i];
    while(neighbors != NULL) {
      edges1[neighbors->head] = 1;
      neighbors = neighbors->tail;
    }
    neighbors = G2.neighbors[iso[i]];
    while(neighbors != NULL) {
      edges2[neighbors->head] = 1;
      neighbors = neighbors->tail;
    }

    for(j=0 ; j<size ; j++)
      if(edges1[j] != edges2[iso[j]]) {
	free(edges1);
	free(edges2);
	return 0;
      }

  }

  free(edges1);
  free(edges2);

  return 1;

}
