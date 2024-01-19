/*
Dati 2 grafi G ed H con uguali nodi,calcolare la differenza pari in T. T avrà
l’arco (a,b) con peso p se l’arco è in G ma NON in H con peso p OPPURE
l’arco è in entrambi i grafi ma la differenza dei pesi p è positiva e pari.
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

grafo *differenza_pari_grafo(grafo *g1, grafo *g2)
{
    grafo *g3=new_elem(g1->nv);

    for(int i=0; i<g3->nv; i++)
    {
        g3->adj[i]=NULL;

        arco *e1=g1->adj[i];

        while(e1!=NULL)
        {
            int v=e1->key;
            int peso1=e1->peso;
            int peso2=0;

            arco *e2=g2->adj[i];

            while(e2!=NULL)
            {
                if(e2->key==v)
                {
                    peso2=e2->peso;
                    break;
                }

                e2=e2->next;
            }

            int differenza_peso=peso1-peso2;

            if(differenza_peso > 0 && differenza_peso %2==0)
            {
                aggiungi_arco(g3,i,v,differenza_peso);
            }

            e1=e1->next;
        }
    }

    return g3;
}

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    g1=new_elem(4);
    g2=new_elem(4);

    aggiungi_arco(g1,0,1,4);
    aggiungi_arco(g1,0,2,6);
    aggiungi_arco(g1,1,3,8);

    aggiungi_arco(g2,0,1,2);
    aggiungi_arco(g2,0,2,4);
    aggiungi_arco(g2,1,3,6);

    grafo *g3=differenza_pari_grafo(g1,g2);

    printf("STAMPO GRAFO G3: \n");
    stampa_grafo(g3);

    printf("\n");

    return 0;
}


