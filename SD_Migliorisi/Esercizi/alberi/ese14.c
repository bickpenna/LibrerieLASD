/*
scrivere una funzione che dato un abr verifichi che esso sia abr, e una funzione che dat0 un x 
restituisca la chiave minima del sottoalbero radicato in x
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
        printf("%d| ", radice->inforadice);
        visita_preordine(radice->sx);
        visita_preordine(radice->dx);
    }
}

void visita_ordine(albero *radice)
{
    if(radice)
    {
        visita_ordine(radice->sx);
        printf("%d| ", radice->inforadice);
        visita_ordine(radice->dx);
    }
}

void visita_postordine(albero *radice)
{
    if(radice)
    {
        visita_postordine(radice->sx);
        visita_postordine(radice->dx);
        printf("%d| ", radice->inforadice);
    }
}

int ricerca_minimo(albero *radice)
{
    int min=0;

    if(!vuoto(radice))
    {
        if(radice->sx==NULL)
        {
            min=radice->inforadice;
        }
        else
        {
            min=ricerca_minimo(radice->sx);
        }
    }
    return min;
}

int minimo_sottoalbero_radicato_k(albero *radice, int k)
{
    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice==k)
    {
        return ricerca_minimo(radice);
    }
    else if(radice->inforadice < k)
    {
        return minimo_sottoalbero_radicato_k(radice->dx,k);
    }
    else if(radice->inforadice > k)
    {
        return minimo_sottoalbero_radicato_k(radice->sx,k);
    }
    return -1;
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

    return is_abr_ric(radice->sx, min, radice->inforadice-1) && is_abr_ric(radice->dx, radice->inforadice+1, max);
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

int main()
{
    albero *abr=NULL;
    int k,min;

    printf("GENERO ALBERO: \n");
    new_albero(&abr);

    printf("VISUALIZZO IN ORDINE L'ALBERO: \n");
    visita_ordine(abr);

    printf("\nInserisci elemento k: ");
    scanf("%d", &k);

    min=minimo_sottoalbero_radicato_k(abr,k);

    printf("\nIl minimo del sotto albero radicato in %d è %d\n", k, min);

}