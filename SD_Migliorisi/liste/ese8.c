/*Scrivere una funzione ricorsiva che, data una lista di interi doppiamente puntata, realizzi
l’inserimento degli elementi in ordine crescente.
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

int empty_lista(lista *head)
{
    return (head==NULL);
}

int lunghezza_lista(lista *head)
{
    if(empty_lista(head))
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
        printf("ERRORE DI ALLOCAZIONE DI MEMORIA\n");
    }

    return tmp;
}

lista *insert_coda(lista *head, int info)
{
    if(empty_lista(head))
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

lista *insertOrdLista(lista *head, int info)
{
    lista *tmp;

    if(empty_lista(head))
    {
        return new_elem(info);
    }

    if(head->info>info)
    {
        tmp=new_elem(info);
        tmp->next=head;
        return tmp;
    }

    head->next=insertOrdLista(head->next,info);

    return head;
}

void stampa_lista(lista *head)
{
    if(empty_lista(head))
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

        //*head=insert_coda(*head,val);
        *head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    stampa_lista(l);
}
