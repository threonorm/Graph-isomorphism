
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdlib.h>


// list types

typedef
struct cons
{
  int head;
  struct cons *tail;
}
cons;

typedef cons* list; // the empty list is the NULL pointer


// basic list operations

int free_list(list l);

list pop(list l);

list push(int n, list l);


// big_color, used for coloration refinement. 'fix' contains the old color, and 'mult' is the multiset

typedef
struct big_color
{
  int fix; // the color of the vertex itself
  int *mult; // the multiset
}
big_color;


// basic operations on big_colors

big_color new_big_color(int size);

void delete_big_color(big_color bc);

int comp_big_colors(big_color bc1, big_color bc2, int size); // bc1==bc2


// data structure for a graph. 'size' is the number of vertices and 'neighbors[vertex]' is the adjacency list for 'vertex'

typedef
struct graph
{
  int size;
  list *neighbors;
}
graph;


void free_graph(graph G);


#endif
