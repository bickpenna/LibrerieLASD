/*
Si considerino due liste di numeri interi Lista1 e Lista2 implementate entrambe come lista
doppiamente puntata non circolare utilizzando la seguente struttura
struct elemento {
struct elemento *prev;
int inf;
struct elemento *next;}
struct elemento *Lista1,*Lista2;
b. Si implementi una funzione ricorsiva che elimini dalla lista Lista1 tutti i numeri
negativi e dalla lista Lista2 tutti quelli positivi senza usare strutture dati aggiuntive e
senza cambiare l’ordine degli elementi.
c. Si implementi una funzione ricorsiva interleaving che prendendo in input le due liste
modificate restituisce l’interleaving delle due liste, fino a che una delle due liste non
diventi nulla.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
    lista *nuovo_nodo;
    nuovo_nodo=(lista *)malloc(sizeof(lista));

    if(nuovo_nodo)
    {
        nuovo_nodo->prev=NULL;
        nuovo_nodo->info=info;
        nuovo_nodo->next=*head;
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    if(*head!=NULL)
    {
        (*head)->prev=nuovo_nodo;
    }

    *head=nuovo_nodo;
}

void stampa_lista(lista *head)
{
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d<->",head->info);
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

void remove_negative_fromL1(lista **l1)
{
    if(empty_list(*l1))
    {
        return;
    }

    lista *next=(*l1)->next;

    if((*l1)->info < 0)
    {
        *l1=next;
        if(next!=NULL)
        {
            next->prev=NULL;
        }
    }
    else
    {
        l1=&((*l1)->next);
    }

    remove_negative_fromL1(l1);
}

void remove_positive_fromL2(lista **l2)
{
    if(empty_list(*l2))
    {
        return;
    }

    lista *next=(*l2)->next;

    if((*l2)->info > 0)
    {
        *l2=next;

        if(next!=NULL)
        {
            next->prev=NULL;
        }

    }
    else
    {
        l2=&((*l2))->next;
    }
    remove_positive_fromL2(l2);
}

lista *interleaving(lista *l1, lista *l2)
{
    if(empty_list(l1))
    {
        return l2;
    }

    if(empty_list(l2))
    {
        return l2;
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
    lista *res_interleaving=NULL;

    new_list(&l1);
    new_list(&l2);

    printf("LISTA L1: \n");
    stampa_lista(l1);

    printf("LISTA L2: \n");
    stampa_lista(l2);

    remove_negative_fromL1(&l1);

    printf("L1 MODIFICATA: \n");
    stampa_lista(l1);

    remove_positive_fromL2(&l2);

    printf("L2 MODIFICATA: \n");
    stampa_lista(l2);

    res_interleaving=interleaving(l1,l2);

    printf("LISTA RISULTANTE : \n");
    stampa_lista(res_interleaving);
}