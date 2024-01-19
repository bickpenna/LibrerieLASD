/*
Date due liste doppiamente puntate e non circolari di interi positivi L1 e L1
caricate da tastiera, scrivere una funzione in che che presi in input L1 e L2
rimuova da L1 tutte le occorrenze dei dispari e li inserisca in testa a L2
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
        printf("Errore di allocazione");
    }

    return tmp;
}

lista *insert_coda(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_nodo(info);
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
        //insert_testa(head,val);
    }
}


void remove_and_insert_ric(lista **l1, lista **l2, lista *current, lista *prev)
{
    if(current==NULL)
    {
        return;
    }

    if(current->info%2!=0)
    {
        lista *next=current->next;

        if(prev!=NULL)
        {
            prev->next=next;
        }
        else
        {
            *l1=next;
        }

        if(next!=NULL)
        {
            next->prev=prev;
        }

        insert_testa(l2,current->info);
        free(current);

        remove_and_insert_ric(l1,l2,next,prev);
    }
    else
    {
        remove_and_insert_ric(l1,l2,current->next,current);
    }
}

void remove_and_insert(lista **l1, lista **l2)
{
    remove_and_insert_ric(l1,l2,*l1,NULL);
}

int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    new_list(&l1);
    new_list(&l2);

    printf("LISTA L1: \n");
    stampa_lista(l1);

    printf("LISTA L2: \n");
    stampa_lista(l2);

    remove_and_insert(&l1,&l2);

    printf("L1 MODIFICATA: \n");
    stampa_lista(l1);

    printf("L2 MODIFICATA: \n");
    stampa_lista(l2);
    
}
