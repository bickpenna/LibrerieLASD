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

void modifica_peso_arco(grafo *g, int u, int v, int nuovo_peso)
{
    arco *tmp=g->adj[u];

    if(tmp==NULL)
    {
        return;
    }

    while(tmp)
    {
        if(tmp->key==v)
        {
            tmp->peso=nuovo_peso;
            break;
        }
        tmp=tmp->next;
    }
}

arco *arco_peso_maggiore(grafo *g)
{
    arco *peso_massimo=NULL;

    for(int i=0;i<g->nv;i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            if(peso_massimo == NULL || e->peso > peso_massimo->peso)
            {
                peso_massimo=e;
            }
            e=e->next;
        }
    }

    return peso_massimo;
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

void stampa_percorso_minimo(int *prev, int sorgente, int dest)
{
    if(dest==sorgente)
    {
        printf("%d ", sorgente);
    }
    else if(prev[dest]==-1)
    {
        printf("Nessun percorso da %d a %d \n", sorgente, dest);
    }
    else
    {
        stampa_percorso_minimo(prev,sorgente,prev[dest]);
        printf("%d ", dest);
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

grafo *crea_grafo_t(grafo *g, grafo *h)
{
    grafo *t=new_elem(g->nv);

    for(int i=0; i<g->nv; i++)
    {
        arco *e_g=g->adj[i];
        arco *e_h=g->adj[i];

        while(e_g != NULL && e_h != NULL)
        {
            int somma_peso=e_g->peso+e_h->peso;

            if(somma_peso%2==0)
            {
                aggiungi_arco(t,i,e_g->key,somma_peso);
            }

            e_g=e_g->next;
            e_h=e_h->next;
        }
    }

    return t;
}

bool is_tree(grafo *g)
{
    int *in_degrees=(int *)calloc(g->nv,sizeof(int));
    int root_count=0;
    int root=-1;

    for(int i=0; i<g->nv; i++)
    {
        arco *e=g->adj[i];

        while(e!=NULL)
        {
            in_degrees[e->key]++;
            e=e->next;
        }
    }

    for(int i=0; i<g->nv; i++)
    {
        if(in_degrees[i]==0)
        {
            root_count++;
            root=i;
        }
    }

    if(root_count!=1)
    {
        free(in_degrees);
        return false;
    }

    int *visited=(int *)calloc(g->nv,sizeof(int));
    dfs(g);
    dfs1(g,root,visited);

    for(int i=0; i<g->nv; i++)
    {
        if(!visited[i])
        {
            free(in_degrees);
            free(visited);
            return false;
        }
    }

    free(in_degrees);
    free(visited);

    return true;
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

grafo *crea_grafo_t(grafo *g1, grafo *g2)
{
    grafo *t=new_elem(g1->nv);

    for(int i=0; i<g1->nv; i++)
    {
        arco *e_g1=g1->adj[i];
        arco *e_g2=g2->adj[i];

        while(e_g1!=NULL && e_g2!=NULL)
        {
            if((e_g1->peso%2==0 && e_g2->peso%2==0) || (e_g1->peso%2!=0 && e_g2->peso%2!=0))
            {
                int somma_p=e_g1->peso+e_g2->peso;

                aggiungi_arco(t,i,e_g1->key,somma_p);
            }

            e_g1=e_g1->next;
            e_g2=e_g2->next;
        }
    }

    return t;
}

bool is_edge_here(grafo *g, int u, int v)
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

grafo *rimuovi_arco_maggiore(grafo *g, grafo *h)
{
    if (is_empty(g) || is_empty(h))
    {
        return NULL;
    }

    for (int a = 0; a < g->nv; a++)
    {
        arco *eg = g->adj[a];
        arco *eh = h->adj[a];

        while (eg != NULL && eh != NULL)
        {
            if (eg->key == eh->key)
            {
                if (eg->peso > eh->peso)
                {
                    rimuovi_arco(g, a, eg->key);
                }
                else if (eh->peso > eg->peso)
                {
                    rimuovi_arco(h, a, eh->key);
                }

                eg = eg->next;
                eh = eh->next;
            }
            else if (eg->key < eh->key)
            {
                eg = eg->next;
            }
            else
            {
                eh = eh->next;
            }
        }
    }
    return g;
}
