/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L e un intero el, verifichi se esiste una 
occorrenza di el nella lista
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

int ricerca_elemento(lista *head, int el)
{
    if(empty_list(head))
    {
        return 0;
    }

    if(head->info==el)
    {
        return 1;
    }

    return ricerca_elemento(head->next,el);
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    printf("LISTA ORIGINALE: \n");
    stampa_lista(l);

    int res;
    printf("\nInserisci l'elemento da ricercare :  ");
    scanf("%d",&res);

    if(ricerca_elemento(l,res))
    {
        printf("Elemento %d presente nella lista\n",res);
    }
    else
    {
        printf("Elemento %d non presente nella lista\n",res);
    }
}