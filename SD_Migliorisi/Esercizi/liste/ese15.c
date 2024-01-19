/*
Si considerino due liste di interi LISTA1 e LISTA2 implementate come liste doppiamente puntate
non circolari.Dopo aver realizzato dal main una procedura per la inizializzazione manuale delle 
due liste e la stampa, si inserisca nel main una funzione che tramite l'uso della sola ricorsione
presi in input LISTA1 e LISTA2 faccia le seguenti cose:
a)rimuova da lista1 i multipli di 2 e li inserisca in testa a lista2
b)rimuova da lista2 i multipli di 5 e li inserisca in testa a lista1
c)stampi le liste cosi modificate
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

lista *rimuovi_multipli2_l1(lista *l1,lista **l2)
{
    if(empty_list(l1))
    {
        return NULL;
    }

    l1->next=rimuovi_multipli2_l1(l1->next,l2);

    if(l1->info%2==0)
    {
        insert_testa(l2,l1->info);
        lista *tmp=l1->next;

        if(tmp!=NULL)
        {
            tmp->prev=l1->prev;
        }

        free(l1);
        return tmp;
    }
    return l1 ;
}

lista *rimuovi_multipli5_l2(lista *l2,lista **l1)
{
    if(empty_list(l2))
    {
        return NULL;
    }

    l2->next=rimuovi_multipli5_l2(l2->next,l1);

    if(l2->info%5==0)
    {
        insert_testa(l1,l2->info);
        lista *tmp=l2->next;

        if(tmp!=NULL)
        {
            tmp->prev=l2->prev;
        }

        free(l2);
        return tmp;
    }
    return l2 ;
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

    l1=rimuovi_multipli2_l1(l1,&l2);
    l2=rimuovi_multipli5_l2(l2,&l1);
    
    printf("L1 MODIFICATA: \n");
    stampa_lista(l1);

    printf("L2 MODIFICATA: \n");
    stampa_lista(l2);    
}