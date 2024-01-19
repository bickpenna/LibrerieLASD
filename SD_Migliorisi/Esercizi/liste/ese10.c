/*
Date due liste doppiamente concatenate,l1 ed l2, fare le seguenti cose:
a) eliminare da l1 i negativi ed inserirli in testa ad l2
b) eliminare da l2 i positivi ed inserirli in testa ad l1
c) restituire le due liste così modificate.
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
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));

    if(nuovo_nodo)
    {
        nuovo_nodo->prev=NULL;
        nuovo_nodo->info=info;
        nuovo_nodo->next=*head;
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

void rimuovi_negativi_e_inserisci_in_testa(lista **l1, lista **l2) 
{
    if(empty_list(*l1)) 
    {
        return;
    }

    lista *next = (*l1)->next;

    if ((*l1)->info < 0) 
    {
        insert_testa(l2, (*l1)->info); // Utilizzo della tua funzione di inserimento in testa
        *l1 = next;
        if (next != NULL) 
        {
            next->prev = NULL;
        }
    }
    else 
    {
        l1 = &((*l1)->next);
    }

    rimuovi_negativi_e_inserisci_in_testa(l1, l2);
}

/*
void rimuovi_positivi_e_inserisci_in_testa(struct Node** L1, struct Node** L2) {
    if (*L2 == NULL) {
        return;
    }

    struct Node* next = (*L2)->next;

    if ((*L2)->data >= 0) {
        inserisci_in_testa(L1, (*L2)->data); // Utilizzo della tua funzione di inserimento in testa
        *L2 = next;
        if (next != NULL) {
            next->prev = NULL;
        }
    } else {
        L2 = &((*L2)->next);
    }

    rimuovi_positivi_e_inserisci_in_testa(L1, L2);
}
*/


int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    new_list(&l1);
    new_list(&l2);

    printf("LISTA L1: \n");
    stampa_lista(l1);

    printf("\nLISTA L2: \n");
    stampa_lista(l2);

    rimuovi_negativi_e_inserisci_in_testa(&l1,&l2); 

    printf("\nL1 MODIFICATA: \n");
    stampa_lista(l1);

    printf("\nL2 MODIFICATA: \n");
    stampa_lista(l2);   
}

