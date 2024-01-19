/*
Sia G un grafo non orientato pesato con pesi positivi, di n vertici 0, 1,…, n-1 e
rappresentato con lista di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C una funzione che preso in input il grafo G,
a. data una coppia di nodi (x,y), identifichi ogni possibile percorso (senza ripetizioni)
di nodi che porta da x a y, ne indichi il costo totale di ogni percorso, e ne rimuova
l’ultimo arco incontrato nel percorso più costoso;
b. dato il percorso meno costoso fra quelli precedentemente riportati, aggiunga un
nuovo nodo w nel grafo e un nuovo arco fra il nodo y il nuovo nodo w.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <stdbool.h>

struct el_arco
{
    int key;
    int peso;
    struct el_arco *next;
};
typedef struct el_arco arco;

struct el_grafo
{
    int nv;
    arco **adj;
};
typedef struct el_grafo grafo;

int is_empty(grafo *g)
{
    return (g==NULL);
}

grafo *new_elem(int nv)
{
    grafo *g;
    int i;

    g=(grafo *)malloc(sizeof(grafo));

    if(g)
    {
        g->adj=(arco **)malloc(nv*sizeof(arco *));

        if(g->adj)
        {
            g->nv=nv;

            for(i=0; i<nv; i++)
            {
                g->adj[i]=NULL;
            }
        }
        else
        {
            printf("Errore di allocazione\n");
            free(g);
            g=NULL;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return g;
}

void aggiungi_arco(grafo *g, int u, int v, int peso)
{
    arco *new;
    arco *e;

    new=(arco *)malloc(sizeof(arco));

    if(new)
    {
        new->key=v;
        new->peso=peso;
        new->next=NULL;

        if(g->adj[u]==NULL)
        {
            g->adj[u]=new;
        }
        else
        {
            e=g->adj[u];

            while(e->next!=NULL)
            {
                e=e->next;
            }

            e->next=new;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }
}

void stampa_grafo(grafo *g)
{
    int i;
    int ne=0;
    arco *e;

    if(!is_empty(g))
    {
        printf("\nIl grafo ha %d vertici",g->nv);

        for(i=0;i<g->nv;i++)
        {
            printf("\nNodi adiacenti al nodo %d -> ", i);
            e=g->adj[i];

            while(e!=NULL)
            {
                printf("%d (peso=%d) - ", e->key,e->peso);
                ne=ne+1;
                e=e->next;
            }
            printf("\n");
        }
        printf("Il grado ha %d archi\n", ne);
    }
}

void print_all_path_util(grafo *g, int u, int v, bool visited[], int path[], int *path_index)
{
    visited[u]=true;
    path[*path_index]=u;
    (*path_index)++;

    if(u==v)
    {
        for(int i=0; i< *path_index; i++)
        {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    else
    {
        for(int i=0; i<g->nv; i++)
        {
            if(!visited[i])
            {
                print_all_path_util(g,i,v,visited,path,path_index);
            }
        }
    }

    (*path_index)--;
    visited[u]=false;
}

void print_all_paths(grafo *g, int u, int v)
{
    bool *visited=(bool *)malloc(g->nv*sizeof(bool));
    int  *path=(int *)malloc(g->nv*sizeof(int));
    int path_index=0;

    for(int i=0; i<g->nv; i++)
    {
        visited[i]=false;
    }

    print_all_path_util(g,u,v,visited,path,&path_index);

    free(visited);
    free(path);
}

int main()
{
    grafo *g=NULL;

    g=new_elem(4);

    printf("INIZIALIZZO E STAMPO IL GRAFO G: \n");

    aggiungi_arco(g,0,1,4);
    aggiungi_arco(g,0,2,3);
    aggiungi_arco(g,0,3,1);
    aggiungi_arco(g,2,0,4);
    aggiungi_arco(g,2,1,5);
    aggiungi_arco(g,1,3,1);

    stampa_grafo(g);

    printf("\n");

    int u=2;
    int v=3;

    printf("\nFOLLOWING ARE ALL DIFFERENT PATHS FORM %d TO %d\n", u,v);

    print_all_paths(g,u,v);
}