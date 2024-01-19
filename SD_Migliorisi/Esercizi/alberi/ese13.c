/*
Dati due alberi binari di ricerca T1 e T2 implementati con la seguente struttura a puntatori:
struct nodo {
int inforadice;
struct nodo *left;
struct nodo *right;}
struct nodo *T1,*T2;
implementare una funzione in linguaggio C che rimuova dall’albero tutti i nodi con valore
inforadice dispari. Poi si costruisca un nuovo albero T in cui inforadice è data dalla
somma dei rispettivi valori inforadice nei nodi corrispondenti.
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
        printf("%d| ", radice->inforadice);
    }
}

albero *rimuovi_dispari(albero *radice)
{
    if(vuoto(radice))
    {
        return NULL;
    }

    radice->sx=rimuovi_dispari(radice->sx);
    radice->dx=rimuovi_dispari(radice->dx);

    if(radice->inforadice%2!=0)
    {
        if(radice->sx!=NULL)
        {
            albero *tmp=radice->sx;
            free(radice);
            return tmp;
        }
        else
        {
            albero *tmp=radice->dx;
            free(radice);
            return tmp;
        }
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

albero *costruisci(albero *t1, albero *t2)
{
    if(vuoto(t1) || vuoto(t2))
    {
        return NULL;
    }

    albero *new_node=(albero *)malloc(sizeof(albero));

    if(new_node)
    {
        new_node->inforadice=t1->inforadice+t2->inforadice;
        new_node->sx=costruisci(t1->sx,t2->sx);
        new_node->dx=costruisci(t1->dx,t2->dx);
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return new_node;
}

int main()
{
    albero *t1=NULL;
    albero *t2=NULL;

    printf("GENERO ALBERO T1: \n");
    new_albero(&t1);

    printf("GENERO ALBERO T2: \n");
    new_albero(&t2);

    printf("VISUALIZZO IN ORDINE ALBERO T1: \n");
    visita_ordine(t1);

    printf("\n");

    printf("VISUALIZZO IN ORDINE ALBERO T2: \n");
    visita_ordine(t2);

    printf("\n");

    t1=rimuovi_dispari(t1);

    t2=rimuovi_dispari(t2);

    printf("VISUALIZZO IN ORDINE ALBERO T1 MODIFICATO: \n");
    visita_ordine(t1);

    printf("\n");

    printf("VISUALIZZO IN ORDINE ALBERO T2 MODIFICATO: \n");
    visita_ordine(t2);

    printf("COSTRUISCO IL NUMERO ALBERO T: \n");
    albero *t=costruisci(t1,t2);

    printf("STAMPO NUOVO ALBERO T: \n");
    visita_ordine(t);

    printf("\n");
}