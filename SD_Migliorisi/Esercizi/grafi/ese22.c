/*
Dati 2 grafi G ed H con uguali nodi,calcolare la differenza pari in T. T avrà
l’arco (a,b) con peso p se l’arco è in G ma NON in H con peso p OPPURE
l’arco è in entrambi i grafi ma la differenza dei pesi p è positiva e pari.
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

            for(i=0; i<g->nv; i++)
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
    if(is_empty(g) || is_empty(h))
    {
        return NULL;
    }

    grafo *t=new_elem(g->nv);

    for(int i=0; i<g->nv; i++)
    {
        arco *eg=g->adj[i];
        arco *eh=h->adj[i];

        while(eg!=NULL && eh!=NULL)
        {
            if(eg->key != eh->key)
            {
                aggiungi_arco(t,i,eg->key,eg->peso);
            }
            else
            {
                int somma_p=eg->peso+eh->peso;

                if(somma_p%2==0 && somma_p>0)
                {
                    aggiungi_arco(t,i,eg->key,somma_p);
                }
            }

            eg=eg->next;
            eh=eh->next;
        }
    }

    return t;
}

int main()
{
    grafo *g=NULL;

    printf("CREO, INIZIALIZZO E STAMPO IL GRAFO G:  \n");

    g=new_elem(5);

    aggiungi_arco(g,0,1,3);
    aggiungi_arco(g,1,2,2);
    aggiungi_arco(g,2,3,1);
    aggiungi_arco(g,3,4,4);
    aggiungi_arco(g,4,0,2);
    aggiungi_arco(g,3,2,3);
    aggiungi_arco(g,0,2,7);

    stampa_grafo(g);

    printf("\n");

    grafo *h=NULL;

    printf("CREO, INIZIALIZZO E STAMPO IL GRAFO H: \n");

    h=new_elem(5);

    aggiungi_arco(h,0,1,2);
    aggiungi_arco(h,1,2,1);
    aggiungi_arco(h,2,3,2);
    aggiungi_arco(h,3,4,3);
    aggiungi_arco(h,4,0,1);
    aggiungi_arco(h,3,2,3);

    stampa_grafo(h);

    printf("\n");

    grafo *t=crea_grafo_t(g,h);

    stampa_grafo(t);

    printf("\n");
}