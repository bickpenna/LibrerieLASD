/*
Si consideri un grafo G con V vertici ed E archi. Si implementino in 
linguaggio C le seguenti operazioni utilizzando sia una rappresentazione con liste di adiacenza che con matrice di adiacenza:
Creazione di una struttura dati grafo pesata contenente tutti i vertici del 
grafo G.
Modifica di un peso.
Aggiunta di un arco.
Cancellazione di un arco
Calcolo del grado uscente e entrante di un nodo.
Calcolo dell arco con peso maggiore 
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

struct el
{
    int nv;
    arco **adj;
};
typedef struct el grafo;

int is_empty(grafo *g)
{
    return (g==NULL);
}

grafo *new_elem(int n)
{
    grafo *g;
    int i;

    g=(grafo *)malloc(sizeof(grafo));

    if(g)
    {
        g->adj=(arco **)malloc(n*sizeof(arco *));
        if(g->adj)
        {
            g->nv=n;

            for(i=0;i<n;i++)
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

void aggiungi_arco(grafo *g, int u, int v,int peso)
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

grafo *inserisci_nodo(grafo *g)
{
    arco **e;

    if(is_empty(g))
    {
        return new_elem(1);
    }

    e=realloc(g->adj, (g->nv+1) * sizeof(arco *));

    if(e)
    {
        g->adj=e;
        g->adj[g->nv]=NULL;
        g->nv=g->nv+1;
    }
    else
    {
        printf("Errore di reallocazione\n");
    }

    return g;
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

void modifica_peso_arco(grafo *g, int u, int v, int nuovo_peso)
{
    arco *tmp=g->adj[u];

    if(tmp==NULL)
    {
        return;
    }

    while(tmp)
    {
        if(tmp->key==v)
        {
            tmp->peso=nuovo_peso;
            break;
        }
        tmp=tmp->next;
    }
}

arco *arco_peso_maggiore(grafo *g)
{
    arco *peso_massimo=NULL;

    for(int i=0;i<g->nv;i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            if(peso_massimo == NULL || e->peso > peso_massimo->peso)
            {
                peso_massimo=e;
            }
            e=e->next;
        }
    }

    return peso_massimo;
}

void rimuovi_arco(grafo *g, int u, int v,int peso)
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

int main()
{
    grafo *g=NULL;
    int u;
    int v;
    int max_peso;

    g=new_elem(6);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,0,3,1);
    aggiungi_arco(g,0,4,3);
    aggiungi_arco(g,1,3,1);
    aggiungi_arco(g,1,4,2);
    aggiungi_arco(g,2,3,3);
    aggiungi_arco(g,2,5,2);
    aggiungi_arco(g,3,5,1);
    aggiungi_arco(g,4,5,1);

    stampa_grafo(g);

    modifica_peso_arco(g,2,5,4);

    printf("GRAFO MODIFICATO: \n");
    stampa_grafo(g);

    arco *peso_max=arco_peso_maggiore(g);

    printf("\nL'arco con peso maggiore: %d -> %d (peso : %d)\n", 0, peso_max->key, peso_max->peso);

    rimuovi_arco(g,3,5,1);

    stampa_grafo(g);
}
