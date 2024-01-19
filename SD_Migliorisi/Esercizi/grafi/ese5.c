/*
DIJKSTRA
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

void dijkstra(grafo *g, int sorgente, int *distanze, int *prev)
{
    int visitati[g->nv];

    for(int i=0; i<g->nv; i++)
    {
        distanze[i]=INT_MAX;
        prev[i]=-1;
        visitati[i]=0;
    }

    distanze[sorgente]=0;

    for(int i=0; i<g->nv; i++)
    {
        int minima_distanza=INT_MAX;
        int u=-1;

        for(int j=0; j<g->nv; j++)
        {
            if(!visitati[j] && distanze[j]<minima_distanza)
            {
                minima_distanza=distanze[j];
                u=j;
            }
        }

        visitati[u]=1;

        arco *e=g->adj[u];

        while(e!=NULL)
        {
            int v=e->key;
            int peso=e->peso;
            int alt=distanze[u]+peso;

            if(alt<distanze[v])
            {
                distanze[v]=alt;
                prev[v]=u;
            }

            e=e->next;
        }
    }
}

void stampa_percorso_minimo(int *prev, int sorgente, int dest)
{
    if(dest==sorgente)
    {
        printf("%d ", sorgente);
    }
    else if(prev[dest]==-1)
    {
        printf("Nessun percorso da %d a %d \n", sorgente, dest);
    }
    else
    {
        stampa_percorso_minimo(prev,sorgente,prev[dest]);
        printf("%d ", dest);
    }
}

int main()
{
    grafo *g=NULL;

    g=new_elem(7);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,1,0,2);

    aggiungi_arco(g,0,2,6);
    aggiungi_arco(g,2,0,6);

    aggiungi_arco(g,1,3,5);
    aggiungi_arco(g,3,1,5);

    aggiungi_arco(g,2,3,8);
    aggiungi_arco(g,3,2,8);

    aggiungi_arco(g,3,5,15);
    aggiungi_arco(g,5,3,15);

    aggiungi_arco(g,3,4,10);
    aggiungi_arco(g,4,3,10);

    aggiungi_arco(g,5,4,6);
    aggiungi_arco(g,4,5,6);

    aggiungi_arco(g,4,6,2);
    aggiungi_arco(g,6,4,2);

    aggiungi_arco(g,5,6,6);
    aggiungi_arco(g,6,5,6);

    printf("GRAFO: \n");

    stampa_grafo(g);

    printf("\n");

    int distanza[7];
    int prev[7];

    dijkstra(g,0,distanza,prev);

    printf("\nRisultato dijkstra: \n");

    for(int i=0; i<7; i++)
    {
        printf("Distanza da 0 a %d: %d\n", i, distanza[i]);
    }

    int sorgente=0;
    int destinazione=5;

    stampa_percorso_minimo(prev,sorgente,destinazione);

    printf("\n");

    return 0;
}