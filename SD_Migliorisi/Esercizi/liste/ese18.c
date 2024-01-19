/*
Si considerino due liste di numeri interi Lista1 e Lista2 implementate come liste doppiamente 
puntate e non circolari, utilizzando la seguente struttura 
struct elemento {
struct elemento *prev;
int inf;
struct elemento *next;} 
struct elemento *Lista1,*Lista2;
Si implementi una funzione ricorsiva che presi in input entrambe le liste Lista1 e Lista2 e
nessun altro parametro, esegua le seguenti operazioni (in ordine): (1) rimuova da Lista1 e
Lista2 i negativi. (2) Se il numero degli elementi delle due liste è identico, crei una terza
lista Lista3 come interleaving tra le due liste (con inserimento a pettine).
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

struct el
{
    struct el *prev;
    int info;
    struct el *next;
};
typedef struct el lista;

int empty_list(lista *head)
{
    return (head==NULL);
}

int lunghezza_lista(lista *head)
{
    if(empty_list(head))
    {
        return 0;
    }

    return 1+lunghezza_lista(head->next);
}

lista *new_elem(int info)
{
    lista *tmp;
    tmp=(lista *)malloc(sizeof(lista));

    if(tmp)
    {
        tmp->prev=NULL;
        tmp->info=info;
        tmp->next=NULL;
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return tmp;
}

lista *insert_coda(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_elem(info);
    }
    else
    {
        head->next=insert_coda(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void insert_testa(lista **head, int info)
{
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista ));

    if(nuovo_nodo)
    {
        nuovo_nodo->info=info;
        nuovo_nodo->prev=NULL;
        nuovo_nodo->next=*head;

        if(*head!=NULL)
        {
            (*head)->prev=nuovo_nodo;
        }

        *head=nuovo_nodo;
    }
    else
    {
        printf("Errore di allocazione\n");
    }
}

void stampa_lista(lista *head)
{
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d<->", head->info);
        stampa_lista(head->next);
    }
}

void new_list(lista **head)
{
    int elementi;
    int val;

    printf("Quanti elementi si vogliono inserire? ");
    scanf("%d", &elementi);

    for(int i=0; i<elementi; i++)
    {
        printf("\nInserire elemento numero %d: ",i+1);
        scanf("%d", &val);

        *head=insert_coda(*head,val);
        //*head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

lista *rimuovi_negativi(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    lista *tmp=head->next;

    if(head->info<0)
    {
        if(head->prev!=NULL)
        {
            head->prev->prev=head->next;
        }

        if(head->next!=NULL)
        {
            head->next->prev=head->prev;
        }

        free(head);
        return rimuovi_negativi(tmp);
    }
    else
    {
        head->next=rimuovi_negativi(tmp);

        if(head->next!=NULL)
        {
            head->next->prev=head;
        }

        return head;
    }
}

lista *interleaving(lista *l1,lista *l2)
{
    if(empty_list(l1) || empty_list(l2))
    {
        printf("NON E' POSSIBILE INTERLEAVVING.")
        return NULL;
    }

    int size_l1=lunghezza_lista(l1);
    int size_l2=lunghezza_lista(l2);

    if(size_l1 != size_l2)
    {
        printf("NON E' POSSIBILE INTERLEAVVING.");
        return NULL;
    }

    lista *l1_next=l1->next;
    lista *l2_next=l2->next;

    l1->next=l2;
    l2->prev=l1;

    l2->next=interleaving(l1_next,l2_next);

    if(l2->next!=NULL)
    {
        l2->next->prev=l2;
    }

    return l1;
}

int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    printf("CREO E STAMPO L1: \n");

    new_list(&l1);

    stampa_lista(l1);

    printf("\n");

    printf("CREO E STAMPO L2: \n");

    new_list(&l2);

    stampa_lista(l2);

    printf("\n");

    printf("RIMUOVO NEGATIVI DA L1 E L2 E STAMPO LE LISTE MODIFICATE: \n");

    l1=rimuovi_negativi(l1);
    l2=rimuovi_negativi(l2);

    stampa_lista(l1);

    printf("\n");

    stampa_lista(l2);

    printf("\n");

    lista *l3=interleaving(l1,l2);

    stampa_lista(l3);

}