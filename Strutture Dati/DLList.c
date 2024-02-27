#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
struct Nodo{
    int dato;
    link prec;
    link next;
};

// Liste Doppiamente Concatenate
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

void delTesta(link *head){
    link tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void stampaLista(link head){
    if(head == NULL){
        printf("NULL \n");
        return;
    }
    printf("%d -> ", head->dato);
    stampaLista(head->next);
}

// 1) Esercizio Lista con Elementi dispari da due liste 
void insOdd(link *headO, link headI){
    if (headI == NULL) return;
    if (headI->dato % 2 == 0) insCoda(headO, headI->dato);
    insOdd(headO, headI->next);
}

void insOddF2DL(link *headO, link head1, link head2){
    insOdd(headO, head1);
    insOdd(headO, head2);
}

// 2.1) Togli Pari o Dispari
void delOdd(link *head){
    if(head == NULL || *head == NULL) return;
    
    if((*head)->dato % 2 != 0) {
        delTesta(head);
        delOdd(head);
    } else if ((*head)->next != NULL) {
        delOdd(&(*head)->next);
    }
}

void delHeaven(link *head){
    if(head == NULL || *head == NULL) return;
    
    if((*head)->dato % 2 == 0) {
        delTesta(head);
        delHeaven(head);
    } else if ((*head)->next != NULL) {
        delHeaven(&(*head)->next);
    }
}

void delOddOrHeaven(link *head, int dato){
    if (dato == 1) delOdd(head);
    if (dato == 0) delHeaven(head);
}

// 2.2) Interleaving
link interleaving(link *head1, link *head2){
    if (*head1 == NULL) return *head2;
    if (*head2 == NULL) return *head1;

    link next1 = (*head1)->next;
    link next2 = (*head2)->next;
    (*head1)->next = *head2;
    (*head2)->prec = *head1;

    if (next1 != NULL) next1->prec = *head2;
    (*head2)->next = interleaving(&next1, &next2);

    return *head1;
}

// 3) Togli Negativi
void delNegative(link *head){
    if(head == NULL || *head == NULL) return;

    if((*head)->dato < 0){
        delTesta(head);
        delNegative(head);
    } else if ((*head)->next != NULL){
        delNegative(&(*head)->next);
    }
}

int main(){
    // Lista 1
    link head1 = NULL;
    int dim1 = 10;
    
    for(int i=-7; i<dim1; i++) insCoda(&head1, i);
    printf("\nLista 1: ");
    stampaLista(head1);

    // Lista 2
    link head2 = NULL;
    int dim2 = 14;

    for(int i=-5; i<dim2; i++) insCoda(&head2, i+10);
    printf("\nLista 2: ");
    stampaLista(head2);

    // 1) Lista Dispari
    link headOdd = NULL;
    int dimOdd = dim1 + dim2;

    insOddF2DL(&headOdd, head1, head2);
    printf("\nLista pari: ");
    stampaLista(headOdd);

    // 2.1) Togli Pari o Dispari
    delOddOrHeaven(&head1, 1);
    printf("\nLista Dispari eliminati: ");
    stampaLista(head1);

    delOddOrHeaven(&head2, 0);
    printf("\nLista Pari eliminati: ");
    stampaLista(head2);

    // 2.2) Interleaving (modicfico le liste)
    link headInterleaving = interleaving(&head1, &head2);
    printf("\nLista interleaving: ");
    stampaLista(headInterleaving);

    // 3) Togli Negativi
    delNegative(&head2);
    printf("\nLista Negativi eliminati: ");
    stampaLista(head2);

    
}