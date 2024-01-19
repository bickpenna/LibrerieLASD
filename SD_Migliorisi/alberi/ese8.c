/*
Siano t1 e t2 due alberi binari. Creare un albero ternario T ottenuto estendendo T1 nel seguente modo:
per ogni nodo X comune ai due alberi e tale per cui il valore numerico è lo stesso nei due alberi,
si aggiunge 1 come figlio mezzo in T
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

struct el_tree
{
    struct el_tree *sx;
    int inforadice;
    struct el_tree *middle;
    struct el_tree *dx;
};
typedef struct el_tree albero_ternario;

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

albero_ternario *costruisci_albero_ternario(albero_ternario *t, albero *t1, albero *t2)
{
    if(vuoto(t1) || vuoto(t2))
    {
        return NULL;
    }

    albero_ternario *new_node=(albero_ternario *)malloc(sizeof(albero_ternario));
    
    if(new_node)
    {
        new_node->inforadice=t1->inforadice;
        new_node->sx=costruisci_albero_ternario(new_node->sx,t1->sx,t2->sx);
        new_node->middle=NULL;
        new_node->dx=costruisci_albero_ternario(new_node->dx,t1->dx,t2->dx);

        if(t1->inforadice==t2->inforadice)
        {
            new_node->middle=(albero_ternario *)malloc(sizeof(albero_ternario));
            new_node->middle->inforadice=1;
            new_node->middle->sx=NULL;
            new_node->middle->middle=NULL;
            new_node->middle->dx=NULL;
        }
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return new_node;
}

/*
albero_ternario *costruisci_albero_ternario(albero_ternario *t, albero *t1, albero *t2)
{
    if (vuoto(t1) || vuoto(t2))
    {
        return NULL;
    }

    albero_ternario *new_node = (albero_ternario *)malloc(sizeof(albero_ternario));

    if (new_node)
    {
        new_node->inforadice = t1->inforadice;
        new_node->middle = NULL;

        // Verifica se i valori sono uguali e crea il figlio mezzo se necessario
        if (t1->inforadice == t2->inforadice)
        {
            new_node->middle = (albero_ternario *)malloc(sizeof(albero_ternario));
            if (new_node->middle)
            {
                new_node->middle->inforadice = 1;
                new_node->middle->sx = NULL;
                new_node->middle->middle = NULL;
                new_node->middle->dx = NULL;
            }
            else
            {
                printf("Errore di allocazione per il nodo middle\n");
            }
        }

        // Costruzione dei sottoalberi
        new_node->sx = costruisci_albero_ternario(new_node->sx, t1->sx, t2->sx);
        new_node->dx = costruisci_albero_ternario(new_node->dx, t1->dx, t2->dx);
    }
    else
    {
        printf("Errore di allocazione per il nuovo nodo\n");
    }

    return new_node;
}
*/

int main()
{
    albero *t1=NULL;
    albero *t2=NULL;

    printf("GENERO ALBERO T1\n");
    new_albero(&t1);

    printf("GENERO ALBERO T2\n");
    new_albero(&t2);

    printf("STAMPO ALBERO T1: \n");
    visita_ordine(t1);

    printf("\n");

    printf("STAMPO ALBERO T2: \n");
    visita_ordine(t2);

    printf("GENERO ALBERO TERNARIO: \n");
    albero_ternario *T = costruisci_albero_ternario(NULL,t1,t2);

    printf("STAMPO ALBERO TERNARIO T: \n");
    print_three(T);
}