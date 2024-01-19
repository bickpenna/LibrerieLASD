#include <stdio.h>
#include <stdlib.h>
#define MAX 10


// Funzioni Coda
void defEmptyQueue(int queue[]){
    queue[0] = 0;
    queue[MAX+1] = 1;
}

int isEmpty(int queue[]){
    return queue[0] == 0;
}

int isFull(int queue[]){
    return queue[MAX+1] == queue[0];
}

void enqueue(int queue[], int dato){
    queue[queue[MAX+1]] = dato;

    if(queue[0] == 0) queue[0] = 1;
    queue[MAX+1] = (queue[MAX+1] % MAX) + 1;    
}

int dequeue(int queue[]){
    int dato = queue[queue[0]];

    queue[0] = (queue[0] % MAX) + 1;

    if(queue[0] == queue[MAX+1]){
        queue[0] = 0;
        queue[MAX+1] = 1;
    }
    
    return dato;
}

void printQueue(int queue[]){
    int dato;
    if(!isEmpty(queue)){
        dato = dequeue(queue);
        printf("%d ", dato);
        printQueue(queue);
        enqueue(queue, dato);
    }
}

void reverse(int queue[]){
    int dato;
    if(!isEmpty(queue)){
        dato = dequeue(queue);
        reverse(queue);
        enqueue(queue, dato);
    }
}

// 1) Elimina Dispari
void eliminaDispari(int queue[]){
    int dato;
    if(!isEmpty(queue)){
        dato = dequeue(queue);
        if (dato % 2 == 0) enqueue(queue, dato);
        eliminaDispari(queue);
    }
}

int main(){
    // Coda 1
    int queue1[MAX+2];
    defEmptyQueue(queue1);

    for(int i = 0; i < MAX; i++) enqueue(queue1, i);
    printf("\nCoda: ");
    printQueue(queue1);

    // 1) Elimina Dispari
    //eliminaDispari(queue1);
    //printf("\nCoda senza dispari: ");
    //printQueue(queue1);
}