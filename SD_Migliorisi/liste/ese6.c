/*
funzioni per liste double linked 
creazione, inserimento e stampa
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

lista *crea_lista(int n)
{
    if(n<=0)
    {
        return NULL;
    }

    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));

    if(nuovo_nodo)
    {
        nuovo_nodo->info=n;
        nuovo_nodo->prev=NULL;
        nuovo_nodo->next=crea_lista(n-1);
    }

    if(nuovo_nodo->next!=NULL)
    {
        nuovo_nodo->next->prev=nuovo_nodo;
    }

    return nuovo_nodo;
}

lista *new_nodo(int info)
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
        printf("ERRORE DI ALLOCAZIONE");
    }

    return tmp;
}

lista *insert(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_nodo(info);
    }
    else
    { 
        head->next=insert(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void insert_testa(lista **head, int info)
{
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));
    nuovo_nodo->info=info;
    nuovo_nodo->prev=NULL;
    nuovo_nodo->next=*head;

    if(*head!=NULL)
    {
        (*head)->prev=nuovo_nodo;
    }

    *head=nuovo_nodo;
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

        //*head=insert(*head,val);
        insert_testa(head,val);
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

int main()
{
    lista *l=NULL;

    new_list(&l);

    printf("LISTA CREATA: \n");
    stampa_lista(l);
}