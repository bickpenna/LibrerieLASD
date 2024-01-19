/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, raddoppi tutti gli elementi dispari 
della lista
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

lista *new_elem(int info)
{
    lista *tmp;

    tmp=(lista *)malloc(sizeof(lista));

    if(tmp!=NULL)
    {
        tmp->info=info;
        tmp->next=NULL;
    }

    return tmp;
}

lista *insert_coda(lista *head,int info)
{
    if(head==NULL)
    {
        head=new_elem(info);
    }
    else
    {
        head->next=insert_coda(head->next,info);
    }
    return  head;
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
    }
}

void raddoppia_dispari(lista *head)
{
    if(empty_list(head))
    {
        return;
    }
    
    if(head->info%2!=0)
    {
        head->info=head->info*2;
    }

    raddoppia_dispari(head->next);
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    stampa_lista(l);

    raddoppia_dispari(l);

    stampa_lista(l);
}
