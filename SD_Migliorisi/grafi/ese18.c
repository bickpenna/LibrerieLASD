/*
Siano G e H due grafi non orientati pesati entrambi con pesi positivi, di n vertici 0, 1,…,
n-1 e rappresentati con liste di adiacenza utilizzando la seguente struttura:
typedef struct graph {
int nv;
edge **adj; } graph;
graph *G, *H;
typedef struct edge {
int key;
int peso;
struct edge *next; } edge;
scrivere in linguaggio C tre funzioni che in successione, presi in input i due grafi G e H,
a. Sostituiscano tutti gli archi in G e H in modo che ogni arco (a, b) in G abbia peso
a+b in G, e a*b in H
b. Per ogni arco (a, b) in G e H, rimuovano l’arco in G se la somma dei due pesi è
dispari e da H in caso contrario.
c. Preso m come input, controllino se esiste un sottografo di G, di m nodi, fortemente
connesso
d. Studiare la complessità delle funzioni implementate.
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

void sostituisci_pesi(grafo *g, grafo *h)
{
    if (is_empty(g) || is_empty(h))
    {
        return;
    }

    int i;

    for (i = 0; i < g->nv; i++)
    {
        arco *current = g->adj[i];

        while (current != NULL && current->next != NULL) // Verifica anche current->next
        {
            current->peso = current->key + current->next->key;
            current = current->next;
        }
    }

    for (i = 0; i < h->nv; i++)
    {
        arco *current = h->adj[i];

        while (current != NULL && current->next != NULL) // Verifica anche current->next
        {
            current->peso = current->key * current->next->key;
            current = current->next;
        }
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

void rimuovi_peso_dispari(grafo *g, grafo *h)
{
    if(is_empty(g) || is_empty(h))
    {
        return;
    }

    for(int i=0; i<g->nv; i++)
    {
        arco *eg=g->adj[i];
        arco *eh=h->adj[i];

        while((eg!=NULL && eg->next!=NULL) && (eh!=NULL && eh->next!=NULL))
        {
            int somma_p=eg->peso+eh->peso;
            
            if(somma_p%2!=0)
            {
                rimuovi_arco(g,i,eg->key);
            }
            else if(somma_p%2==0)
            {
                rimuovi_arco(h,i,eh->key);
            }

            eg=eg->next;
            eh=eh->next;
        }
    }
}

int main()
{
    grafo *g=NULL;
    grafo *h=NULL;

    printf("INIZIALIZZO E STAMPO IL GRAFO G: \n");

    g=new_elem(6);
    
    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,0,2,4);
    aggiungi_arco(g,1,3,1);
    aggiungi_arco(g,1,4,3);
    aggiungi_arco(g,2,4,5);
    aggiungi_arco(g,3,5,2);

    stampa_grafo(g);

    printf("\n");

    printf("INIZIALIZZO E STAMPO IL GRAFO H: \n");

    h=new_elem(6);

    aggiungi_arco(h,0,1,3);
    aggiungi_arco(h,0,2,1);
    aggiungi_arco(h,1,3,3);
    aggiungi_arco(h,2,4,2);
    aggiungi_arco(h,3,5,1);
    aggiungi_arco(h,4,5,4);

    stampa_grafo(h);

    printf("\n");

    printf("OPERAZIONE DI MODIFICA PESI PER I DUE GRAFI: \n");

    sostituisci_pesi(g,h);

    printf("STAMPO GRAFO G MODIFICATO: \n");
    stampa_grafo(g);

    printf("\n");

    printf("STAMPO GRAFO H MODIFICATO: \n");
    stampa_grafo(h);

    printf("\n");

    rimuovi_peso_dispari(g,h);

    printf("STAMPO GRAFO G MODIFICATO: \n");
    stampa_grafo(g);

    printf("\n");

    printf("STAMPO GRAFO H MODIFICATO: \n");
    stampa_grafo(h);
}
