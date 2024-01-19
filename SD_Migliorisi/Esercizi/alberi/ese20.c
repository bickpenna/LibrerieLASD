/*
Dato un albero e una chiave k, scrivere una funzione che verifichi che 
l'albero sia binario di ricerca, e restituisca il valore minimo del sottoablero 
radiceato in k
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
    else if( el < radice->inforadice)
    {
        radice->sx=inserisci(radice->sx,el);
    }
    else if( el > radice->inforadice)
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

int is_ABR_ric(albero *radice, int min, int max)
{
    if(vuoto(radice))
    {
        return 1; //true
    }

    if(radice->inforadice < min || radice->inforadice > max)
    {
        return 0; //false
    }

    return is_ABR_ric(radice->sx, min, radice->inforadice -1) && is_ABR_ric(radice->dx, radice->inforadice+1, max);

}

int is_ABR(albero *radice)
{
    return is_ABR_ric(radice, INT_MIN, INT_MAX);
}

int min_subtree_k(albero *radice, int k)
{
    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice == k)
    {
        return ricerca_minimo(radice);
    }
    
    if(k < radice->inforadice)
    {
        return min_subtree_k(radice->sx,k);
    }

    if(k > radice->inforadice)
    {
        return min_subtree_k(radice->dx,k);
    }

    return -1;
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

    printf("STAMPO ABR: \n");
    visita_ordine(abr);

    printf("\n");

    if(is_ABR(abr))
    {
        printf("L'albero inserito è un abr\n");
    }
    else
    {
        printf("FALSE!\n");
    }

    int k;

    printf("Inserisci K per subtree_function: ");
    scanf("%d", &k);

    int min_sottoalbero=min_subtree_k(abr, k);

    printf("Il minimo del sottoalbero radicato in %d è %d\n", k, min_sottoalbero);
}
