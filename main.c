#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "structs.h"
#include "graph_io.h"
#include "graph_gen.h"
#include "colors.h"
#include "isomorphism.h"
#include "connexity.h"



int main(int argc,char *argv[])
{
  int i;
    
  //-------To open files, and verify there are in arguments of the call---
  FILE* graph1= NULL;
  FILE* graph2=NULL;
  if(argc<3){printf("Not enough arguments"); return 1;}
  graph1=fopen(argv[1],"r+");
  graph2=fopen(argv[2],"r+");

  
  graph G1 = graph_from_file(graph1);  
  graph G2 = graph_from_file(graph2);
  
  
  //----- Try to build the isomorphism--------------

  int size=G1.size;
  
  // erase the upper portion of code and uncomment this if you want to test with random generated conected graph
  /*
  int size = 2000;
  int edges = 4000;

  graph G1 = rand_connected_graph(size, edges);
  int *permut = rand_permut(size);
  graph G2 = permut_graph(G1, permut);
  free(permut);
  study_connexity(G1);
  */



  int *iso = malloc(size*sizeof(int));

  // uncomment this line to have a display of the analysis of the connected components of G1
  // study_connexity(G1); 




  clock_t uptime = clock() / (CLOCKS_PER_SEC / 1000);
  int flag = weisfeiler_lehman1(G1, G2, iso); // use isomorphism_naive if you want to test the naive backtracking algorithm...
  clock_t downtime= clock()/ (CLOCKS_PER_SEC /1000);

  printf("elapsed time: %2.1f\n", (double)(downtime-uptime));
  if(flag) {
    assert(iso_check(G1, G2, iso) == 1);
    printf("the two graphs are isomorph, with the following isomorphism:\n\n[ ");
    for(i=0 ; i<size ; i++) {
      printf("%d->%d", i, iso[i]);
      if(i != size-1)
	printf(" ; ");
    }
    printf(" ]\n\n");
  }
  else
    printf("the two graphs are not isomorph !\n\n");


 
  //------To free memory and to close files----
  
  free(iso);
  free_graph(G1);
  free_graph(G2);
  
  fclose(graph1);
  fclose(graph2);
  return 0;
}
