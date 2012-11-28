#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//For all vertex, associate in the step k,an array color of length n, which contains
//in color[i] the number of repetition of color i, in the coloration f_k
//TODO: Stable coloration 
//I'm prefering using a sparse structure, with list. It is less costly in
//memory
struct pii
{
    int a;
    int b;
};

struct list
{
    int elem;
    struct list* next;
};

struct isomorph
{
    struct list pii;
};
typedef struct color color;
struct color
{
    int n;
    struct list l[];
};

struct graph
{
    struct list lsommet;
    struct graph *next;
};
color* to_color(color *col_init, struct graph graph)
{   
    return col_init;
}

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
