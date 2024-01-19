/*
RICERCA DI ELEMENTO IN ABR
RICERCA DEL MINIMO IN UN ABR
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

struct el
{
    int inforadice;
    struct el *sx;
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
        tmp->inforadice=inforadice;
        tmp->sx=sx;
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
            aux->inforadice=el;
            aux->sx=NULL;
            aux->dx=NULL;
            radice=aux;
        }
        else
        {
            printf("Errore di allocazione");
        }
    }
    else if(el<radice->inforadice)
    {
        radice->sx=inserisci(radice->sx, el);
    }
    else if(el>radice->inforadice)
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
    else if(radice->inforadice>r)
    {
        trovato=ricerca(radice->sx,r);
    }
    else if(radice->inforadice<r)
    {
        trovato=ricerca(radice->dx,r);
    }

    return trovato;
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

void elimina(albero **radice, int el)
{
    albero *aux;
    aux=*radice;

    if(vuoto(*radice))
    {
        return;
    }

    if((*radice)->inforadice > el)
    {
        elimina(&((*radice)->sx),el);
    }
    else if((*radice)->inforadice < el)
    {
        elimina(&((*radice)->dx),el);
    }
    else
    {
        if(!((*radice)->sx) && (!((*radice)->dx)))
        {
            free(*radice);
            *radice=NULL;
        }
        else if(((*radice)->sx)&& (!((*radice)->dx)))
        {
            *radice=aux->sx;
        }
        else if(!((*radice)->sx) && ((*radice)->dx))
        {
            *radice=aux->dx;
        }
        else if((aux->dx == NULL) || (aux->sx == NULL))
        {
            free(aux);
            return;
        }
        else if(((*radice)->sx) && ((*radice)->dx))
        {
            (*radice)->inforadice=ricerca_minimo((*radice)->dx);
            elimina(&(*radice)->dx, (*radice)->inforadice);
        }
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

    int valore_da_ricercare;

    printf("Inserisci valore da cercare nell'albero:  ");
    scanf("%d", &valore_da_ricercare);

    if(ricerca(abr, valore_da_ricercare))
    {
        printf("Elemento %d trovato \n", valore_da_ricercare);
    }
    else
    {
        printf("Elemento non trovato\n");
    }

    int valore_minimo=ricerca_minimo(abr);

    printf("Il valore minimo dell'albero è %d\n", valore_minimo);

    int elemento_da_elim = 0;

    printf("\nInserisci l'elemento da eliminare: ");
    scanf("%d", &elemento_da_elim);

    elimina(&abr, elemento_da_elim);

    printf("ALBERO POST OPERAZIONE : \n");
    visita_ordine(abr);
}
