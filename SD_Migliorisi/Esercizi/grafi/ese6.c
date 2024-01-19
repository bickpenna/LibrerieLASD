/*
dati due grafi G1 e G2 entrambi orientati e pesati, implementati con liste di adiacenza
scrivere una funzione in c che faccia la differenza dei due grafi in un terzo grafo G3 in modo che 
un arco (a,b) sarà presente con peso p in G3 se l'arco (a,b) è presente in G1 con peso p1,
presente o meno in G2 con peso p2, e p =p1-p2, ed è positivo.
scrivere l'algoritmo di dijkstra per il percorso minimo sul grafo costruito
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>

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

grafo *differenza_grafi(grafo *g1, grafo *g2)
{
    grafo *g3=(grafo *)malloc(sizeof(grafo));

    if(g3)
    {
        g3->nv=g1->nv;

        g3->adj=(arco **)malloc(g3->nv*sizeof(arco *));

        if(g3->adj)
        {
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

                    int peso_diff=peso1-peso2;

                    if(peso_diff > 0)
                    {
                        arco *new=(arco *)malloc(sizeof(arco));

                        if(new)
                        {
                            new->key=v;
                            new->peso=peso_diff;
                            new->next=g3->adj[i];
                            g3->adj[i]=new;
                        }
                        else
                        {
                            printf("Errore di allocazione\n");
                        }
                    }
                    e1=e1->next;
                }
            }
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }
    return g3;
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

        arco *e = g->adj[u];

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

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    g1=new_elem(6);
    g2=new_elem(6);

    aggiungi_arco(g1,0,1,2);
    aggiungi_arco(g1,0,2,4);
    aggiungi_arco(g1,1,3,7);
    aggiungi_arco(g1,1,4,1);
    aggiungi_arco(g1,2,3,3);
    aggiungi_arco(g1,2,4,8);
    aggiungi_arco(g1,4,3,5);

    printf("STAMPO GRAFO G1: \n");
    stampa_grafo(g1);

    printf("\n");

    aggiungi_arco(g2,0,1,3);
    aggiungi_arco(g2,0,2,1);
    aggiungi_arco(g2,1,3,4);
    aggiungi_arco(g2,1,4,2);
    aggiungi_arco(g2,2,4,5);
    aggiungi_arco(g2,3,4,6);
    aggiungi_arco(g2,4,5,8);
    aggiungi_arco(g2,5,0,9);

    printf("STAMPO GRAFO G2: \n");
    stampa_grafo(g2);

    printf("\n");

    grafo *g3=differenza_grafi(g1,g2);

    printf("STAMPO GRAFO G3: \n");
    stampa_grafo(g3);

    int distanza[6];
    int prev[6];

    dijkstra(g3,0,distanza,prev);

    printf("\nRisultato dijkstra: \n");

    for(int i=0; i<6; i++)
    {
        printf("Distanza da 0 a %d: %d\n", i, distanza[i]);
    }
}