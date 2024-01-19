/*
si considerino due alberi binari di ricerca T1 e T2. 
dopo aver verificato che sono entrambi alberi binari di ricerca, verificare che T1 è un sottoalbero di T2.
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
        printf("%d |", radice->inforadice);
        visita_preordine(radice->sx);
        visita_preordine(radice->dx);
    }
}

void visita_ordine(albero *radice)
{
    if(radice)
    {
        visita_ordine(radice->sx);
        printf("%d |", radice->inforadice);
        visita_ordine(radice->dx);
    }
}

void visita_postordine(albero *radice)
{
    if(radice)
    {
        visita_postordine(radice->sx);
        visita_postordine(radice->dx);
        printf("%d |", radice->inforadice);
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

    return is_abr_ric(radice->sx, min, radice->inforadice-1) && is_abr_ric(radice->dx, radice->inforadice+1, max);
}

int is_abr(albero *radice)
{
    return is_abr_ric(radice, INT_MIN, INT_MAX);
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

    printf("GENERO ALBERO T1: \n");
    new_albero(&t1);

    printf("GENERO ALBERO T2: \n");
    new_albero(&t2);

    printf("VISUALIZZO ALBERO T1: \n");
    visita_ordine(t1);

    printf("\n");

    printf("VISUALIZZO ALBERO T2: \n");
    visita_ordine(t2);

    printf("\n");

    if(is_subtree(t1,t2))
    {
        printf("T1 è un sottoalbero di T2.\n");
    }
    else
    {
        printf("T1 non è n sottoalbero di T2.\n");
    }
}
