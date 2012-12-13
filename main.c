#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "colors.h"
#include "isomorphism.h"



graph fast_graph_maker(int *tab, int size)
{
  graph G;
  G.size = size;
  G.neighbors = malloc(size*sizeof(list));
  int i;
  for(i=0 ; i<size ; i++)
    G.neighbors[i] = NULL;
  for(i=0 ; i<size*size ; i++)
    if(tab[i])
      G.neighbors[i/size] = push(i%size, G.neighbors[i/size]);
  return G;
}

void fast_print_graph(graph G)
{
  int size = G.size;
  printf("size: %d\n", size);
  int i;
  for(i=0 ; i<size ; i++)
  {
    printf("%d: ", i);
    list neighbors = G.neighbors[i];
    while(neighbors != NULL)
    {
      printf("%d, ", neighbors->head);
      neighbors = neighbors->tail;
    }
    printf("\n");
  }
}




int main(int argc,char *argv[])
{
  int i;
  
   //-------To open files, and verify there are in arguments of the call---
  FILE* graph1= NULL;
  FILE* graph2=NULL;
  if(argc<3){printf("Not enough arguments"); return 1;}
  graph1=fopen(argv[1],"r+");
  graph2=fopen(argv[2],"r+");
  //------- To read the first graph line after line.------
  
  graph G1;
  fscanf(graph1, "%d\n", &G1.size);
  G1.neighbors= malloc(G1.size*sizeof(list));
  int k;
  for (k=0;k<G1.size;k++)
  {
      G1.neighbors[k]=lecture_ligne(graph1);
  }
  
  //------ To read the second graph, line after line.-----
  
  graph G2;
  fscanf(graph2, "%d\n", &G2.size);
  G2.neighbors= malloc(G2.size*sizeof(list));
  for (k=0;k<G2.size;k++)
  {
    G2.neighbors[k]=lecture_ligne(graph2);
  }
  //----- Try to build the isomorphism--------------
//  fast_print_graph(G1); 
 // fast_print_graph(G2);
  int size=G1.size;
 // printf("\n\n");
 // printf("\n-----------\n\n");
  int *iso = malloc(size*sizeof(int));
  clock_t uptime = clock() / (CLOCKS_PER_SEC / 1000);
  int flag = weisfeiler_lehman1(G1, G2, iso);
  clock_t downtime= clock()/ (CLOCKS_PER_SEC /1000);
  printf("%d %2.1f\n",flag,(double)(downtime-uptime));
  //for(i=0 ; i<size ; i++) printf("%d ", iso[i]); printf("\n\n");
  //flag = isomorphism_naive(G1, G2, iso);
  //printf("-----%d-----\n", flag);
  //for(i=0 ; i<size ; i++) printf("%d ", iso[i]); printf("\n\n");
 
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
