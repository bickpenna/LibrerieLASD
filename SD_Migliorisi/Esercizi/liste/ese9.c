/*
Date due liste implementa la funzione di togli negativi che elimina da L1
tutti i negativi e i poisitivi da L2 senza cambiare ordine. Implementare la
funzione interleaving che date due liste restituisce il loro interleaving tale
che mette un elemento di L1 ogni due di L2 fino a che una delle due non si
annulla
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct el
{
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
        head=new_elem(info);
    }
    else
    {
        head->next=insert_coda(head->next,info);
    }

    return head;
}

lista *insert_testa(lista *head, int info)
{
    lista *nuovo_nodo=new_elem(info);

    if(nuovo_nodo)
    {
        nuovo_nodo->info=info;
        nuovo_nodo->next=head;
    }

    return nuovo_nodo;
}

lista *insertOrdLista(lista *head, int info)
{
    lista *tmp;

    if(empty_list(head))
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
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d->", head->info);
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

lista *togli_negativi(lista *head) 
{
    if (empty_list(head)) 
    {
        return NULL;
    }

    head->next=togli_negativi(head->next);

    if (head->info < 0) 
    {
        lista *tmp = head;
        head = head->next;
        free(tmp);
    }

    return head;
}

lista *togli_positivi(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=togli_positivi(head->next);

    if(head->info>0)
    {
        lista *tmp=head;
        head=head->next;
        free(tmp);
    }

    return head;
}

int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    new_list(&l1);

    printf("LISTA ORIGINALE \n");
    stampa_lista(l1);

    l1=togli_negativi(l1);

    printf("LISTA L1 MODIFICATA: \n");
    stampa_lista(l1);

    new_list(&l2);

    printf("LISTA ORIGINALE \n");
    stampa_lista(l2);

    l2=togli_positivi(l2);

    printf("LISTA L2 MODIFICATA\n");
    stampa_lista(l2);
    
}