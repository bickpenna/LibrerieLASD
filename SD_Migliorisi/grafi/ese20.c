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
a. per ogni arco (a, b) presente sia in G che in H, rimuove l’arco con il peso maggiore
(in caso di equivalenza di pesi ne rimuove uno a caso).
b. per ogni arco (a, b) non presente sia in G che in H, ne aggiunge in modo alternante
uno a G e uno a H, con il seguente peso. Se (a,b) è l’arco i-esimo aggiunto, il suo
peso è fattoriale di i.
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

            for(i=0;i<g->nv; i++)
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

arco *peso_maggiore(grafo *g)
{
    arco *peso_massimo=NULL;

    for(int i=0; i < g->nv; i++)
    {
        arco *e= g->adj[i];
        
        while(e!=NULL)
        {
            if(peso_massimo==NULL || e->peso > peso_massimo->peso)
            {
                peso_massimo=e;
            }

            e=e->next;
        }
    }
    return peso_massimo;
}

void rimuovi_arco(grafo *g, int u, int v)
{
    arco *prev;
    arco *e;

    e=g->adj[u];

    if(e->key==v)
    {
        g->adj[u]=e->next;
    }
    else
    {
        prev=e;

        while(prev->next->key!=v)
        {
            prev=prev->next;
            e=prev->next;
            prev->next=e->next;
        }
    }

    free(e);
}

bool is_edge_here(grafo *g, int u, int v)
{
    if(is_empty(g))
    {
        return false;
    }

    arco *corrente=g->adj[u];

    while(corrente!=NULL)
    {
        if(corrente->key==v)
        {
            return true;
        }

        corrente=corrente->next;
    }

    return false;
}

grafo *rimuovi_arco_maggiore(grafo *g, grafo *h)
{
    if (is_empty(g) || is_empty(h))
    {
        return NULL;
    }

    for (int a = 0; a < g->nv; a++)
    {
        arco *eg = g->adj[a];
        arco *eh = h->adj[a];

        while (eg != NULL && eh != NULL)
        {
            if (eg->key == eh->key)
            {
                if (eg->peso > eh->peso)
                {
                    rimuovi_arco(g, a, eg->key);
                }
                else if (eh->peso > eg->peso)
                {
                    rimuovi_arco(h, a, eh->key);
                }

                eg = eg->next;
                eh = eh->next;
            }
            else if (eg->key < eh->key)
            {
                eg = eg->next;
            }
            else
            {
                eh = eh->next;
            }
        }
    }
    return g;
}


int main()
{
    grafo *g = new_elem(6);
    
    aggiungi_arco(g, 0, 1, 2);
    aggiungi_arco(g, 0, 2, 4);
    aggiungi_arco(g, 1, 3, 1);
    aggiungi_arco(g, 1, 4, 3);
    aggiungi_arco(g, 2, 4, 5);
    aggiungi_arco(g, 3, 5, 2);
    
    grafo *h = new_elem(6);
    
    aggiungi_arco(h, 0, 1, 3);
    aggiungi_arco(h, 0, 2, 1);
    aggiungi_arco(h, 1, 3, 3);
    aggiungi_arco(h, 2, 4, 2);
    aggiungi_arco(h, 3, 5, 1);
    aggiungi_arco(h, 4, 5, 4);
    
    printf("Grafo G:\n");
    stampa_grafo(g);
    
    printf("\nGrafo H:\n");
    stampa_grafo(h);
    
    grafo *risultato=rimuovi_arco_maggiore(g,h);

    printf("\nGrafo G modificato:\n");
    stampa_grafo(g);
    
    printf("\nGrafo H modificato:\n");
    stampa_grafo(h);
    
    return 0;
}

