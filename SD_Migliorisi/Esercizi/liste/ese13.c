/*
Si considerino due liste di interi Lista1 e Lista2 implementate come liste doppiamente puntate non
circolari. Dopo aver realizzato dal main una procedura per la inizializzazione manuale delle due liste e la
stampa, si inserisca nel main una funzione (da implementare ed eseguire) che tramite l'uso della sola
ricorsione, presi in input Lista1 e Lista2, faccia le seguenti cose.
a) Rimuove tutte le ripetizioni da Lista1 e Lista2. Inoltre rimuovere da Lista2 quelli presenti in Lista1
b) Stampare le liste così modificate
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

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
        printf("Errore di allocazione \n");
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
        printf("Errore di allocazione \n");
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
        printf("FINE LISTA \n");
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
        //*head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

bool is_here(lista *head, int valore)
{
    lista *tmp=head;

    while(tmp!=NULL)
    {
        if(tmp->info==valore)
        {
            return true;
        }
        tmp=tmp->next;
    }

    return false;
}

void remove_duplicates(lista **l1)
{
    if (*l1 == NULL || (*l1)->next == NULL)
    {
        return; // La lista è vuota o ha solo un elemento, non ci sono duplicati da rimuovere
    }

    lista *current = *l1;

    while (current != NULL)
    {
        lista *next_unique = current->next;

        while (next_unique != NULL && next_unique->info == current->info)
        {
            lista *duplicate = next_unique;
            next_unique = next_unique->next;

            if (duplicate->prev != NULL) 
            {
                duplicate->prev->next = next_unique;
            }
            if (next_unique != NULL) 
            {
                next_unique->prev = duplicate->prev;
            }

            free(duplicate);
        }
        current = next_unique;
    }

    remove_duplicates(&((*l1)->next)); // Chiamata ricorsiva per il resto della lista
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

    remove_duplicates(&l1);

    printf("L1 MODIFICATA: \n");
    stampa_lista(l1);
}