/*
Siano T un albero binario di ricerca di interi. Verificare che in T, per ogni elemento numerico (eccetto il
massimo) ci sia il suo successore numerico. Per esempio l'albero con 3,4,e 5 va bene, mentre 3,4, e 7 no!
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

    return 1;
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
            aux->dx=NULL;
            aux->inforadice=el;
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

int ricerca(albero *radice, int val)
{
    int trovato;

    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice==val)
    {
        return 1;
    }
    else if(radice->inforadice > val)
    {
        trovato=ricerca(radice->sx,val);
    }
    else if(radice->inforadice < val)
    {
        trovato=ricerca(radice->dx,val);
    }

    return trovato;
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

int check_successore(albero *radice, int *prev_val) {
    if (vuoto(radice)) {
        return 1;
    }

    if (!check_successore(radice->sx, prev_val)) {
        return 0;
    }

    if (radice->inforadice <= *prev_val) {
        return 0;
    }

    *prev_val = radice->inforadice;

    if (!check_successore(radice->dx, prev_val)) {
        return 0;
    }

    return 1;
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

    printf("ALBERO : \n");
    visita_ordine(abr);
    printf("\n");

    int prev_val=INT_MIN;

    if(check_successore(abr,&prev_val))
    {
        printf("Ogni elemento ha il suo successore numerico\n");
    }
    else
    {
        printf("Non tutti gli elementi hanno il loro successore numerico\n");
    }

    return 0;
}

