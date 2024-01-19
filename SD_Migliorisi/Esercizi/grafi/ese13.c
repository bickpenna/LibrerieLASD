/*
Siano G e H due grafi orientati pesati entrambi con pesi positivi, di n vertici 0, 1,…, n-1 e
rappresentati con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G, *H;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C una funzione che presi in input i due grafi G e H,
a. crei un nuovo grafo T in modo che un arco (a, b) sarà presente in T se l'arco è
presente in G e in H e i loro rispettivi pesi sono entrambi pari o entrambi dispari. Il
peso associato all'arco inserito sarà la somma dei pesi dei due archi nei grafi
corrispondenti.
b. Calcolare il grado incidente e adiacente di G e H.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

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

grafo *crea_grafo_t(grafo *g1, grafo *g2)
{
    grafo *t=new_elem(g1->nv);

    for(int i=0; i<g1->nv; i++)
    {
        arco *e_g1=g1->adj[i];
        arco *e_g2=g2->adj[i];

        while(e_g1!=NULL && e_g2!=NULL)
        {
            if((e_g1->peso%2==0 && e_g2->peso%2==0) || (e_g1->peso%2!=0 && e_g2->peso%2!=0))
            {
                int somma_p=e_g1->peso+e_g2->peso;

                aggiungi_arco(t,i,e_g1->key,somma_p);
            }

            e_g1=e_g1->next;
            e_g2=e_g2->next;
        }
    }

    return t;
}

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    g1=new_elem(6);

    aggiungi_arco(g1,0,1,2);
    aggiungi_arco(g1,0,2,4);
    aggiungi_arco(g1,1,2,1);
    aggiungi_arco(g1,1,3,3);
    aggiungi_arco(g1,2,3,5);
    aggiungi_arco(g1,3,4,2);
    aggiungi_arco(g1,4,5,7);

    printf("STAMPO GRAFO G: \n");
    stampa_grafo(g1);

    printf("\n");

    g2=new_elem(6);

    aggiungi_arco(g2,0,1,3);
    aggiungi_arco(g2,0,2,1);
    aggiungi_arco(g2,1,2,4);
    aggiungi_arco(g2,1,3,2);
    aggiungi_arco(g2,2,3,6);
    aggiungi_arco(g2,3,4,8);
    aggiungi_arco(g2,4,5,1);

    printf("STAMPO GRAFO H: \n");
    stampa_grafo(g2);

    printf("\n");

    grafo *t=crea_grafo_t(g1,g2);

    printf("STAMPO GRAFO T: \n");
    stampa_grafo(t);
}