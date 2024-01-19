/*
INSERIMENTO E CANCELLAZIONE NODO
BFS E DFS
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

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
    return g==NULL;
}

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

grafo *new_elem(int n)
{
    grafo *g;
    int i;

    g=(grafo *)malloc(sizeof(grafo));

    if(g)
    {
        g->adj=(arco **)malloc(n*sizeof(arco *));

        if(g->adj)
        {
            g->nv=n;

            for(i=0;i<n;i++)
            {
                g->adj[i]==NULL;
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

void aggiungi_arco(grafo *g, int u, int v,int peso)
{
    arco *new;
    arco *e;

    new=(arco *)malloc(sizeof(arco *));

    if(new)
    {
        new->key=v;
        new->peso=peso;

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
        printf("Il grafo ha %d vertici\n", g->nv);

        for(i=0;i<g->nv;i++)
        {
            printf("Nodi adiacenti al nodo %d -> ", i);
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

grafo *inserisci(grafo *g)
{
    arco **e;

    if(is_empty(g))
    {
        return new_elem(1);
    }

    e=realloc(g->adj, (g->nv+1) * sizeof(arco*));

    if(e)
    {
        g->adj=e;
        g->adj[g->nv]=NULL;
        g->nv=g->nv+1;
    }
    else
    {
        printf("Errore di reallocazione\n");
    }

    return g;
}

void cancella_nodo(grafo *g, int nodo)
{
    g->adj[nodo]=NULL;

    for(int i=0; i<g->nv; i++)
    {
        arco *tmp=g->adj[i];
        arco *prev=NULL;

        while(tmp)
        {
            if(tmp->key==nodo)
            {
                if(prev)
                {
                    prev->next=tmp->next;
                }
                else
                {
                    g->adj[i]=tmp->next;
                }

                free(tmp);
                break;
            }
            prev=tmp;
            tmp=tmp->next;
        }
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
            printf("%d, ", e->key);
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
        printf("Errore di allocazione\n");
    }
}

void bfs1(grafo *g, int i, int *aux)
{
    arco *e;
    int coda[MAX+1];

    inizializza_queue(coda);

    enqueue(coda,i);

    while(!empty_queue(coda))
    {
        i=dequeue(coda);
        aux[i]=1;

        for(e=g->adj[i]; e; e=e->next)
        {
            if(!aux[e->key])
            {
                enqueue(coda,e->key);
                printf("%d, ", e->key);
                aux[e->key]=1;
            }
        }
    }
}

void bfs(grafo *g)
{
    int i;
    int  *aux=calloc(g->nv, sizeof(int));

    if(aux)
    {
        for(i=0;i<g->nv;i++)
        {
            if(!aux[i])
            {
                printf("\n%d", i+1);
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

    g=new_elem(5);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,0,3,4);
    aggiungi_arco(g,1,2,1);
    aggiungi_arco(g,1,4,3);
    aggiungi_arco(g,2,3,2);
    aggiungi_arco(g,2,4,1);
    aggiungi_arco(g,3,4,4);
    aggiungi_arco(g,4,0,2);

    printf("RISULTATO BFS: \n");
    bfs(g);
    /*
    printf("Risultato DFS: \n");
    dfs(g);
    */

    /*
    printf("STAMPO GRAFO DI ORIGINE: \n");
    stampa_grafo(g);

    g=inserisci(g);

    printf("GRAFO DOPO L'AGGIUNTA DI UN VERTICE: \n");
    stampa_grafo(g);

    cancella_nodo(g,2);

    printf("GRAFO CON NODO N RIMOSSO: \n");
    stampa_grafo(g);
    */
}