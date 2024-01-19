/*
Siano dati due ABR T1 e T2.
1. Scrivere una funzione che costruisca un albero binario T unione di T1 e T2 nel quale gli elementi di T1 e
T2 che si trovano in posizione uguale sono sommati.
2. Si generi un albero ternario a partire dall’albero costruito nel punto precedente aggiungendo, per ogni
nodo con entrambi i figli, un terzo nodo contenente la media dei due figli
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

struct el_3
{
    struct el_3 *sx;
    int inforadice;
    struct el_3 *middle;
    struct el_3 *dx;
};
typedef struct el_3 albero_ternario;

int vuoto(albero *radice)
{
    if(radice) return 0;
    else return 1;
}

albero *new_elem(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;
    tmp=(albero *)malloc(sizeof(albero));

    if(tmp)
    {
        tmp->sx=sx;
        tmp->dx=dx;
        tmp->inforadice=inforadice;
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
        radice->sx=inserisci(radice->sx, el);
    }
    else if(el > radice->inforadice)
    {
        radice->dx=inserisci(radice->dx, el);
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
    albero *t1=NULL;
    albero *t2=NULL;
    albero *t=NULL;

    new_albero(&t1);

    new_albero(&t2);

    visita_ordine(t1);

    visita_ordine(t2);

    t=unisci_alberi(t1,t2);

    visita_ordine(t);
}