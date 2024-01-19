/*
PRIMITIVE SUI GRAFI
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct el_edge
{
    int key;
    struct el_edge *next;
};
typedef struct el_edge arco;

struct el
{
    int nv;
    arco **adj; //vettore con n liste di adiacenza;
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
        g->adj=(arco **)malloc(n*sizeof(arco*));
        
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
        printf("Errore di allocazione per il grafo\n");
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
        printf("Il grafo ha %d vertici\n", g->nv);

        for(i=0;i<g->nv;i++)
        {
            printf("Nodi adiacenti al nodo %d-> ",i);
            e=g->adj[i];
            while(e!=NULL)
            {
                printf("%d ", e->key);
                ne=ne+1;
                e=e->next;
            }
            printf("\n");
        }

        printf("\nIl grafo ha %d archi\n", ne);
    }
}

void aggiungi_arco(grafo *g, int u, int v)
{
    arco *new;
    arco *e;

    if(is_empty(g))
    {
        return;
    }

    new=(arco *)malloc(sizeof(arco));

    if(new)
    {
        new->key=v;
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
                e->next=new;
            }
        }
    }
    else
    {
        printf("Errore di allocazione\n");
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

grafo *trasposto_grafo(grafo *g)
{
    grafo *gt=(grafo *)malloc(sizeof(grafo));

    if(gt)
    {
        gt->nv=g->nv;
        gt->adj=(arco **)malloc(gt->nv* sizeof(arco *));

        for(int i=0; i< gt->nv; i++)
        {
            gt->adj[i]=NULL;
        }

        for(int i=0; i<g->nv; i++)
        {
            arco *tmp=g->adj[i];
            while(tmp)
            {
                aggiungi_arco(gt,tmp->key,i);
                tmp=tmp->next;
            }
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return gt;

}

int main()
{
    grafo *g=NULL;

    g= new_elem(6);

	aggiungi_arco(g,0,2);
	aggiungi_arco(g,1,2);
	aggiungi_arco(g,1,4);
	aggiungi_arco(g,2,3);
	aggiungi_arco(g,3,4);
	aggiungi_arco(g,4,1);
    aggiungi_arco(g,5,3);

    //rimuovi_arco(g,3,4);
	stampa_grafo(g);

    printf("GRAFO TRASPOSTO: \n");
    grafo *gt=trasposto_grafo(g);

    stampa_grafo(gt);
}