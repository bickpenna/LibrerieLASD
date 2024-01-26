#include <stdio.h>
#include <stdlib.h>

typedef int *Stack;

//Funzioni
int isFull(Stack stack, int dim);
int isEmpty(Stack stack);
int defStack(Stack *stack);
void push(Stack stack, int dim, int value);
int pop(Stack stack);
int top(Stack stack);
void displayStack(Stack stack, int dim);
void sceltaMenu(int val, Stack *stack, int dim);
void menuStack(Stack *stack, int dim);

int isEmpty(Stack stack){
    if (stack[0] == 1) return 1;
    else return 0;
}

int isFull(Stack stack, int dim){
    if (stack[0] > dim) return 1;
    else return 0;
}

int defStack(Stack *stack){
    int dim;
    printf("Definisci la dimensione dello stack: ");
    scanf("%d", &dim);

    *stack = (int*) calloc(dim+1, sizeof(int));
    if (*stack == NULL) exit(EXIT_FAILURE);

    (*stack)[0]=1;
    return dim;
}

void push(Stack stack, int dim, int value) {
    if(isFull(stack, dim)) printf("Lo stack è pieno!! Elemento non inserito.");
    else{
        stack[stack[0]] = value;
        stack[0]++;
    }
}

int pop(Stack stack){
    int elemento;
    if(isEmpty(stack)) {
        printf("Lo stack è vuoto!!");
        return -1;
    }
    else {
        elemento = stack[stack[0]-1];
        stack[0]--;
        return elemento;
    }
}

int top(Stack stack) {
    if (isEmpty(stack)) {
        printf("Lo stack è vuoto!!");
        return -1;
    } else {
        return stack[stack[0]-1];
    }
}

void displayStack(Stack stack, int dim) {
    int dato;
    if(isEmpty(stack)) return;
    else {
        dato = pop(stack);
        printf("%d\n", dato);
        displayStack(stack, dim);
        push(stack, dim, dato);
    }
}

void sceltaMenu(int val, Stack *stack, int dim) {
    int value;
    switch(val) {
        case 1:
            printf("Inserisci l'elemento da aggiungere nello Stack: ");
            scanf("%d", &value);
            push(*stack, dim, value);
            break;
        case 2:
            value = pop(*stack);
            if(value != -1) printf("Elemento %d eliminato dallo stack", value);
            break;
        case 3:
            printf("Elemento in cima allo stack: %d\n", top(*stack));
            break;
        case 4:
            if (isEmpty(*stack)) printf("Lo stack è vuoto.\n");
            else printf("Lo stack non è vuoto.\n");
            break;
        case 5:
            displayStack(*stack, dim); 
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
}


void menuStack(Stack *stack, int dim) {
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

    sceltaMenu(val, stack, dim);
}

int main() {
    Stack stack;
    int dim = defStack(&stack);

    while(1) menuStack(&stack, dim);
}
