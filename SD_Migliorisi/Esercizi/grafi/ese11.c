/*
Siano G e H due grafi orientati pesati entrambi con pesi positivi, di n vertici 0,1,…, n-1. H
rappresentato con matrice di adiacenza e G rappresentato con liste di adiacenza utilizzando
la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C una funzione che, presi in input i due grafi G e H,
a. verifichi che i due grafi siano alberi
b. indipendentemente da a, restituisca G con i pesi dei suoi archi diminuiti dei pesi degli
archi corrispondenti in H. Se un arco ottiene peso minore di 10, l’arco deve essere 
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

            for(i=0;i<nv;i++)
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

void dfs1(grafo *g, int i, int *aux)
{
    arco *e;
    aux[i]=1;

    for(e=g->adj[i]; e; e=e->next)
    {
        if(!aux[e->key])
        {
            printf("%d, ", e->key);
            dfs1(g,e->key,aux);
        }
    }
}

void dfs(grafo *g)
{
    int i;
    int  *aux=calloc(g->nv,sizeof(int));

    if(!aux)
    {
        printf("Errore di allocazione\n");
    }
    else
    {
        for(i=0; i<g->nv; i++)
        {
            if(!aux[i])
            {
                printf("%d , ",i);
                dfs1(g,i,aux);
            }
        }
        free(aux);
    }
}

bool is_tree(grafo *g)
{
    int *in_degrees=(int *)calloc(g->nv,sizeof(int));
    int root_count=0;
    int root=-1;

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            in_degrees[e->key]++;
            e=e->next;
        }
    }

    for(int i=0; i<g->nv; i++)
    {
        if(in_degrees[i]==0)
        {
            root_count++;
            root=i;
        }
    }

    if(root_count!=1)
    {
        free(in_degrees);
        return false;
    }

    int *visited=(int *)calloc(g->nv,sizeof(int));
    dfs(g);
    dfs1(g,root,visited);

    for(int i=0; i<g->nv; i++)
    {
        if(!visited[i])
        {
            free(in_degrees);
            free(visited);
            return false;
        }
    }

    free(in_degrees);
    free(visited);

    return true;
}

int main()
{
    grafo *g=NULL;

    g=new_elem(5);

    aggiungi_arco(g,0,1,1);
    aggiungi_arco(g,0,2,1);
    aggiungi_arco(g,1,3,1);
    aggiungi_arco(g,2,4,1);

    printf("STAMPO IL GRAFO G: \n");
    stampa_grafo(g);

    printf("\n");

    bool is_g_tree=is_tree(g);

    if(is_g_tree)
    {
        printf("Il grafo G è un albero.\n");
    }
    else
    {
        printf("Il grafo G non è un albero.\n");
    }
}