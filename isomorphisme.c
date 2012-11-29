#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//For all vertex, associate in the step k,an array color of length n, which contains
//in color[i] the number of repetition of color i, in the coloration f_k
//TODO: Stable coloration 
//I'm prefering using a sparse structure, with list. It is less costly in
//memory


int size;
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

//    int tabl[size]; tableau de taille n, contient le nombre de répétition de chaque couleur
struct graph
{
    struct list lsommet;
    struct graph *next;
};

    //Possedant un coloriage à l'ordre k on veut colorier à k+1
    //un coloriage c'est un tableau de taille nombre de sommets, ou a
    //chaque case on met une la couleur (généralisée du sommet)
    //On rajoute donc comme couleur le multiensemble des couleurs
    //Ensuite on renomme les couleurs dans {1,n}
int* new_coloration (int **color)
{
}
int test_color (int *color1, int *color2)
{
    int i;
    int res=1;
    for(i=0;i<size;i++)
    {
        if(color1[i]!=color2[i]){res=0;} 
    }
    return res;
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
