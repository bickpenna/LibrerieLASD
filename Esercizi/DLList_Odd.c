#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
struct Nodo{
    int dato;
    link prec;
    link next;
};

link getLast(link head){
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

link newNodo(int dato){
    link new = (link) malloc(sizeof(struct Nodo));
    if(!new) exit(EXIT_FAILURE);

    new->dato = dato;
    new->prec = NULL;
    new->next = NULL;
    return new;
}

void insTesta(link *head, int dato){
    link new = newNodo(dato);
    new->next = *head;
    if (*head != NULL){
        new->prec = (*head)->prec;
        (*head)->prec = new;
    }

    *head = new;
}

void insCoda(link *head, int dato){
    if(*head == NULL){
        insTesta(head, dato);
        return;
    }
    link last = getLast(*head);
    link new = newNodo(dato);

    new->prec = last;
    last->next = new;
}

void stampaLista(link head){
    if(head == NULL){
        printf("NULL \n");
        return;
    }
    printf("%d -> ", head->dato);
    stampaLista(head->next);
}

void insOdd(link *headO, link headI){
    if(headI == NULL) return;
    if (headI->dato % 2 == 0) insCoda(headO, headI->dato);
    insOdd(headO, headI->next);
}

void insOddF2DL(link *headO, link head1, link head2){
    insOdd(headO, head1);
    insOdd(headO, head2);
}

int main(){
    link head1 = NULL;
    link head2 = NULL;
    link headO = NULL;
    int dim1 = 10;
    int dim2 = 14;
    int dimO = dim1 + dim2;
    
    for(int i=0; i<dim1; i++) insCoda(&head1, i);
    for(int i=0; i<dim2; i++) insCoda(&head2, i+10);

    printf("\nLista 1: ");
    stampaLista(head1);
    printf("\nLista 2: ");
    stampaLista(head2);

    insOddF2DL(&headO, head1, head2);
    printf("\nLista pari: ");
    stampaLista(headO);



}