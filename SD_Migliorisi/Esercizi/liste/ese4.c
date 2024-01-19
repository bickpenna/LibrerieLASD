/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L e un intero el, rimuova una 
ricorrenza di el dalla lista (se ne esiste una)
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
    else
    {
        printf("ERRORE DI ALLOCAZIONE\n");
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

lista *rimuovi_elemento(lista *head, int el)
{
    if(empty_list(head))
    {
        return head;
    }

    if(head->info==el)
    {
        lista *tmp=head->next;
        free(head);
        return tmp;
    }

    head->next=rimuovi_elemento(head->next,el);

    return head;
}

int main()
{
    lista *l=NULL;

    new_list(&l);

    printf("LISTA ORIGINALE: \n");
    stampa_lista(l);

    int del_elem;
    printf("INSERISCI L'ELEMENTO CHE VUOI ELEMINARE: ");
    scanf("%d", &del_elem);

    l=rimuovi_elemento(l,del_elem);

    printf("LISTA MODIFICATA: \n");
    stampa_lista(l);

    return 0;
}