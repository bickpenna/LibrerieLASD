/*
Sia T un Albero bianario definito secondo la seguente struttura
struct nodo {
int inforadice;
struct nodo *sx;
struct nodo *dx;}
struct nodo *T;
a. Si implementi la funzione check_ABR che preso solo T verifichi che si tratta di un
ABR.
b. Si implementi una funzione che preso T crei un albero ternario TER (struttura da
definire) in cui sono presenti tutti i nodi di T e in aggiunta si inserisce in TER un figlio
centrale foglia ad ogni nodo che ha entrambi i figli in T e il suo valore sia l'intero media
dei valori dei due figli
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
    struct el *sx;
    int inforadice;
    struct el *middle;
    struct el *dx;
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
        radice->sx=inserisci(radice->sx, el); 
    }
    else if( el > radice->inforadice)
    {
        radice->dx=inserisci(radice->dx, el);
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

int is_abr_ric(albero *radice, int min , int max)
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
    return is_abr_ric(radice, INT_MIN, INT_MAX);
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
        int media=(t->sx->inforadice + t->dx->inforadice)/2;

        albero_ternario *middle_node=(albero_ternario *)malloc(sizeof(albero_ternario));

        if(middle_node)
        {
            middle_node->inforadice=media;
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

void print_three(albero_ternario *radice)
{
    if(radice)
    {
        printf("%d|", radice->inforadice);
        print_three(radice->sx);
        print_three(radice->middle);
        print_three(radice->dx);
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

    new_albero(&abr);

    visita_ordine(abr);

    printf("\n");

    if(is_abr(abr))
    {
        printf("L'albero è un ABR");
    }
    else
    {
        printf("L'albero non è un ABR");
    }

    printf("\n");

    albero_ternario *TER=costruisci(abr);

    print_three(TER);

    printf("\n");

}