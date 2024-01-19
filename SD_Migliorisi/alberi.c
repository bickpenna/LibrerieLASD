struct el
{
    int inforadice;
    struct el *sx;
    struct el *dx;
};
typedef struct el albero;

int vuoto(albero *radice)
{
    if(radice) return 0;
    else return 1;
}

int radice(albero *radice, int *val)
{
    int ok=0;

    if (!vuoto(radice))
    {
        *val=radice->inforadice;
        ok=1;
    }

    return ok;
}

albero *sx(albero *radice)
{
    albero *result=NULL;

    if(!vuoto(radice))
    {
        result=radice->sx;
    }
    
    return NULL;
}

albero *dx(albero *radice)
{
    albero *result=NULL;

    if(!vuoto(radice))
    {
        result=radice->dx;
    }

    return NULL;
}

albero *new_elem(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;
    tmp=(albero *)malloc(sizeof(albero));

    if(tmp)
    {
        tmp->inforadice=inforadice;
        tmp->sx=sx;
        tmp->dx=dx;
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return tmp;
}

albero *inserisci(albero *radice, int el)
{
	albero *aux;

	if(vuoto(radice))
	{
		aux=(albero *)malloc(sizeof(albero));
		if(aux)
		{
			aux->inforadice=el;
			aux->sx=NULL;
			aux->dx=NULL;
			radice=aux;
		}
		else
		{
			printf("Memoria non allocata\n");
		}
	}
	else if(el<radice->inforadice)
	{
		radice->sx=inserisci(radice->sx,el);
	}
	else if(el>radice->inforadice)
	{
		radice->dx=inserisci(radice->dx,el);
	}

	return radice;
}

void visita_preordine(albero *radice)
{
    if(radice)
    {
        printf("%d|", radice->inforadice);
        visita_preordine(radice->sx);
        visita_preordine(radice->dx);
    }
}

void visita_ordine(albero *radice)
{
    if(radice)
    {
        visita_ordine(radice->sx);
        printf("%d|", radice->inforadice);
        visita_ordine(radice->dx);
    }
}

void visita_postordine(albero *radice)
{
    if(radice)
    {
        visita_postordine(radice->sx);
        visita_postordine(radice->dx);
        printf("%d|", radice->inforadice);
    }
}

int is_abr_ric(albero *radice, int min, int max)
{
    if(vuoto(radice))
    {
        return 1;
    }

    if(radice->inforadice < min || radice->inforadice > max)
    {
        return 0;
    }

    return is_abr_ric(radice->sx, min, radice->inforadice -1) && is_abr_ric(radice->dx, radice->inforadice +1, max);
}

int is_abr(albero *radice)
{
    return is_abr_ric(radice, INT_MIN, INT_MAX);
}

void new_albero(albero **radice) 
{
    int elementi;
    int val;

    printf("Quanti elementi si vogliono inserire? ");
    scanf("%d", &elementi);

    for (int i = 0; i < elementi; i++) 
    {
        printf("\nInserire elemento numero %d: ", i + 1);
        scanf("%d", &val);

        *radice=inserisci(*radice, val);
    }
}

int ricerca(albero *radice, int r)
{
    int trovato=0;

    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice==r)
    {
        return 1;
    }
    else if(radice->inforadice>r)
    {
        trovato=ricerca(radice->sx,r);
    }
    else if(radice->inforadice<r)
    {
        trovato=ricerca(radice->dx,r);
    }

    return trovato;
}

int ricerca_minimo(albero *radice)
{
    int minimo=0;

    if(!vuoto(radice))
    {
        if(radice->sx==NULL)
        {
            minimo=radice->inforadice;        
        }
        else
        {
            minimo=ricerca_minimo(radice->sx);
        }
    }

    return minimo;
}

void elimina(albero **radice, int el)
{
    albero *aux;
    aux=*radice;

    if(vuoto(*radice))
    {
        return;
    }

    if((*radice)->inforadice > el)
    {
        elimina(&((*radice)->sx),el);
    }
    else if((*radice)->inforadice < el)
    {
        elimina(&((*radice)->dx),el);
    }
    else
    {
        if(!((*radice)->sx) && (!((*radice)->dx)))
        {
            free(*radice);
            *radice=NULL;
        }
        else if(((*radice)->sx)&& (!((*radice)->dx)))
        {
            *radice=aux->sx;
        }
        else if(!((*radice)->sx) && ((*radice)->dx))
        {
            *radice=aux->dx;
        }
        else if((aux->dx == NULL) || (aux->sx == NULL))
        {
            free(aux);
            return;
        }
        else if(((*radice)->sx) && ((*radice)->dx))
        {
            (*radice)->inforadice=ricerca_minimo((*radice)->dx);
            elimina(&(*radice)->dx, (*radice)->inforadice);
        }
    }
}

void sottrai_minimo(albero *radice, int minimo)
{
    if(vuoto(radice))
    {
        return;
    }

    radice->inforadice-=minimo;

    sottrai_minimo(radice->sx,minimo);
    sottrai_minimo(radice->dx,minimo);
}

int minimo_subtree__k(albero *radice, int k)
{
    if(!vuoto(radice))
    {
        if(radice->inforadice==k)
        {
            return ricerca_minimo(radice);
        }
        else if(radice->inforadice<k)
        {
            return minimo_subtree__k(radice->dx,k);
        }
        else if(radice->inforadice>k)
        {
            return minimo_subtree__k(radice->sx,k);
        }
    }
    return -1;
}

int somma_figli(albero *radice)
{
    if(vuoto(radice))
    {
        return 0;
    }

    int somma=0;

    if(radice->sx!=NULL)
    {
        somma+=radice->sx->inforadice;
    }

    if(radice->dx!=NULL)
    {
        somma+=radice->dx->inforadice;
    }

    somma+=somma_figli(radice->sx);
    somma+=somma_figli(radice->dx);

    return somma;
}

albero *rimuovi_nodo(albero *radice)
{
    if(vuoto(radice))
    {
        return NULL;
    }

    radice->sx=rimuovi_nodo(radice->sx);
    radice->dx=rimuovi_nodo(radice->dx);

    int sum=somma_figli(radice);

    if(radice->inforadice < sum/2);
    {
        albero *tmp;
        if(radice->sx!=NULL)
        {
            tmp=radice->sx;
        }
        else
        {
            tmp=radice->dx;
        }

        free(radice);
        return tmp;
    }

    return radice;
}

albero_ternario *costruisci_albero_ternario(albero_ternario *t, albero *t1, albero *t2)
{
    if(vuoto(t1) || vuoto(t2))
    {
        return NULL;
    }

    albero_ternario *new_node=(albero_ternario *)malloc(sizeof(albero_ternario));
    
    if(new_node)
    {
        new_node->inforadice=t1->inforadice;
        new_node->sx=costruisci_albero_ternario(new_node->sx,t1->sx,t2->sx);
        new_node->middle=NULL;
        new_node->dx=costruisci_albero_ternario(new_node->dx,t1->dx,t2->dx);

        if(t1->inforadice==t2->inforadice)
        {
            new_node->middle=(albero_ternario *)malloc(sizeof(albero_ternario));
            new_node->middle->inforadice=1;
            new_node->middle->sx=NULL;
            new_node->middle->middle=NULL;
            new_node->middle->dx=NULL;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return new_node;
}

void print_three(albero_ternario *radice)
{
    if(radice)
    {
        printf("%d|", radice->inforadice);
        print_three(radice->sx);
        print_three(radice->middle);
        print_three(radice->dx);
    }
}

albero* unisci_alberi(albero* T1, albero* T2) {
    if (T1 == NULL && T2 == NULL) {
        return NULL;
    }

    albero* nuovo_nodo = (albero*)malloc(sizeof(albero));
    nuovo_nodo->inforadice = (T1 ? T1->inforadice : 0) + (T2 ? T2->inforadice : 0);
    nuovo_nodo->sx = unisci_alberi(T1 ? T1->sx : NULL, T2 ? T2->sx : NULL);
    nuovo_nodo->dx = unisci_alberi(T1 ? T1->dx : NULL, T2 ? T2->dx : NULL);

    return nuovo_nodo;
}

albero *costruisci_T(albero *t1, albero *t2)
{
    if(vuoto(t1) || vuoto(t2))
    {
        return NULL;
    }

    albero *new=(albero *)malloc(sizeof(albero));

    if(new)
    {
        if(!vuoto(t1))
        {
            new->inforadice=t1->inforadice;
            new->sx=costruisci_T(t1->sx,NULL);
            new->dx=costruisci_T(t1->dx,NULL);
        }
        else if(!vuoto(t2))
        {
            new->inforadice=t2->inforadice;
            new->sx=costruisci_T(NULL, t2->sx);
            new->dx=costruisci_T(NULL, t2->dx);
        }
        else
        {
            new->inforadice=0;
            new->sx=new->dx=NULL;
        }
    }

    return new;
}

albero_ternario *costruisci(albero *t)
{
    if(vuoto(t))
    {
        return NULL;
    }

    albero_ternario *new_node=(albero_ternario *)malloc(sizeof(albero_ternario));

    if(new_node)
    {
        new_node->inforadice=t->inforadice;
        new_node->sx=costruisci(t->sx);
        new_node->middle=NULL;
        new_node->dx=costruisci(t->dx);
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    if(t->sx != NULL && t->dx != NULL)
    {
        int media=(t->sx->inforadice + t->dx->inforadice)/2;

        albero_ternario *middle_node=(albero_ternario *)malloc(sizeof(albero_ternario));

        if(middle_node)
        {
            middle_node->inforadice=media;
            middle_node->sx=NULL;
            middle_node->dx=NULL;
            middle_node->middle=NULL;
            new_node->middle=middle_node;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }

    return new_node;
}

albero *rimuovi_dispari(albero *radice)
{
    if(vuoto(radice))
    {
        return NULL;
    }

    radice->sx=rimuovi_dispari(radice->sx);
    radice->dx=rimuovi_dispari(radice->dx);

    if(radice->inforadice%2!=0)
    {
        if(radice->sx!=NULL)
        {
            albero *tmp=radice->sx;
            free(radice);
            return tmp;
        }
        else
        {
            albero *tmp=radice->dx;
            free(radice);
            return tmp;
        }
    }

    return radice;
}


albero_ternario *costruisci(albero *t)
{
    if(vuoto(t))
    {
        return NULL;
    }

    albero_ternario *new_node=(albero_ternario *)malloc(sizeof(albero_ternario));

    if(new_node)
    {
        new_node->inforadice=t->inforadice;
        new_node->sx=costruisci(t->sx);
        new_node->middle=NULL;
        new_node->dx=costruisci(t->dx);
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    if(t->sx != NULL && t->dx != NULL)
    {
        int somma=t->sx->inforadice + t->dx->inforadice;

        albero_ternario *middle_node=(albero_ternario *)malloc(sizeof(albero_ternario));

        if(middle_node)
        {
            middle_node->inforadice=somma;
            middle_node->sx=NULL;
            middle_node->dx=NULL;
            middle_node->middle=NULL;
            new_node->middle=middle_node;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }

    return new_node;
}

int is_subtree(albero *t1, albero *t2)
{
    if(vuoto(t1))
    {
        return 1;
    }

    if(vuoto(t2))
    {
        return 0;
    }

    if(t1->inforadice == t2->inforadice && is_subtree(t1->sx,t2->sx) && is_subtree(t1->dx,t2->dx))
    {
        return 1;
    }

    return is_subtree(t1,t2->sx) || is_subtree(t1,t2->dx);
}