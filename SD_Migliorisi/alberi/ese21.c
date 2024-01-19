/*
Dato un ABR, trovare il minimo ed il secondo minimo del sottoalbero radicato in k (5pt),
 e poi rimuovere il secondo minimo mantenendo le proprietà di ABR (5pt)
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
    else if (el < radice->inforadice)
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
        printf("%d ", radice->inforadice);
        visita_ordine(radice->dx);
    }
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

int ricerca_secondo_minimo(albero *radice, int *secondominimo)
{
    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->sx!=NULL)
    {
        *secondominimo=radice->inforadice;
        return ricerca_secondo_minimo(radice->sx,secondominimo);
    }
    else
    {
        return radice->inforadice;
    }
}

int minimo_subtree(albero *radice, int k)
{
    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice==k)
    {
        return ricerca_minimo(radice);
    }
    else if(k < radice->inforadice)
    {
        return minimo_subtree(radice->sx,k);
    }
    else if(k > radice->inforadice)
    {
        return minimo_subtree(radice->sx,k);
    }
}

int main()
{
    albero *abr=NULL;

    new_albero(&abr);

    visita_ordine(abr);

    int s_min=ricerca_secondo_minimo(abr,&s_min);

    printf("%d \n", s_min);
}
