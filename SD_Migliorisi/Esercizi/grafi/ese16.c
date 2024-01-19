/*
Si considerino due grafi G e H grafi orientati pesati di n vertici 0,1, , n-1 rappresentati
con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G, *H;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
Scrivere in linguaggio C una funzione che presi in input i grafi G e H, restituisca un
nuovo grafo T con la stessa struttura in modo tale T ha l arco (a,b) se esso è presente
sia in G che in H e il suo peso è dato dalla somma del relativo peso in G e H più il
grado adiacente di a più il grado incidente di b in H.
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

            while (e->next!=NULL)
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

int grado_uscente(grafo *g, int nodo)
{
    int grado=0;

    arco *e=g->adj[nodo];

    while(e!=NULL)
    {
        grado++;
        e=e->next;
    }

    return grado;
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

grafo *crea_grafo_t(grafo *g, grafo *h)
{
    if(is_empty(g) || is_empty(h))
    {
        return NULL;
    }

    grafo *t=new_elem(g->nv);

    for(int a=0; a<g->nv;a++)
    {
        for(int b=0; b<g->nv; b++)
        {
            if(a!=b && is_edge_here(g,a,b) && is_edge_here(h,a,b))
            {
                int pesog=0;
                int pesoh=0;

                arco *eg=g->adj[a];
                arco *eh=h->adj[a];

                while (eg!=NULL)
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

                int grado_adiacente_a=grado_uscente(g,a)+grado_uscente(h,a);
                int grado_incidente_b=grado_entrante(g,b)+grado_uscente(h,b);

                int peso_arco_t=pesog+pesoh+grado_adiacente_a+grado_incidente_b;

                aggiungi_arco(t,a,b,peso_arco_t);
                
            }
        }
    }
    return t;    
}

int main() {
    // Crea due grafi G e H
    grafo* G = new_elem(6);
    grafo* H = new_elem(6);

    // Aggiungi archi ai grafi G e H come desiderato
    aggiungi_arco(G, 0, 1, 2);
    aggiungi_arco(G, 1, 2, 3);
    aggiungi_arco(G, 2, 3, 1);
    aggiungi_arco(H, 0, 1, 1);
    aggiungi_arco(H, 1, 2, 2);
    aggiungi_arco(H, 2, 3, 1);

    printf("Grafo G:\n");
    stampa_grafo(G);

    printf("\nGrafo H:\n");
    stampa_grafo(H);

    // Chiama la funzione crea_grafo_T con G e H
    grafo* T = crea_grafo_t(G, H);

    printf("\nGrafo T:\n");
    stampa_grafo(T);

    // Libera la memoria allocata per i grafi
    // Libera la memoria per G, H e T come necessario

    return 0;
}



