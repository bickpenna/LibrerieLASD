/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, la modifichi in modo tale che ogni 
numero dispari sia seguito dal suo successore pari.
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
    if (empty_list(head))
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
        printf("ERRORE DI ALLOCAZIONE");
    }
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

void stampa_lista(lista *head)
{
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d->",head->info);
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
    }
}

lista *aggiungi_successore_pari(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    if(head->info%2!=0)
    {
        lista *nuovo_nodo=(lista *)malloc(sizeof(lista));
        nuovo_nodo->info=head->info+1;
        nuovo_nodo->next=head->next;
        head->next=nuovo_nodo;
        head=nuovo_nodo->next;
    }
    else
    {
        head=head->next;
    }
    
    head=aggiungi_successore_pari(head);

    return head;
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    printf("LISTA ORIGINALE: \n");
    stampa_lista(l);

    l=aggiungi_successore_pari(l);

    printf("LISTA MODIFICATA: \n");
    stampa_lista(l);
}