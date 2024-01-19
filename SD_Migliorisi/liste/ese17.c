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
    if(empty_list)
    {
        return 0;
    }

    return 1+lunghezza_lista (head->next);
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

lista *inserisci_coda(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_elem(info);
    }
    else
    {
        head->next=inserisci_coda(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void inserisci_testa(lista **head, int info)
{
    lista *nuovo_nodo;
    nuovo_nodo=(lista *)malloc(sizeof(lista ));

    if(nuovo_nodo)
    {
        nuovo_nodo->info=info;
        nuovo_nodo->prev=NULL;
        nuovo_nodo->next=*head;

        if(*head==NULL)
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

        *head=inserisci_coda(*head,val);
        //*head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

lista *rimuovi_negativi_l1(lista *l1, lista **l2)
{
    if(empty_list(l1))
    {
        return NULL;
    }

    l1->next=rimuovi_negativi_l1(l1->next,l2);

    if(l1->info<0)
    {
        inserisci_testa(l2,l1->info);
        lista *tmp=l1->next;

        if(tmp!=NULL)
        {
            tmp->prev=l1->prev;
        }

        free(l1);
        return tmp;
    }

    return l1;
}

lista *rimuovi_positivi_l2(lista *l2, lista **l1)
{
    if(empty_list(l2))
    {
        return NULL;
    }

    l2->next=rimuovi_positivi_l2(l2->next,l1);

    if(l2->info>0)
    {
        inserisci_testa(l1,l2->info);
        lista *tmp=l2->next;

        if(tmp!=NULL)
        {
            tmp->prev=l2->prev;
        }

        free(l2);
        return tmp;
    }

    return l2;
}

int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    new_list(&l1);

    stampa_lista(l1);

    printf("\n");

    new_list(&l2);

    stampa_lista(l2);

    printf("\n");

    l1=rimuovi_negativi_l1(l1,&l2);
    l2=rimuovi_positivi_l2(l2,&l1);

    stampa_lista(l1);

    printf("\n");

    stampa_lista(l2);
}
