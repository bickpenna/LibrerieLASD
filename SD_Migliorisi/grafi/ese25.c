/*
Dati due grafi G1 e G2 entrambi orientati e pesati, implementati con liste di adiacenza. 
Scrivere una funzione in C che:
1. faccia la differenza dei due grafi in un terzo grafo in modo che un arco (a,b) sarà presento con
peso p se l'arco (a,b) è presente in G1 con peso p1, presente o meno in G2 con peso p2
e p=p1-p2;
2. scrivere dijkstra per il percorso minimo sul grafo costruito
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <stdbool.h>

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

bool is_edge_present(grafo *g, int u, int v)
{
    if(is_empty(g))
    {
        return false;
    }

    arco *corrente=g->adj[u];

    while(corrente!=NULL)
    {
        if(corrente->key==v)
        {
            return true;
        }
        corrente=corrente->next;
    }

    return false;
}

grafo *differenza_grafo(grafo *g1, grafo *g2)
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

            int diff_peso=peso1-peso2;

            if(diff_peso>0)
            {
                aggiungi_arco(g3,i,v,diff_peso);
            }

            e1=e1->next;
        }
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

        arco *e=g->adj[u];

        while(e!=NULL && e->next)
        {
            if(e->key>=0 && e->key < g->nv)
            {
                int v=e->key;
                int peso=e->peso;
                int alt=distanze[u]+peso;
                

                if(alt<distanze[v])
                {
                    distanze[v]=alt;
                    prev[v]=u;
                }
            }

            e=e->next;
        }
    }
}

void print_percorso_minimo(int *prev, int sorg, int dest)
{
    if(dest==sorg)
    {
        printf("%d ", sorg);
    }
    else if(prev[dest]==-1)
    {
        printf("Nessun percorso\n");
    }
    else
    {
        print_percorso_minimo(prev,sorg,prev[dest]);
        printf("%d ", dest);
    }
}

int main()
{
    grafo *g1=NULL;
    grafo *g2=NULL;

    g1=new_elem(5);

    aggiungi_arco(g1,0,2,3);
    aggiungi_arco(g1,1,3,4);
    aggiungi_arco(g1,1,2,1);
    aggiungi_arco(g1,2,0,3);
    aggiungi_arco(g1,2,1,2);
    aggiungi_arco(g1,3,4,4);

    printf("GGRAFO G1: \n");
    stampa_grafo(g1);

    g2=new_elem(5);

    aggiungi_arco(g2,0,2,1);
    aggiungi_arco(g2,1,3,6);
    aggiungi_arco(g2,1,2,0);
    aggiungi_arco(g2,2,0,2);
    aggiungi_arco(g2,2,1,1);
    aggiungi_arco(g2,3,4,2);

    printf("GRAFO G2: \n");
    stampa_grafo(g2);

    printf("\n");

    grafo *g3=differenza_grafo(g1,g2);

    printf("GRAFO G3: \n");
    stampa_grafo(g3);

    printf("\n");

    int distanze[5];
    int prev[5];

    dijkstra(g3,0,distanze,prev);

    printf("\nRisultato dijkstra: \n");

    for(int i=0; i<5; i++)
    {
        printf("Distanza da 0 a %d: %d\n", i, distanze[i]);
    }

    int sorgente=0;
    int destinazione=5;

    print_percorso_minimo(prev,sorgente,destinazione);

    printf("\n");

    return 0;

}