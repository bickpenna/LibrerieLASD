/*
Presi due ABR, si costruisca un albero binario che sommi i valori posti nelle stesse 
posizioni (se esistenti). Inoltre trasformare l'albero ottenuto in quadernario in modo che il 
terzo nodo, aggiunto senza figli, abbia il valore somma dei fratelli esistenti nell'albero 
binario e il quarto, sempre senza figli, la differenza.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct el_bin
{
    struct el_bin *sx;
    int inforadice;
    struct el_bin *dx;
};
typedef struct el_bin albero;

struct el_qua
{
    struct el_qua *sx;
    struct el_qua *middle_sx;
    struct el_qua *middle_dx;
    struct el_qua *dx;
    int inforadice;
};
typedef struct el_qua albero_quad;

int is_empty(albero *radice)
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
        printf("Erroe di allocazione\n");
    }

    return tmp;
}

albero *inserisci(albero *radice, int el)
{
    albero *aux;

    if(is_empty(radice))
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

albero *somma_abr(albero *abr1, albero *abr2)
{
    if(is_empty(abr1) || is_empty(abr2))
    {
        return NULL;
    }

    albero *nodo_somma;

    nodo_somma=new_elem(NULL,abr1->inforadice+abr2->inforadice,NULL);
    nodo_somma->sx=somma_abr(abr1->sx,abr2->sx);
    nodo_somma->dx=somma_abr(abr1->dx,abr2->sx);

    return nodo_somma;
}

int somma_fratelli(albero_quad *radice_quad)
{
    if(radice_quad==NULL)
    {
        return 0;
    }

    int somma=0;

    if(radice_quad->sx)
    {
        somma+=radice_quad->sx->inforadice;
    }
    
    if(radice_quad->middle_sx)
    {
        somma+=radice_quad->middle_sx->inforadice;
    }

    if(radice_quad->middle_dx)
    {
        somma+=radice_quad->middle_dx->inforadice;
    }

    if(radice_quad->dx)
    {
        somma+=radice_quad->dx->inforadice;
    }

    return somma;
}

int differenza_sx_dx(albero_quad *nodo)
{
    if (nodo == NULL)
        return 0;

    int somma_sx = 0;
    int somma_dx = 0;

    if (nodo->sx)
        somma_sx = nodo->sx->inforadice;
    if (nodo->dx)
        somma_dx = nodo->dx->inforadice;

    return somma_sx - somma_dx;
}

// Funzione ricorsiva per trasformare l'albero quaternario
void trasforma_albero(albero_quad *nodo)
{
    if (nodo == NULL)
        return;

    if (nodo->middle_sx == NULL)
    {
        // Aggiungi un terzo nodo con la somma dei fratelli
        albero_quad *terzo_nodo = malloc(sizeof(albero_quad));
        terzo_nodo->sx = terzo_nodo->middle_sx = terzo_nodo->middle_dx = terzo_nodo->dx = NULL;
        terzo_nodo->inforadice = somma_fratelli(nodo);

        nodo->middle_sx = terzo_nodo;
    }

    if (nodo->middle_dx == NULL)
    {
        // Aggiungi un quarto nodo con la differenza tra sx e dx
        albero_quad *quarto_nodo = malloc(sizeof(albero_quad));
        quarto_nodo->sx = quarto_nodo->middle_sx = quarto_nodo->middle_dx = quarto_nodo->dx = NULL;
        quarto_nodo->inforadice = differenza_sx_dx(nodo);

        nodo->middle_dx = quarto_nodo;
    }

    // Chiamata ricorsiva per i nodi figli
    trasforma_albero(nodo->sx);
    trasforma_albero(nodo->middle_sx);
    trasforma_albero(nodo->middle_dx);
    trasforma_albero(nodo->dx);
}

// Funzione per stampare l'albero quaternario
void stampa_albero(albero_quad *nodo)
{
    if (nodo == NULL)
        return;

    printf("%d ", nodo->inforadice);
    stampa_albero(nodo->sx);
    stampa_albero(nodo->middle_sx);
    stampa_albero(nodo->middle_dx);
    stampa_albero(nodo->dx);
}


int main()
{
    albero *abr1=NULL;
    albero *abr2=NULL;

    printf("CREO, INIZIALIZZO E STAMPO I DUE ALBERI: \n");

    new_albero(&abr1);

    visita_ordine(abr1);

    printf("\n");

    new_albero(&abr2);

    visita_ordine(abr2);

    printf("\n");

    albero *somma_alberi=somma_abr(abr1,abr2);

    printf("ALBERO SOMMA: \n");

    visita_ordine(somma_alberi);

    printf("\n");

}