/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, elimini tutti gli elementi divisibili 
per 10
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

lista *new_elem(int info)
{
    lista *tmp;

    tmp=(lista *)malloc(sizeof(lista));
    
    if(tmp)
    {
        tmp->info=info;
        tmp->next=NULL;
    }

    return tmp;
}

int  empty_list(lista *head)
{
    return (head==NULL);
}

int lunghezzaLista(lista *head)
{
    if(empty_list(head))
    {
        return 0;
    }
    return 1+lunghezzaLista(head->next);
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

lista *elimina_mod10_ric(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=elimina_mod10_ric(head->next);

    if(head->info%10==0)
    {
        lista *tmp=head->next;
        free(head);
        return tmp;
    }
    else
    {
        return head;
    }
}

void elimina_mod10(lista **head_ref)
{
    *head_ref=elimina_mod10_ric(*head_ref);
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    printf("LISTA ORIGINALE: \n");
    stampa_lista(l);

    elimina_mod10(&l);

    printf("LISTA MODIFICATA: \n");
    stampa_lista(l);
}

