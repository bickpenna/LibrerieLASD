#include <stdio.h>
#include <stdlib.h>


typedef struct Nodo *link;
struct Nodo{
    int dato;
    link next;
};

void push(link *stack){
    link new = newNodo();
    new->next = *stack;
    *stack = new;
}



void menuStack(link *stack) {
    int val;
    printf("\n-- Menù Operazioni Stack --\n");

    printf("\nOperazioni di Inserimento:\n");
    printf("1. Push (Aggiungi un elemento in cima allo stack)\n");

    printf("\nOperazioni di Rimozione:\n");
    printf("2. Pop (Rimuovi l'elemento in cima allo stack)\n");

    printf("\nOperazioni di Visualizzazione:\n");
    printf("3. Top (Visualizza l'elemento in cima allo stack)\n");
    printf("4. Controllo Stack Vuoto\n");
    printf("5. Mostra tutti gli elementi dello stack\n");

    printf("\nUscire:\n");
    printf("0. Esci\n");
    printf("-----------------------------\n");
    printf("Scelta: ");
    scanf("%d", &val);

    sceltaMenu(val, stack);
}

int main(){
    link stack = NULL;
    while(1) menu(&head);
}
