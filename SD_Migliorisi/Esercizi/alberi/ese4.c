/*
Dato un albero binario di ricerca, i cui nodi sono caratterizzati da chiavi intere, e dato un intero k,
scrivere una funzione ricorsiva che verifichi che k sia nell’albero, e se c’è restituisca la chiave minima
del sottoalbero radicato in k
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

int ricerca_minimo(albero *radice)
{
    int minimo=0;

    if(radice->sx==NULL)
    {
        minimo=radice->inforadice;
    }
    else
    {
        minimo=ricerca_minimo(radice->sx);
    }

    return minimo;
}

int ricerca_elemento(albero *radice, int k)
{
    int trovato=0;

    if(vuoto(radice))
    {
        return 0;
    }

    if(radice->inforadice==k)
    {
        return 1;
    }
    else if(radice->inforadice > k)
    {
        trovato=ricerca_elemento(radice->sx,k);
    }
    else if(radice->inforadice < k)
    {
        trovato=ricerca_elemento(radice->dx,k);
    }

    return trovato;
}

int minimo_subtree__k(albero *radice, int k)
{
    if(!vuoto(radice))
    {
        if(radice->inforadice==k)
        {
            return ricerca_minimo(radice);
        }
        else if(radice->inforadice<k)
        {
            return minimo_subtree__k(radice->dx,k);
        }
        else if(radice->inforadice>k)
        {
            return minimo_subtree__k(radice->sx,k);
        }
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
    int k;
    int min;
    albero *abr=NULL;

    new_albero(&abr);

    printf("ABR: \n");
    visita_ordine(abr);

    printf("Inserisci valore da cercare nell'albero:  ");
    scanf("%d", &k);

    if(ricerca_elemento(abr, k))
    {
        printf("Elemento %d trovato \n", k);
    }
    else
    {
        printf("Elemento non trovato\n");
    }

    min=minimo_subtree__k(abr,k);

    printf("\nIl minimo del sottoalbero radicato è: %d",min);

}
