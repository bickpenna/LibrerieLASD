/*
Siano G e H due grafi orientati pesati entrambi con pesi positivi, di n vertici 0, 1, , n-1 e
rappresentati con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G, *H;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C una funzione che, presi in input i due grafi G e H, restituisca un
nuovo grafo P (della stessa struttura di G e H), che abbia
i. gli stessi vertici di G e H
ii. un arco (a, b) per ogni arco arco (a,b) presente sia in H che nella trasposta di
G, e tale che la differenza tra i due pesi sia positiva. Tale differenza
rappresenta poi il peso di (a,b) in P.
b. Implementare una funzione che calcoli, dato G e un suo nodo, il suo grado
incidente.
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
        g->adj=(arco **)malloc(nv*sizeof(arco*));

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

int grado_entrante(grafo *g, int nodo)
{
    if(is_empty(g))
    {
        return 0;
    }

    int grado=0;

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            if(e->key==nodo)
            {
                grado++;
            }

            e=e->next;
        }
    }

    return grado;
}

grafo *trasposto_grafo(grafo *g)
{
    grafo *gt=(grafo *)malloc(sizeof(grafo));

    if(gt)
    {
        gt->nv=g->nv;

        gt->adj=(arco **)malloc(gt->nv*sizeof(arco *));

        if(gt->adj)
        {
            for(int i=0; i<gt->nv; i++)
            {
                gt->adj[i]=NULL;
            }

            for(int i =0; i<gt->nv; i++)
            {
                arco *tmp=g->adj[i];

                while(tmp)
                {
                    aggiungi_arco(gt,tmp->key,i,tmp->peso);
                    tmp=tmp->next;
                }
            }
        }
        else
        {
            printf("Errore di allocazione\n");
            free(gt);
            gt=NULL;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return gt;
}

grafo *crea_grafo_p(grafo *g, grafo *h)
{
    grafo *p=new_elem(g->nv);
    grafo *gt=trasposto_grafo(g);

    for(int a=0; a<g->nv; a++)
    {
        for(int b=0; b<g->nv; b++)
        {
            if(a!=b)
            {
                arco *eg=gt->adj[a];
                arco *eh=h->adj[a];

                int pesog=-1;
                int pesoh=-1;

                while(eg!=NULL)
                {
                    if(eg->key==b)
                    {
                        pesog=eg->peso;
                        break;
                    }
                    eg=eg->next;
                }

                while(eh!=NULL)
                {
                    if(eh->key==b)
                    {
                        pesoh=eh->peso;
                        break;
                    }
                    eh=eh->next;
                }

                if(pesog>=0 && pesoh>=0 && pesoh>pesog)
                {
                    int diff_pesi=pesoh-pesog;

                    aggiungi_arco(p,a,b,diff_pesi);
                }
            }
        }
    }

    free(gt);
    return p;
}

int main()
{
    grafo *g=NULL;
    grafo *h=NULL;

    g=new_elem(5);

    printf("CREO E STAMPO IL GRAFO G: \n");

    aggiungi_arco(g,0,1,5);
    aggiungi_arco(g,1,2,8);
    aggiungi_arco(g,1,3,6);
    aggiungi_arco(g,2,4,7);
    aggiungi_arco(g,3,4,3);

    stampa_grafo(g);

    printf("\n");

    int vertice=3;
    int ge=grado_entrante(g,vertice);

    if(ge>0)
    {
        printf("Il grado entrante del vertice %d è %d\n", vertice,ge);
    }
    else
    {
        printf("Errore nel calcolo\n");
    }

    grafo *gt=trasposto_grafo(g);

    printf("STAMPO GRAFO TRASPOSTA: \n");
    stampa_grafo(gt);

    printf("\n\n");

    printf("CREO E STAMPO IL GRAFO H: \n");
    h=new_elem(5);

    aggiungi_arco(h,0,1,4);
    aggiungi_arco(h,1,2,7);
    aggiungi_arco(h,1,3,4);
    aggiungi_arco(h,2,4,6);
    aggiungi_arco(h,3,4,2);

    stampa_grafo(h);

    printf("\n");

    grafo *p=crea_grafo_p(g,h);

    stampa_grafo(p);
    return 0;
}