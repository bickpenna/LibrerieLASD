#include <stdio.h>
#include <stdlib.h>

typedef int *link;

int defStack(link *stack){
    int dim;
    printf("Definisci la dimensione dello stack: ");
    scanf("%d", &dim);

    *stack = (int*) calloc(dim+1, sizeof(int));
    if (*stack == NULL) exit(EXIT_FAILURE);

    (*stack)[0]=1;
    return dim;
}

int isEmpty(link stack){
    if (stack[0] == 1) return 1;
    else return 0;
}

int isFull(link stack, int dim){
    if (stack[0] == dim) return 1;
    else return 0;
}

void push(link stack, int dim, int value) {
    if(isFull(stack, dim)) printf("Lo stack è pieno!! Elemento non inserito.");
    else{
        stack[stack[0]] = value;
        stack[0]++;
    }
}

int pop(link stack){
    int elemento;
    if(isEmpty(stack)) {
        printf("Lo stack è vuoto!!");
        return -1;
    }
    else {
        elemento = stack[stack[0]];
        stack[0]--;
        return elemento;
    }
}

void sceltaMenu(int val, link *stack, int dim) {
    int value;
    switch(val) {
        case 1:
            printf("Inserisci l'elemento da aggiungere nello Stack: ");
            scanf("%d", &value);
            push(stack, dim, value);
            break;
        case 2:
            value = pop(stack);
            if(value != -1) printf("Elemento %d eliminato dallo stack", value);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
}

void menuStack(link *stack, int dim) {
    int val;
    printf("\n-- Menù Operazioni Stack --\n");

    printf("\nOperazioni di Inserimento:\n");
    printf("1. Push (Aggiungi un elemento in cima allo stack)\n");

    printf("\nOperazioni di Rimozione:\n");
    printf("2. Pop (Rimuovi l'elemento in cima allo stack)\n");

    /*printf("\nOperazioni di Visualizzazione:\n");
    printf("3. Top (Visualizza l'elemento in cima allo stack)\n");
    printf("4. Controllo Stack Vuoto\n");
    printf("5. Mostra tutti gli elementi dello stack\n");*/

    printf("\nUscire:\n");
    printf("0. Esci\n");
    printf("-----------------------------\n");
    printf("Scelta: ");
    scanf("%d", &val);

    sceltaMenu(val, stack, dim);
}

int main() {
    link stack;
    int dim = defStack(&stack);

    while(1) menuStack(&stack, dim);
}
