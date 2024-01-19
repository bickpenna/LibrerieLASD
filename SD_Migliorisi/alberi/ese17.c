/*
2. Dato un ABR, trovare il minimo ed il secondo minimo del sottoalbero radicato in k (5pt), 
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

int vuoto(albero *rad)
{
    if(rad) return 0;
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
    else if( radice->inforadice < el)
    {
        radice->dx=inserisci(radice->dx,el);
    }
    else if(radice->inforadice > el)
    {
        radice->sx=inserisci(radice->sx,el);
    }

    return radice;
}

void visita_preordine(albero *radice)
{
    if(radice)
    {
        printf("%d ", radice->inforadice);
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
        printf("%d ",radice->inforadice);
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

int minimo_subtree(albero *radice, int k)
{
    if(!vuoto(radice))
    {
        if(radice->inforadice==k)
        {
            return ricerca_minimo(radice);
        }
        else if(radice->inforadice < k)
        {
            return minimo_subtree(radice->dx, k);
        }
        else if(radice->inforadice > k)
        {
            return minimo_subtree(radice->sx, k);
        }
    }

    return -1;
}

void ricerca_secondo_minimo(albero *radice, int *min1, int *min2)
{
    if(vuoto(radice))
    {
        return;
    }

    if(radice->inforadice < *min1)
    {
        *min2 = *min1;
        *min1=radice->inforadice;
    }
    else if(radice->inforadice > *min1 && radice->inforadice < *min2)
    {
        *min2 =radice->inforadice;
    }

    ricerca_secondo_minimo(radice->sx, min1, min2);
    ricerca_secondo_minimo(radice->dx, min1, min2);
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
    else if(radice->inforadice > r)
    {
        trovato=ricerca(radice->sx,r);
    }
    else if(radice->inforadice < r)
    {
        trovato=ricerca(radice->dx,r);
    }

    return trovato;
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

    visita_preordine(abr);

    int min=ricerca_minimo(abr);

    printf("\nIl minimo è %d\n", min);

    int k;

    printf("Inserisci un valore da ricercare: ");
    scanf("%d", &k);

    printf("\n");

    if(ricerca(abr, k))
    {
        printf("Elemento %d trovato \n", k);
    }
    else
    {
        printf("Elemento non trovato\n");
    }

    int min_sub=minimo_subtree(abr, k);

    printf("Il minimo del sottoalbero radice in %d è %d\n", k, min_sub);

}