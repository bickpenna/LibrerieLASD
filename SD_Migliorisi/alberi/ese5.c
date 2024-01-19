/*
Dato un albero,implementa una funzione che rimuove dall’albero tutti i nodi
con valore info radice minore della metà della somma dei figli.
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
    albero *abr=NULL;

    new_albero(&abr);

    printf("ALBERO ORIGINALE: \n");
    visita_ordine(abr);

    int somma=somma_figli(abr);
    printf("la somma è %d\n", somma);

    abr=rimuovi_nodo(abr);
}

