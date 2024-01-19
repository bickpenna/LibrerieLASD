/*
Siano G e H due grafi orientati pesati entrambi con pesi positivi, di n vertici 0,1,…, n-1 e
rappresentati con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G, *H;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C una funzione che preso in input i due grafi G e H, restituisce G
con i pesi dei suoi archi diminuiti dei pesi degli archi corrispondenti in H. Se un arco
ottiene peso negativo, l’arco deve essere rimosso. Descrivere la complessità della funzione
implementata.
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

            for(i=0;i<g->nv;i++)
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

void aggiorna_pesi(grafo *g, grafo *h)
{
    if (is_empty(g) || is_empty(h))
    {
        return;
    }

    for (int u = 0; u < g->nv; u++)
    {
        arco *eg = g->adj[u];
        arco *eh = h->adj[u];

        while (eg != NULL && eh != NULL)
        {
            if (eg->key == eh->key)
            {
                int diff = eg->peso - eh->peso;

                if (diff < 0)
                {
                    // La differenza è negativa, rimuovi l'arco da g
                    rimuovi_arco(g, u, eg->key);
                }
                else
                {
                    eg->peso = diff; // Aggiorna il peso in g
                }

                eh = eh->next;
            }
            eg = eg->next;
        }
    }
}


int main()
{
    grafo *g=NULL;
    grafo *h=NULL;

    printf("INIZIALIZZO E STAMPO IL GRAFO G: \n");

    g=new_elem(4);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,1,2,1);
    aggiungi_arco(g,0,3,3);
    aggiungi_arco(g,3,1,1);

    stampa_grafo(g);

    printf("\n");

    printf("INIZIALIZZO E STAMPO IL GRAFO H: \n");

    h=new_elem(4);

    aggiungi_arco(h, 0, 1, 3);
    aggiungi_arco(h, 1, 2, 2);
    aggiungi_arco(h, 0, 3, 4);
    aggiungi_arco(h, 3, 1, 2);

    stampa_grafo(h);

    printf("\n");

    aggiorna_pesi(g,h);

    stampa_grafo(g);


}