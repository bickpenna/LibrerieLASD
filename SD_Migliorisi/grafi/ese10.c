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

void elimina_grafo(grafo *g)
{
    if (g != NULL) {
        for (int i = 0; i < g->nv; i++) 
        {
            arco *e = g->adj[i];
            while (e != NULL) 
            {
                arco *temp = e;
                e = e->next;
                free(temp);
            }
        }
        free(g->adj);
        free(g);
    }
}

grafo *crea_grafo_t(grafo *g, grafo *h, grafo *f)
{
    grafo *t= new_elem(g->nv);

    for(int i=0; i<g->nv;i++)
    {
        arco *e_g=g->adj[i];
        arco *h_g=h->adj[i];
        arco *f_g=f->adj[i];

        while(e_g != NULL && h_g != NULL)
        {
            int somma_peso=e_g->peso+h_g->peso;

            if(somma_peso %2==0 && f_g->peso!=somma_peso)
            {
                aggiungi_arco(t,i,e_g->key,somma_peso);
            }
            else if(f_g->peso==somma_peso)
            {
                elimina_grafo(t);
                return t;
            }

            e_g=e_g->next;
            h_g=h_g->next;
            f_g=f_g->next;
        }
    }

    return t;
}

int main()
{
    grafo *g=NULL;
    grafo *h=NULL;
    grafo *f=NULL;

    g=new_elem(6);

    aggiungi_arco(g, 0, 1, 2);
    aggiungi_arco(g, 0, 2, 4);
    aggiungi_arco(g, 1, 3, 3); // Esempio di un altro arco in g
    aggiungi_arco(g, 2, 4, 5); // Esempio di un altro arco in g
    aggiungi_arco(g,3,5,9);

    printf("STAMPO GRAFO G: \n");
    stampa_grafo(g);

    printf("\n");

    h = new_elem(6);
    aggiungi_arco(h, 0, 1, 3);
    aggiungi_arco(h, 0, 2, 1);
    aggiungi_arco(h, 1, 3, 2); // Esempio di un altro arco in h
    aggiungi_arco(h, 2, 4, 6); // Esempio di un altro arco in h
    aggiungi_arco(h,3,5,5);

    printf("STAMPO GRAFO H: \n");
    stampa_grafo(h);

    printf("\n");

    f = new_elem(6);
    aggiungi_arco(f, 0, 1, 5);
    aggiungi_arco(f, 0, 2, 6);
    aggiungi_arco(f, 1, 3, 7); // Esempio di un altro arco in f
    aggiungi_arco(f, 2, 4, 8); // Esempio di un altro arco in f
    aggiungi_arco(f,3,5,10);

    printf("STAMPO GRAFO F: \n");
    stampa_grafo(f);

    printf("\n");

    grafo *t=crea_grafo_t(g,h,f);

    if (t != NULL)
    {
        printf("STAMPO GRAFO T:\n");
        stampa_grafo(t);
    }
    else
    {
        printf("La creazione del grafo T è stata annullata.\n");
    }
}