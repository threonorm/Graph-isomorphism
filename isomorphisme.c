#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct cons
{
  int head;
  struct cons *tail;
};

typedef struct cons* list; // the empty list is the NULL pointer

struct graph
{
  int size;
  list *neighbors;
};


struct big_color
{
  int x;
  int *y;
};


struct big_color new_big_color(int size)
{
  struct big_color bc;
  bc.y = malloc(size*sizeof(int));
  int i;
  for(i=0;i<size;i++)
    bc.y[i] = 0;
  return bc;
}


void delete_big_color(struct big_color bc)
{
  free(bc.y);
};


int comp_big_color(struct big_color bc1, struct big_color bc2, int size)
{
  if(bc1.x != bc2.x)
    return 0;
  else
  {
    int i;
    for(i=0 ; i<size ; i++)
      if(bc1.y[i] != bc2.y[i])
	return 0;
    return 1;
  }
}


int *new_coloration(struct graph G, int *old_colors)
{
  struct big_color *bc = malloc(G.size*sizeof(struct big_color));
  int i = 0;

  for(i=0 ; i<G.size ; i++)
  {
    bc[i].x = old_colors[i];
    list neighbors = G.neighbors[i];
    while(neighbors != NULL)
    {
      bc[i].y[old_colors[neighbors->head]]++;
      neighbors = neighbors->tail;
    }
  }

  // on doit maintenant réordonner le big_colors de sorte à se ramener à un intervalle 0..n-1
  // le recoloriage doit être unique pour pouvoir tester la stabilité du coloriage
  // on prend la convention suivante : les couleurs font leur apparition en ordre croissant pour les sommets 0..n-1

  int *new_colors = malloc(G.size*sizeof(int));
  for(i=0 ; i<G.size ; i++)
    new_colors[i] = -1; // par défaut
  int max_color = -1;
  for(i=0 ; i<G.size ; i++)
  {
    int j;
    for(j=0 ; j<i ; j++)
      if(comp_big_color(bc[i],bc[j],G.size))
      {
	new_colors[i] = new_colors[j];
	break;
      }
    if(new_colors[i] = -1) // on n'a pas trouvé de sommets avant avec la même couleur
      new_colors[i] = (++max_color); // on lui donne une couleur pas encore attribuée
  }


  // on libère l'espace mémoire utilisé par les big_colors
  for(i=0 ; i<G.size ; i++)
    delete_big_color(bc[i]);


  return new_colors;

 
}











typedef int* tt;





int main()
{
  int *x;
  tt y;
  y = x;
  return 0;
}