/*
3, Sia G un grafo orientato e pesato con nodi O, I, n-I. Si calcoli il grado entrante e uscente. Inoltre
dato in input da tastiera un nodo x,
a) rimuovere fisicamente il nodo se la somma dei suoi archi entranti è maggiore di quelli uscenti.
b) per ogni arco (a,x) con peso pl e (x,b) con peso p2, si consideri l'arco (a,b) con peso p=p1+p2. Se tale
arco (a,b) non è presente in G oppure è presente ma con un peso inferiore al valore p, si aggiunga in G
l'arco (a,b) con peso p.
Si stampi il grafo prima e dopo le modifiche
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

int lunghezza_lista(arco *e)
{
    if(e==NULL)
    {
        return 0;
    }
    
    return 1+lunghezza_lista(e->next);
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

void cancella_nodo(grafo *g, int nodo)
{
    g->adj[nodo]=NULL;

    for(int i=0; i<g->nv; i++)
    {
        arco *tmp=g->adj[i];
        arco *prev=NULL;

        while(tmp)
        {
            if(tmp->key==nodo)
            {
                if(prev)
                {
                    prev->next=tmp->next;
                }
                else
                {
                    g->adj[i]=tmp->next;
                }
                free(tmp);
                break;
            }

            prev=tmp;
            tmp=tmp->next;
        }
    }
}

int cancella_nodo_somma_archi(grafo *g, int nodo)
{
    int grado_usc=grado_uscente(g,nodo);
    int grado_ent=grado_entrante(g,nodo);

    if(grado_ent>grado_usc)
    {
        cancella_nodo(g,nodo);
    }
}

int main()
{
    grafo *g=NULL;

    g=new_elem(6);

    aggiungi_arco(g,0,1,3);
    aggiungi_arco(g,0,2,4);
    aggiungi_arco(g,1,2,1);
    aggiungi_arco(g,1,3,5);
    aggiungi_arco(g,2,3,9);
    aggiungi_arco(g,3,4,6);
    aggiungi_arco(g,4,5,7);

    printf("STAMPO IL GRAFO G: \n");
    stampa_grafo(g);

    printf("\n");

    printf("CALCOLO GRADO ENTRANTE E GRADO USCENTE DI UN DETERMINATO NODO: \n");

    int grado_usc=grado_uscente(g,1);

    printf("Il grado uscente del nodo 1 è %d\n", grado_usc);

    printf("\n");

    int grado_ent=grado_entrante(g,1);

    printf("ll grado entrante del nodo 1 è %d\n", grado_ent);

    printf("\n");

    cancella_nodo(g,3);

    printf("GRAFO MODIFICATO: \n");
    stampa_grafo(g);
}