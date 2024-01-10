#include <stdio.h>
#include <stdlib.h>

typedef int *link;

int isEmpty(link stack){
    if (stack[0] == 1) return 1;
    return 0;
}

int isFull(link stack, int dim){
    if (stack[0]> dim) return 1;
    return 0;
}

int defStackHeaven(link *stack, int dim){
    *stack = (int*) calloc(dim+1, sizeof(int));
    if (stack == NULL) exit(EXIT_FAILURE);
    
    (*stack)[0]=1;
    
    return dim;
}

int defStack(link *stack){
    int dim;
    printf("Definisci la dimensione dello stack: ");
    scanf("%d", &dim);

    *stack = (int*) calloc(dim+1, sizeof(int));
    if (stack == NULL) exit(EXIT_FAILURE);
    
    (*stack)[0]=1;
    
    return dim;
}

void push(link stack, int dim, int value){
    if(isFull(stack, dim)) printf("Lo stack è pieno, elemento non inserito");
    else{
        stack[stack[0]] = value;
        stack[0]++;
    }
}

int pop(link stack){
    int elemento;
    if(!isEmpty(stack)){
        elemento = stack[stack[0]-1];
        stack[0]--;
        return elemento;
    }

    printf("Lo stack è vuoto!!");
    return -1;
}

void printStack(link stack, int dim){
    int dato;
    if(isEmpty(stack)) return;
    
    dato = pop(stack);
    printf("%d\n", dato);
    printStack(stack, dim);
    push(stack, dim, dato);
}

void pushHeaven(link stackH, int dimH, link stackI, int dimI){
    int dato;
    if(isEmpty(stackI)) return;

    dato = pop(stackI);
    if(dato%2 == 0) push(stackH, dimH, dato);
    pushHeaven(stackH, dimH, stackI, dimI);
    push(stackI, dimI, dato);
}

void pushHeavenFrom2Stack(link stackH, int dimH, link stack1, int dim1, link stack2, int dim2){
    pushHeaven(stackH, dimH, stack1, dim1);
    pushHeaven(stackH, dimH, stack2, dim2);
}

int main(){
    link stack1;
    link stack2;
    link stackH;
    int dim1, dim2, dimH;
    
    dim1 = defStack(&stack1);
    dim2 = defStack(&stack2);
    dimH = dim1+dim2;

    for(int i=0; i<dim1; i++) push(stack1, dim1, i);
    for(int i=0; i<dim2; i++) push(stack2, dim2, i+10);

    printf("Stack 1:\n");
    printStack(stack1, dim1);

    printf("Stack 2:\n");
    printStack(stack2, dim2);

    defStackHeaven(&stackH, dimH);
    pushHeavenFrom2Stack(stackH, dimH, stack1, dim1, stack2, dim2);

    printf("Stack H:\n");
    printStack(stackH, dimH);
}