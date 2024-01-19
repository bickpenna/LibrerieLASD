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
Scrivere in linguaggio C una funzione che, presi in input G e H, crei e restituisca un nuovo
grafo T di n vertici e tale che T ha un arco con peso p se tale arco è presente in G e in H e la
somma dei relativi pesi è p, p è pari, e non via sia un altro arco con peso p in T.
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

grafo *crea_grafo_t(grafo *g, grafo *h)
{
    grafo *t=new_elem(g->nv);

    for(int i=0; i<g->nv; i++)
    {
        arco *e_g=g->adj[i];
        arco *e_h=g->adj[i];

        while(e_g != NULL && e_h != NULL)
        {
            int somma_peso=e_g->peso+e_h->peso;

            if(somma_peso%2==0)
            {
                aggiungi_arco(t,i,e_g->key,somma_peso);
            }

            e_g=e_g->next;
            e_h=e_h->next;
        }
    }

    return t;
}

int main()
{
    grafo *g=NULL;
    grafo *h=NULL;

    g=new_elem(6);
    h=new_elem(6);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,0,2,4);
    aggiungi_arco(g,1,2,1);
    aggiungi_arco(g,1,3,3);
    aggiungi_arco(g,2,3,5);
    aggiungi_arco(g,3,4,2);
    aggiungi_arco(g,4,5,7);

    printf("STAMPO GRAFO G: \n");
    stampa_grafo(g);

    printf("\n");

    aggiungi_arco(h,0,1,3);
    aggiungi_arco(h,0,2,1);
    aggiungi_arco(h,1,2,4);
    aggiungi_arco(h,1,3,2);
    aggiungi_arco(h,2,3,6);
    aggiungi_arco(h,3,4,8);
    aggiungi_arco(h,4,5,1);

    printf("STAMPO GRAFO H: \n");
    stampa_grafo(h);

    printf("\n");

    grafo *t=crea_grafo_t(g,h);

    printf("STAMPO GRAFO T: \n");
    stampa_grafo(t);

    printf("\n");

}