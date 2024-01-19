/*
Dato un grafo pesato, implementare queste funzioni:
3a. Rimuovere l'arco col peso minimo
3b. Dato un vertice, calcolarne il grado adiacente ed incidente
Generare un nuovo grafo G2 che è il trasposto del grafo originale
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
                grado ++;
            }
            e=e->next;
        }
    }

    return grado;
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

grafo *trasposto_grafo(grafo *g)
{
    grafo *gt=(grafo *)malloc(sizeof(grafo));

    if(gt)
    {
        gt->nv=g->nv;
        gt->adj=(arco **)malloc(g->nv*sizeof(arco *));

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
            free(gt);
            gt=NULL;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return gt;
}

arco *peso_minimo(grafo *g)
{
    arco *peso_minimo=NULL;

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            if(peso_minimo==NULL || e->peso < peso_minimo->peso)
            {
                peso_minimo=e;
            }
            e=e->next;
        }
    }

    return peso_minimo;
}

void rimuovi_arco(grafo *g, int u, int v)
{
    arco *e;
    arco *prev;

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

void rimuovi_arco_peso_minimo(grafo *g)
{
    arco *min_arco=peso_minimo(g);

    if(min_arco==NULL)
    {
        printf("Nessun arco presente nel grafo\n");
        return;
    }

    int u;
    min_arco=g->adj[u];
    int v=min_arco->key;

    rimuovi_arco(g,u,v);

    printf("Rimosso l'arco con peso minimo: (%d, %d) con peso %d\n", u, v, min_arco->peso);
}

int main()
{
    grafo *g=NULL;

    g=new_elem(4);

    aggiungi_arco(g,0,1,2);
    aggiungi_arco(g,0,2,4);
    aggiungi_arco(g,1,3,4);
    aggiungi_arco(g,1,2,5);
    aggiungi_arco(g,2,3,3);

    stampa_grafo(g);

    arco *peso_min=peso_minimo(g);

    printf("Larco con il peso minimo  ha chiave %d e ha peso %d\n", peso_min->key, peso_min->peso);

    printf("\n");

   // rimuovi_arco_peso_minimo(g);
   //  stampa_grafo(g);

    int nodo;  
    printf("Inserisci nodo di cui vuoi sapre grado entrante e uscente: \n");
    scanf("%d", &nodo);

    if(nodo>g->nv)
    {
        printf("HAI SUPERATO IL LIMITE\n");
        return -1;
    }
    else
    {
        int gu=grado_uscente(g,nodo);
        int ge=grado_entrante(g,nodo);

        printf("GRADO ENTRANTE : %d\nGRADO USCENTE : %d\n",ge,gu);
    }

    return 0;
}