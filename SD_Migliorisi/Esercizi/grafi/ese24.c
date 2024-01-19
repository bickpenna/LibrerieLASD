/*
Dato un grafo orientato e pesato, implementato con liste di adiacenza,
scrivere una funzione che rimuova tutti gli archi con peso pari 
e tutti i nodi con grado uscente dispari
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

    g=(grafo *)malloc(sizeof(grafo ));

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

int grado_uscente(grafo *g, int nodo)
{
    if(is_empty(g))
    {
        return 0;
    }

    int grado=0;

    arco *e=g->adj[nodo];

    while(e!=NULL)
    {
        grado++;
        e=e->next;
    }

    return grado;
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

void rimuovi_archi_pari(grafo *g)
{
    if(is_empty(g))
    {
        return;
    }

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while (e!=NULL)
        {
            if(e->peso%2==0)
            {
                int v=e->key;

                rimuovi_arco(g,i,v);

                e=g->adj[i]; //ricomicia dalla testa della lista di adiacenza
            }
            else
            {
                e=e->next;
            }
        }
        
    }
}

void cancella_nodo(grafo *g, int nodo)
{
    if(is_empty(g))
    {
        return;
    }

    arco *temp=g->adj[nodo];

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

void rimuovi_nodi_ge_dispari(grafo *g)
{
    if(is_empty(g))
    {
        return;
    }

    for(int i=0; i<g->nv; i++)
    {
        int ge=grado_uscente(g,i);

        if(ge%2!=0)
        {
            //il nodo ha grado uscente dispari e lo rimuovo;
            cancella_nodo(g,i);
        }
    }
}

int main()
{
    grafo *g=NULL;

    g=new_elem(6);

    aggiungi_arco(g, 0, 1, 1);
    aggiungi_arco(g, 0, 2, 1);
    aggiungi_arco(g, 1, 3, 1);
    aggiungi_arco(g, 2, 4, 1);

    printf("STAMPO IL GRAFO: \n");
    stampa_grafo(g);

    printf("\n");

    //rimuovi_archi_pari(g);
    rimuovi_nodi_ge_dispari(g);

    printf("STAMPO IL GRAFO MODIFICATO: \n");
    stampa_grafo(g);
}