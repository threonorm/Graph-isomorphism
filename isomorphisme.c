#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct cons
{
  int head;
  struct cons *tail;
};

typedef struct cons* list; // the empty list is the NULL pointer

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

list lecture_ligne(FILE* graph)
//-----To read a line of a graph-file and build the neibourhood associated---
{ 
  int i,j;
  fscanf(graph, "%d ",&i);
  if(i>0)
  {
  list l;
  l=malloc(sizeof(struct cons));
  l->tail=NULL;
  list loc;
  for (j=0;j<i-1;j++)
  {
    loc=malloc(sizeof(struct cons));
    fscanf(graph,"%d ",&(loc->head));
    loc->tail=l;
    l=loc;
  }
  fscanf(graph,"%d\n",&(l->head));
  return l;
  }
  else{return NULL;}
}



int main(int argc,char *argv[])
{
  int *x;
  tt y;
  y = x;
  //-------To open files, and verify there are in arguments of the call---
  FILE* graph1= NULL;
  FILE* graph2=NULL;
  if(argc<3){printf("Not enough arguments"); return 1;}
  graph1=fopen(argv[1],"r+");
  graph2=fopen(argv[2],"r+");
  //------- To read the first graph line after line.------
  
  struct graph G1;
  fscanf(graph1, "%d\n", &G1.size);
  G1.neighbors= malloc(G1.size*sizeof(list));
  int k;
  for (k=0;k<G1.size;k++)
  {
      G1.neighbors[k]=lecture_ligne(graph1);
  }
  
  //------ To read the second graph, line after line.-----
  
  struct graph G2;
  fscanf(graph2, "%d\n", &G2.size);
  G2.neighbors= malloc(G2.size*sizeof(list));
  for (k=0;k<G2.size;k++)
  {
    G2.neighbors[k]=lecture_ligne(graph2);
  }

  //----- Try to build the isomorphism--------------
  



  //------To free memory and to close files----
  for(k=0;k<G1.size;k++)
  {
      free_list(G1.neighbors[k]);
  }
  for(k=0;k<G2.size;k++)
  {
      free_list(G2.neighbors[k]);
  }
  free(G1.neighbors);
  free(G2.neighbors);
  fclose(graph1);
  fclose(graph2);
  return 0;
}
