#include <stdio.h>
#include <stdlib.h>
#define DIM 5

typedef int *Stack;

// Stack
void defStack(Stack stack);
int isEmpty(Stack stack);
int isFull(Stack stack);
void push(Stack stack, int dato);
int pop(Stack stack);
void printStack(Stack stack);
// Rimozione
void rimuoviCoppie(Stack S1, Stack S2);
// Menu
int printMenu();
void menu(Stack S1, Stack S2);

// Stack
int isEmpty(Stack stack){
    if (stack[0] == 1) return 1;
    return 0;
}

int isFull(Stack stack){
    if (stack[0]> DIM) return 1;
    return 0;
}

void defStack(Stack stack){
    stack[0]=1;
}

void push(Stack stack, int dato){
    if(isFull(stack)) printf("Lo stack è pieno, elemento non inserito\n");
    else{
        stack[stack[0]] = dato;
        stack[0]++;
    }
}

int pop(Stack stack){
    int elemento;
    if(!isEmpty(stack)){
        elemento = stack[stack[0]-1];
        stack[0]--;
        return elemento;
    }

    printf("Lo stack è vuoto!!");
    return -1;
}

void printStack(Stack stack){
    int dato;
    if(isEmpty(stack)) return;
    
    dato = pop(stack);
    printf("%d\n", dato);
    printStack(stack);
    push(stack, dato);
}

// Rimozione Coppie
void rimuoviCoppie(Stack S1, Stack S2){
    int dato1, dato2;
    if (isEmpty(S1) && isEmpty(S2)) return;
    else{
        dato1 = pop(S1);
        dato2 = pop(S2);

        rimuoviCoppie(S1, S2);

        if (dato1 == 2*dato2){
            push(S1, dato1);
            push(S2, dato2);
        }
    }
}

// Menu
int printMenu(){
    int scelta;

    printf("\nMENU\n");
    
    printf("1) Stampa Struttura 1\n");
    printf("2) Stampa Struttura 2\n");
    printf("3) Aggiungi Elementi a Strutture\n");
    printf("4) Rimuovi Coppie\n");
    
    printf("99) ESCI!!\n");

    printf("\nScelta: ");
    scanf("%d", &scelta);
    return scelta;
}

void menu(Stack S1, Stack S2){
    int scelta = printMenu();
    int dato1;
    int dato2;
    switch(scelta) {
        case 1:
            printf("Struttura 1: \n");
            printStack(S1);
            break;
        case 2:
            printf("Struttura 2: \n");
            printStack(S2);
            break;
        case 3:
            printf("Elemento da aggiungere alla prima struttura: ");
            scanf("%d", &dato1);
            
            printf("Elemento da aggiungere alla seconda struttura: ");
            scanf("%d", &dato2);

            push(S1, dato1);
            push(S2, dato2);
            
            printf("Struttura 1: \n");
            printStack(S1);

            printf("Struttura 2: \n");
            printStack(S2);
            break;
        case 4:
            rimuoviCoppie(S1, S2);

            printf("Struttura 1: \n");
            printStack(S1);

            printf("Struttura 2: \n");
            printStack(S2);
            break;
        case 99:
            printf("Uscita dal programma.\n");
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
}


// MAIN
int main(){
    int S1[DIM+1];
    int S2[DIM+1];

    defStack(S1);
    defStack(S2);

    while(1) menu(S1, S2);
}