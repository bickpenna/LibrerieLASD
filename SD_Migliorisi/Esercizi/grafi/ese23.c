/*
3. Dato un grafo pesato, implementare queste funzioni:
3a. Rimuovere l'arco col peso minimo
3b. Dato un vertice, calcolarne il grado adiacente ed incidente
3. Generare un nuovo grafo G2 che è il trasposto del grafo originale
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

    g=(grafo *)malloc(sizeof(grafo ));

    if(g)
    {
        g->adj=(arco **)malloc(nv*sizeof(arco *));

        if(g->adj)
        {
            g->nv=nv;

            for(i=0;i<g->nv;i++)
            {
                g->adj[i]==NULL;
            }
        }
        else
        {
            printf("Errore di autenticazione\n");
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

arco *arco_peso_minimo(grafo *g, int *out_u, int *out_v)
{
    int peso_minimo = INT_MAX;
    int u = -1;
    int v = -1;
    arco *min_arco = NULL;

    for (int i = 0; i < g->nv; i++)
    {
        arco *e = g->adj[i];

        while (e != NULL)
        {
            if (e->peso < peso_minimo)
            {
                peso_minimo = e->peso;
                u = i;
                v = e->key;
                min_arco = e;
            }

            e = e->next;
        }
    }

    *out_u = u;
    *out_v = v;
    return min_arco;
}

void rimuovi_arco_peso_minimo(grafo *g)
{
    int u, v;
    arco *min_arco = arco_peso_minimo(g, &u, &v);

    if (min_arco != NULL)
    {
        rimuovi_arco(g, u, v);
    }
    else
    {
        printf("Nessun arco presente nel grafo\n");
    }
}

int grado_entrante(grafo *g, int nodo)
{
    int grado=0;

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            if(e->key==nodo)
            {
                grado++;
            }
            
            e=e->next;
        }
    }

    return grado;
}

grafo *trasposto_grafo(grafo *g)
{
    grafo *gt=(grafo *)malloc(sizeof(grafo));

    if(gt)
    {
        gt->nv=g->nv;
        gt->adj=(arco **)malloc(gt->nv*sizeof(arco *));

        if(gt->adj)
        {
            for(int i=0; i<gt->nv; i++)
            {
                gt->adj[i]=NULL;
            }

            for(int i=0; i<g->nv; i++)
            {
                arco *tmp=g->adj[i];
                
                while(tmp)
                {
                    aggiungi_arco(gt,tmp->key,i,tmp->peso);
                    tmp=tmp->next;
                }
            }
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }

    return gt;
}

int grado_uscente(grafo *g, int nodo)
{
    int grado=0;

    arco *e=g->adj[nodo];

    while(e!=NULL)
    {
        grado++;
        e=e->next;
    }

    return grado;
}

int main()
{
    grafo *g=NULL;

    int u,v;

    g=new_elem(5);

    aggiungi_arco(g, 0, 1, 3);
    aggiungi_arco(g, 1, 2, 2);
    aggiungi_arco(g, 2, 3, 1);
    aggiungi_arco(g, 3, 4, 4);
    aggiungi_arco(g, 4, 0, 2);

    stampa_grafo(g);

    printf("\n");

    arco *min=arco_peso_minimo(g,&u,&v);

    if (min != NULL)
    {
        printf("Arco con peso minimo va da %d a %d con peso %d\n", u, v, min->peso);
    }
    else
    {
        printf("Nessun arco presente nel grafo\n");
    }

    printf("\n");

    rimuovi_arco_peso_minimo(g);

    stampa_grafo(g);

    printf("\n\n");

    int nodo=4;

    int ge=grado_entrante(g,nodo);
    int gu=grado_uscente(g,nodo);

    printf("IL GRADO ENTRANTE E USCENTE DI %d sono %d , %d \n",nodo,ge,gu);

    printf("\n");

    grafo *gt=trasposto_grafo(g);

    stampa_grafo(gt);
}