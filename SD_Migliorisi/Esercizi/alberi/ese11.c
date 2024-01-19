/*
Dato un albero binario di ricerca T implementato con la seguente struttura a puntatori:
struct nodo {
int inforadice;
struct nodo *left;
struct nodo *right;}
struct nodo *T;
implementare una funzione in linguaggio C ricorsiva che rimuova tutti ogni nodo con
valore negativo dall’albero T e il suo sottoalbero destro. Dunque, per ogni nodo rimosso, il
suo sottoalbero sinistro diventa sottoalbero sinistro di suo padre.
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

albero *remove_node(albero *radice)
{
    if(vuoto(radice))
    {
        return NULL;
    }

    radice->sx=remove_node(radice->sx);
    radice->dx=remove_node(radice->dx);

    if(radice->inforadice<0)
    {
        albero *left_subtree=radice->sx;
        free(radice);
        return left_subtree;
    }

    return radice;
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

    printf("GENERO L'ALBERO: \n");
    new_albero(&abr);

    printf("VISUALIZZO IN ORDINE L'ALBERO: \n");
    visita_ordine(abr);

    printf("\nEFFETTUO OPERAZIONE: \n");
    abr=remove_node(abr);

    printf("\nVISUALIZZO L'ALBERO MODIFICATO: \n");
    visita_ordine(abr);

    printf("\n");
}