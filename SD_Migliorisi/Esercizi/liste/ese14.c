/*
Si implementi la funzione void togli_numero che prende in input soltanto le due liste
(Lista1 e Lista2), calcola il numero degli elementi in Lista1 (diciamo m) e se tale numero
(m) è presente in Lista2 lo rimuove da questa lista (in tutte le sue occorrenze). Poi, ripete
l’operazione invertendo le due liste e così via. L'algoritmo termina non appena il numero m
calcolato non è presente nella lista in cui deve essere rimosso o una delle due liste diventa
vuota.
Si discuta la complessità della funzione implementata.
Esempio, sia Lista1 uguale a 31488 e Lista2 uguale 8548. Dopo la prima
iterazione Lista2 è uguale a 848 (rimosso 5) e alla seconda iterazione Lista1 è uguale
1488 (rimosso 3). Alla prossima iterazione, Lista2 è 88 (rimosso 4). A questo
punto l'algoritmo termina perchè gli elementi in Lista2 sono 2 e tale numero non è
presente in Lista1.
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

lista *rimuovi_elemento(lista *head, int num)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=rimuovi_elemento(head->next,num);

    if(head->info==num)
    {
        lista *tmp=head->next;
        if(tmp!=NULL)
        {
            tmp->prev=head->prev;
        }
        free(head);
        return tmp;
    }

    return head;
}

void togli_numero_ric(lista **l1, lista **l2)
{
    int size=lunghezza_lista(*l1);

    if(size==0 || lunghezza_lista(*l2)==0)
    {
        return;
    }

    *l2=rimuovi_elemento(*l2,size);

    /*lista *tmp=*l1;
    *l1=*l2;
    *l2=tmp;*/

    togli_numero_ric(l1,l2);
}

void togli_numero(lista **l1, lista **l2)
{
    togli_numero_ric(l1,l2);
}


int main()
{
    lista *l1=NULL;
    lista *l2=NULL;

    new_list(&l1);
    new_list(&l2);

    printf("LISTA L1\n");
    stampa_lista(l1);

    printf("LISTA L2\n");
    stampa_lista(l2);

    togli_numero(&l1,&l2);

    printf("L1 MODIFICATA : \n");
    stampa_lista(l1);

    printf("L2 MODIFICATA: \n");
    stampa_lista(l2);

}