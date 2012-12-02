#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//I'm prefering using a sparse structure, with list. It is less costly in
//memory

//Size is a global variable representing the max degree of graphs. 

//-----------Global variables---------------
int size;



//----------------Data structures---------------
struct list
{
    int elem;
    struct list* next;
};


struct graph
{
    struct list lsommet;
    struct graph *next;
};


//-------------Basic functions--------------

int i_of_list(int i,struct list *l)
//To access to the i-th element of a list l
{
    int j;
    struct list *lres=l;
    for(j=0;j<i;j++)
    {
        l= l->next;
    }
    return (l->elem);
}

struct list acces(struct graph *graphentree, int i)
//Basic function to have the neighbourhood of the vertex i.
{
  int j;
  struct graph *aux=graphentree;
  for(j=0;j<i;j++)
  {
          aux = aux->next;
  }
  return aux->lsommet;
}

//Todo : A function that renumerate colors.

int* renumerate_color (struct graph g1,int **color_old)
{

}

int* new_coloration_vertex (struct graph g1,int **color_old,int i)
//Find the new color of vertex i.
{
    struct list sommets;
    int *color_i=NULL;
    color_i=malloc(sizeof(int)*size);
    sommets= acces(&g1,i);
    //Remark: It's costly, always polynomial, but this step cost about n^2
    int j;
    int k;
    while(sommets.next !=NULL)
    {
        for(k=0;k<size;k++)
        {color_i[j]=color_i[j]+color_old[k][j];}
    }
}


int test_color (int *color1, int *color2)
//Equality for colors
{
    int i;
    int res=1;
    for(i=0;i<size;i++)
    {
        if(color1[i]!=color2[i]){res=0;} 
    }
    return res;
}


//---------------Body-------------

int main(int argc, char *argv[])
{
    int n_vertex1;
    int n_edge1;
    int n_vertex2;
    int n_edge2;
    FILE* graph1= NULL;
    FILE* graph2=NULL;
    if(argc<=3){printf("Not enough arguments"); return 1;}
    graph1=fopen(argv[1],"r+");
    graph2=fopen(argv[2],"r+");
    //Build the isomorphism when it is possible.
    fclose(graph1);
    fclose(graph2);
    return 0;
}
