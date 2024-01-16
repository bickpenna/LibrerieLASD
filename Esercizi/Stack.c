#include <stdio.h>
#include <stdlib.h>

typedef int *link;

// Stack
int isEmpty(link stack){
    if (stack[0] == 1) return 1;
    return 0;
}

int isFull(link stack, int dim){
    if (stack[0]> dim) return 1;
    return 0;
}

void defStack(link *stack, int dim){
    *stack = (int*) calloc(dim+1, sizeof(int));
    if (stack == NULL) exit(EXIT_FAILURE);
    
    (*stack)[0]=1;
}

void push(link stack, int dim, int dato){
    if(isFull(stack, dim)) printf("Lo stack è pieno, elemento non inserito\n");
    else{
        stack[stack[0]] = dato;
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

// 1) Crea un terzo stack con gli elementi pari dei due precedenti
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

// 2) Raddoppia Occorrenze di uno stack
void raddoppiaOccorrenze(link stack, int dim){
    int dato;
    if(isEmpty(stack)) return;

    dato = pop(stack);
    raddoppiaOccorrenze(stack, dim);
    push(stack, dim, dato);
    push(stack, dim, dato);
}

int main(){
    // Stack 1
    link stack1;
    int dim1 = 6; 
    
    defStack(&stack1, dim1+1);
    for(int i=0; i<dim1; i++) push(stack1, dim1, i);

    printf("Stack 1:\n");
    printStack(stack1, dim1);

    // Stack 2
    link stack2;
    int dim2 = 5;
    
    defStack(&stack2, dim2);
    for(int i=0; i<dim2; i++) push(stack2, dim2, i+10);

    printf("Stack 2:\n");
    printStack(stack2, dim2);


    // 1) Stack Pari
    link stackHeaven;
    int dimHeaven = dim1+dim2;

    defStack(&stackHeaven, dimHeaven);
    pushHeavenFrom2Stack(stackHeaven, dimHeaven, stack1, dim1, stack2, dim2);
    
    printf("Stack Heaven:\n");
    printStack(stackHeaven, dimHeaven);

    //2) Raddoppia Occorrenze Stack (lo stack deve essere grande il doppio)
    link stackRaddoppiato;
    int dimRaddoppiato = 10;

    defStack(&stackRaddoppiato, dimRaddoppiato);
    for(int i=0; i<dimRaddoppiato/2; i++)
        push(stackRaddoppiato, dimRaddoppiato, i+10);

    printf("Stack pre raddoppio:\n");
    printStack(stackRaddoppiato, dimRaddoppiato);

    raddoppiaOccorrenze(stackRaddoppiato, dimRaddoppiato);
    printf("Stack con occorrenze raddoppiate:\n");
    printStack(stackRaddoppiato, dimRaddoppiato);
}