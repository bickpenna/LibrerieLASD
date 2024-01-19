/*
BFS E DFS E DIJKSTRA
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 50

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

/*CODA PER BFS*/
int empty_queue(int Q[])
{
    return Q[0]==0;
}

int full_queue(int Q[])
{
    return Q[0]==Q[MAX+1];
}

void enqueue(int Q[], int valore)
{
    Q[Q[MAX+1]]=valore;

    if(Q[0]==0)
    {
        Q[0]=1;
    }

    Q[MAX+1]=(Q[MAX+1]%MAX)+1;
}

int dequeue(int Q[])
{
    int valore=Q[Q[0]];
    Q[0]=(Q[0]%MAX)+1;

    if(Q[0]==Q[MAX+1])
    {
        Q[0]=0;
        Q[MAX+1]=1;
    }

    return valore;
}

void inizializza_queue(int Q[])
{
    Q[0]=0;
    Q[MAX+1]=1;
}

/*GRAFO*/

int is_empty_(grafo *g)
{
    return g==NULL;
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
        printf("Errore di allcazione\n");
    }
}

void stampa_grafo(grafo *g)
{
    int i;
    int ne=0;
    arco *e;

    if(!is_empty_(g))
    {
        printf("\nIl gafo ha %d vertici: ", g->nv);

        for(i=0; i<g->nv; i++)
        {
            printf("Nodi adiacenti al nodo %d-> ", i);
            e=g->adj[i];

            while(e!=NULL)
            {
                printf("%d (peso=%d) - ", e->key,e->peso);
                ne=ne+1;
                e=e->next;
            }
            printf("\n");
        }
        printf("Il grafo ha %d archi\n", ne);
    }   
}

void dfs1(grafo *g, int i, int *aux)
{
    arco *e;
    aux[i]=1;

    for(e=g->adj[i]; e; e=e->next)
    {
        if(!aux[e->key])
        {
            printf("%d ",e->key);
            dfs1(g,e->key,aux);
        }
    }
}

void dfs(grafo *g)
{
    int i;
    int *aux=calloc(g->nv,sizeof(int));

    if(aux)
    {
        for(i=0;i<g->nv;i++)
        {
            if(!aux[i])
            {
                printf("\n%d, ",i);
                dfs1(g,i,aux);
            }
        }
        free(aux);
    }
    else
    {
        printf("Errore di allocazione");
    }
}

void bfs1(grafo *g, int i, int *aux)
{
    arco *e;
    int coda_visitati[MAX+1];
    inizializza_queue(coda_visitati);
    enqueue(coda_visitati,i);

    while(!empty_queue(coda_visitati))
    {
        i=dequeue(coda_visitati);
        aux[i]=1;

        for(e=g->adj[i]; e; e=e->next)
        {
            if(!aux[e->key])
            {
                enqueue(coda_visitati,e->key);
                printf("%d. ", e->key);
                aux[e->key]=1;
            }
        }
    }
}

void bfs(grafo *g)
{
    int i;
    int *aux=calloc(g->nv, sizeof(int));

    if(aux)
    {
        for(i=0;i<g->nv;i++)
        {
            if(!aux[i])
            {
                printf("\n%d, ", i+1);
                bfs1(g,i,aux);
            }
        }
        free(aux);
    }
    else
    {
        printf("Errore di allocazione\n");
    }
}

int main()
{
    grafo *g=NULL;

    g=new_elem(10);

    aggiungi_arco(g, 0, 1, 1);
    aggiungi_arco(g, 0, 2, 1);
    aggiungi_arco(g, 1, 3, 1);
    aggiungi_arco(g, 1, 4, 1);
    aggiungi_arco(g, 2, 5, 1);
    aggiungi_arco(g, 2, 6, 1);
    aggiungi_arco(g, 3, 7, 1);
    aggiungi_arco(g, 4, 8, 1);
    aggiungi_arco(g, 5, 9, 1);

    printf("STAMPO IL GRAFO : \n");
    stampa_grafo(g);

    printf("\n");

    printf("RISULTATO DFS: \n");
    dfs(g);

    printf("\n");

    printf("RISULTATO BFS: \n");
    bfs(g);
}