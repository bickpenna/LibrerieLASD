/*
Dato un albero binari di ricerca T implementato con la seguente struttura a puntatori:
struct nodo {
int inforadice;
struct nodo *left;
struct nodo *right;}
struct nodo *T;
implementare una funzione in linguaggio C ricorsiva che, dato un intero n di valore
massimo pari a quello della profondità dell’albero, restituisca l’elenco orizzontale di tutti i
nodi di livello n indicando raggruppandoli per nonni.
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

void nodi_livello_n(albero *radice, int livello, int n)
{
    if(vuoto(radice))
    {
        return;
    }

    if(livello==n)
    {
        printf("%d ", radice->inforadice);
    }

    nodi_livello_n(radice->sx, livello+1, n);
    nodi_livello_n(radice->dx, livello+1, n);
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
    

    printf("GENERO ALBERO: \n");
    new_albero(&abr);

    printf("VISUALIZZO IN ORDINE L'ALBERO: \n");
    visita_ordine(abr);
    printf("\n");

    printf("NODI DI LIVELLO 2 RAGGRUPPATI PER NONNI: ");
    nodi_livello_n(abr,0,2);
    printf("\n");
}