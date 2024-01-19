/*Siano G e H due grafi orientati pesati entrambi con pesi positivi, di n vertici 0, 1,…, n-1 e
 rappresentati con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
 int nv;
 edge **adj; } graph;
graph *G, *H;
typedef struct edge {
 int key;
 int peso;
 struct edge *next; } edge;
Sia F un grafo orientato e pesato, implementato con matrici di adiacenza. Scrivere in 
linguaggio C una funzione che, presi in input G, H e F, con input da tastiera(!), permetta
di fare l'intersezione in un nuovo grafo T, tale per cui l'arco (a,b) con peso p è inserito in T
se (a,b) con peso positivo è presente sia in G e H, p è la somma dei due pesi, e l'arco (a,b) 
con peso p non è presente in F, altrimenti la procedura si deve fermare e annullare la 
creazione del grafo (attenzione a non lasciare grafi parzialmente creati). Tutti i grafi dati in
input non devono essere modificati. I grafi vanno stampati prima e dopo l'operazione di 
interesezione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

void aggiungi_arco(grafo *g, int u, int v , int peso)
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

grafo *crea_grafo_t(grafo *g1, grafo *g2)
{
    grafo *g3=new_elem(g1->nv);

    for(int i=0; i<g1->nv; i++)
    {
        arco *eg1=g1->adj[i];
        arco *eg2=g2->adj[i];

        while(eg1 != NULL && eg2 != NULL)
        {
            int somma_peso=eg1->peso+eg2->peso;

            if(somma_peso > 0)
            {
                aggiungi_arco(g3,i,eg1->key,somma_peso);
            }

            eg1=eg1->next;
            eg2=eg2->next;
        }
    }

    return g3;
}

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    printf("GRAFO G1\n");
    g1=new_elem(5);

    aggiungi_arco(g1,0,1,4);
    aggiungi_arco(g1,1,2,3);
    aggiungi_arco(g1,0,2,1);
    aggiungi_arco(g1,1,3,1);
    aggiungi_arco(g1,2,4,1);

    stampa_grafo(g1);

    printf("\n");

    printf("GRAFO G2: \n");

    g2=new_elem(5);

    aggiungi_arco(g2,0,1,2);
    aggiungi_arco(g2,1,2,1);
    aggiungi_arco(g2,0,2,4);
    aggiungi_arco(g2,1,3,7);
    aggiungi_arco(g2,2,4,5);
    aggiungi_arco(g2,0,4,9);

    stampa_grafo(g2);

    printf("\n");

    grafo *g3=crea_grafo_t(g1,g2);

    stampa_grafo(g3);

}