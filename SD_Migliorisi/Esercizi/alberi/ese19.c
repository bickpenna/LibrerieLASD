/*
Presi due ABR, si costruisca un albero binario che sommi i valori posti nelle stesse 
posizioni (se esistenti). Inoltre trasformare l'albero ottenuto in ternario in modo che il 
terzo nodo, aggiunto senza figli, abbia il valore medio dei fratelli esistenti nell'albero 
binario.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

struct el_bin
{
    struct el_bin *sx;
    int inforadice;
    struct el_bin *dx;
};
typedef struct el_bin albero;

int vuoto(albero *radice)
{
    if(radice) return 0;
    else return 1;
}

albero *new_elem(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;

    tmp=(albero *)malloc(sizeof(albero ));

    if(tmp)
    {
        tmp->sx=sx;
        tmp->inforadice=inforadice;
        tmp->dx=dx;
    }
    else
    {
        printf("Errore di allcazione\n");
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

void visita_ordine(albero *radice)
{
    if(radice)
    {
        visita_ordine(radice->sx);
        printf("%d ", radice->inforadice);
        visita_ordine(radice->dx);
    }
}

albero *somma(albero *a1, albero *a2)
{
    if(vuoto(a1) || vuoto(a2))
    {
        return NULL;
    }

    int valore1, valore2;

    if(a1!=NULL)
    {
        valore1=a1->inforadice;
    }
    else
    {
        valore1=0;
    }

    if(a2!=NULL)
    {
        valore2=a2->inforadice;
    }
    else
    {
        valore2=0;
    }

    albero *nuovo_nodo=new_elem(NULL,valore1+valore2,NULL);

    if(a1!=NULL)
    {
        nuovo_nodo->sx=somma(a1->sx, (a2!=NULL) ? a2->sx : NULL);
        nuovo_nodo->dx=somma(a1->dx, (a2!=NULL) ? a2->dx : NULL);
    }
    else
    {
        nuovo_nodo->sx=somma(NULL, a2->sx);
        nuovo_nodo->dx=somma(NULL, a2->dx);
    }

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
    albero *a1=NULL;
    albero *a2=NULL;

    printf("CREO E INZIALIZZO GLI ALBERI: \n");

    new_albero(&a1);
    new_albero(&a2);

    visita_ordine(a1);

    printf("\n");

    visita_ordine(a2);

    printf("\n");

    albero *a3=somma(a1,a2);

    visita_ordine(a3);
}