/*
Dati due grafi orientati e pesati scrivi una funzione che presi H e G restituisce
con i pesi dei suoi archi diminuiti dei pesi degli archi corrispondenti in H. Se
un arco ha peso minore di 10 lo si elimina. Descrivi la complessità.
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

            for(i=0;i<nv;i++)
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
        printf("Errore di allcazione\n");
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

/*
void rimuovi_arco(grafo *g, int u, int v)
{
    if(g->adj[u]==NULL)
    {
        return;
    }

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
*/

void rimuovi_arco(grafo *g, int u, int v)
{
    if (g->adj[u] == NULL)
    {
        // Non ci sono archi adiacenti al nodo u, quindi non c'è nulla da rimuovere.
        return;
    }

    arco *prev = NULL;
    arco *e = g->adj[u];

    while (e != NULL)
    {
        if (e->key == v)
        {
            if (prev == NULL)
            {
                // Se l'arco da rimuovere è il primo nella lista, aggiorna g->adj[u].
                g->adj[u] = e->next;
            }
            else
            {
                // Altrimenti, collega il nodo precedente al successivo.
                prev->next = e->next;
            }

            // Libera la memoria dell'arco rimosso.
            free(e);
            return;
        }

        prev = e;
        e = e->next;
    }
}


void archi_diminuiti(grafo *g1, grafo *g2)
{
    for(int i=0; i<g1->nv; i++)
    {
        arco *e_g1=g1->adj[i];
        arco *e_g2=g2->adj[i];

        while(e_g1!=NULL && e_g2!=NULL)
        {
            e_g1->peso -= e_g2->peso;

            if(e_g1->peso < 10)
            {
                rimuovi_arco(g1, i, e_g1->key);
            }

            e_g1=e_g1->next;
            e_g2=e_g2->next;
        }
    }
}

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    g1=new_elem(6);
    g2=new_elem(6);

    aggiungi_arco(g2,0,1,5);
    aggiungi_arco(g2,0,2,8);
    aggiungi_arco(g2,1,2,3);
    aggiungi_arco(g2,1,3,7);
    aggiungi_arco(g2,2,3,4);
    aggiungi_arco(g2,3,4,6);
    aggiungi_arco(g2,4,5,2);

    printf("STAMPO GRAFO H: \n");
    stampa_grafo(g2);

    printf("\n");

    aggiungi_arco(g1,0,1,10);
    aggiungi_arco(g1,0,2,15);
    aggiungi_arco(g1,1,2,6);
    aggiungi_arco(g1,1,3,12);
    aggiungi_arco(g1,2,3,7);
    aggiungi_arco(g1,3,4,8);
    aggiungi_arco(g1,4,5,5);

    printf("STAMPO GRAFO G: \n");
    stampa_grafo(g1);

    printf("\n");

    archi_diminuiti(g1,g2);

    printf("STAMPO GRAFO G MODIFICATO: \n");
    stampa_grafo(g1);

    printf("\n");
}