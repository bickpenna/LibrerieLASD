/*
Scrivere una funzione in linguaggio C che preso in input 
un albero binario con n elementi valuti in tempo O(n) 
se l albero è un ABR
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

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

int main()
{
    albero *abr=NULL;

    new_albero(&abr);

    visita_ordine(abr);

    if(is_abr(abr))
    {
        printf("L'albero è un ABR");
    }
    else
    {
        printf("L'albero non è un ABR");
    }
}
