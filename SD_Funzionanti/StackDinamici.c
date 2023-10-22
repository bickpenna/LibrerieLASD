#include <stdio.h>
#include <stdlib.h>


typedef struct Nodo *link;
struct Nodo{
    int dato;
    link next;
};

//Funzioni
link allocaNodo();
void push(link *stack, int value);
void pushTastiera(link *stack);
int pop(link *stack);
int top(link *stack);
void displayStack(link *stack);
void sceltaMenu(int choice, link *stack);
void menuStack(link *stack);


link allocaNodo(){
    link new = (link) malloc(sizeof(struct Nodo));
    if(!new) exit(EXIT_FAILURE);

    new->next = NULL;
    return new;
}

void push(link *stack, int value){
    link new = allocaNodo();
    new->dato = value;
    new->next = *stack;
    *stack = new;
}

void pushTastiera(link *stack){
    int dato;
    printf("\nInserisci elemento da inserire: ");
    scanf("%d", &dato);
    push(stack, dato);
}

int pop(link *stack){
    link tmp;
    int dato;

    if(*stack == NULL) return -1;
    else {
        dato = (*stack)->dato;
        tmp = *stack;
        *stack = (*stack)->next;
        free(tmp);
        return dato;
    }
}

int top(link *stack){
    if(*stack == NULL) return -1;
    return (*stack)->dato;
}

void displayStack(link *stack){
    int dato;
    if(*stack == NULL) return;
    dato = pop(stack);
    printf("%d\n", dato);
    displayStack(stack);
    push(stack, dato);
}

void sceltaMenu(int choice, link *stack) {
    int value;
    switch(choice) {
        case 1:
            pushTastiera(stack);
            break;
        case 2:
            value = pop(stack);
            if(value != -1)
                printf("Elemento %d rimosso dallo stack.\n", value);
            else
                printf("Lo stack è già vuoto.\n");
            break;
        case 3:
            value = top(stack);
            if(value != -1)
                printf("Elemento in cima allo stack: %d\n", value);
            else
                printf("Lo stack è vuoto.\n");
            break;
        case 4:
            if(*stack == NULL)
                printf("Lo stack è vuoto.\n");
            else
                printf("Lo stack non è vuoto.\n");
            break;
        case 5:
            printf("Elementi nello stack:\n");
            displayStack(stack);
            break;
        case 0:
            exit(0); // Esce dal programma
            break;
        default:
            printf("Scelta non valida. Riprova.\n");
            break;
    }
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
    while(1) menuStack(&stack);
}
