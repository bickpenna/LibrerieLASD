/*
scrivere una funzione che dato un abr T, verifichi che T sia un ABR 
e costrusci un albero t1 in modo che per ogni nodo in T che abbia entrambi i figli
, si aggiunge a t1 un terzo figlio middle, che è un nodo foglia,
contenente la somma delle chiavi dei due fratelli
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
        tmp->inforadice=inforadice;
        tmp->dx=dx;
    }
    else
    {
        printf("Errore di allocazione\n");
    }
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
    return is_abr_ric(radice,INT_MIN,INT_MAX);
}

albero_ternario *costruisci(albero *t)
{
    if(vuoto(t))
    {
        return NULL;
    }

    albero_ternario *new_node=(albero_ternario *)malloc(sizeof(albero_ternario));

    if(new_node)
    {
        new_node->inforadice=t->inforadice;
        new_node->sx=costruisci(t->sx);
        new_node->middle=NULL;
        new_node->dx=costruisci(t->dx);
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    if(t->sx != NULL && t->dx != NULL)
    {
        int somma=t->sx->inforadice + t->dx->inforadice;

        albero_ternario *middle_node=(albero_ternario *)malloc(sizeof(albero_ternario));

        if(middle_node)
        {
            middle_node->inforadice=somma;
            middle_node->sx=NULL;
            middle_node->dx=NULL;
            middle_node->middle=NULL;
            new_node->middle=middle_node;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }

    return new_node;
}

void print_three(albero_ternario *t)
{
    if(t)
    {
        printf("%d| ", t->inforadice);
        print_three(t->sx);
        print_three(t->middle);
        print_three(t->dx);
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

int main()
{
    albero *abr=NULL;

    printf("GENERO ALBERO T1: \n");
    new_albero(&abr);

    printf("VISUALIZZO IN ORDINE T1: \n");
    visita_ordine(abr);

    printf("\n");

    printf("COSTRUISCO ALBERO TERNARIO T\n");
    albero_ternario *t=costruisci(abr);

    printf("VISUALIZZO IN ORDINE IL NUOVO ALBERO TERNARIO: \n");
    print_three(t);   
}