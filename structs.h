
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdlib.h>

typedef
struct cons
{
  int head;
  struct cons *tail;
}
cons;

typedef cons* list; // the empty list is the NULL pointer


list pop(list l);

list push(int n, list l);



typedef
struct graph
{
  int size;
  list *neighbors;
}
graph;

typedef
struct big_color
{
  int fix; // the color of the vertex itself
  int *mult; // the multiset
}
big_color;

big_color new_big_color(int size);

void delete_big_color(big_color bc);

int comp_big_colors(big_color bc1, big_color bc2, int size); // bc1==bc2


#endif
