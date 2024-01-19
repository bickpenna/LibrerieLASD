/*
Dati due alberi binari di ricerca T1 e T2 implementati con la seguente struttura a puntatori:
struct nodo {
int inforadice;
struct nodo *left;
struct nodo *right;}
struct nodo *T1,*T2;
implementare una funzione che rimuova da T1 tutti i nodi con valore inforadice minore
della metà della somma dei suoi figli e da T2 quelli con valore maggiore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

struct el
{
    struct el *sx;
    int inforadice;
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

    if(!vuoto(radice))
    {
        *val=radice->inforadice;
        ok=1;
    }

    return ok;
}

albero *new_elem(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;
    tmp=(albero *)malloc(sizeof(albero));

    if(tmp)
    {
        tmp->sx=sx;
        tmp->inforadice=inforadice;
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
            aux->sx=NULL;
            aux->inforadice=el;
            aux->dx=NULL;
            radice=aux;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }
    else if(el < radice->inforadice)
    {
        radice->sx=inserisci(radice->sx,el);
    }
    else if(el > radice->inforadice)
    {
        radice->dx=inserisci(radice->dx,el);
    }

    return radice;
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

albero *remove_from_T1(albero *radice)
{
    if(vuoto(radice))
    {
        return NULL;
    }

    radice->sx=remove_from_T1(radice->sx);
    radice->dx=remove_from_T1(radice->dx);

    int somma_figli=0;

    if(radice->sx!=NULL)
    {
        somma_figli+=radice->sx->inforadice;
    }

    if(radice->dx!=NULL)
    {
        somma_figli+=radice->dx->inforadice;
    }

    if(radice->inforadice < somma_figli/2)
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

int main() 
{
    albero *T1 = NULL;
    albero *T2 = NULL;

    printf("Inserimento elementi in T1:\n");
    new_albero(&T1);

    printf("\nInserimento elementi in T2:\n");
    new_albero(&T2);

    printf("\nAlbero T1 prima della rimozione:\n");
    visita_ordine(T1);

    T1 = remove_from_T1(T1);

    printf("\nAlbero T1 dopo la rimozione:\n");
    visita_ordine(T1);

    /*
    printf("\nAlbero T2 prima della rimozione:\n");
    visita_ordine(T2);

    T2 = remove_from_T2(T2);

    printf("\nAlbero T2 dopo la rimozione:\n");
    visita_ordine(T2);
    */
   
    return 0;
}