#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int *link;

// Funzioni Coda
void defEmptyQueue(link queue){
    queue[0] = 0;
    queue[MAX] = 1;
}

int isEmpty(link queue){
    if(queue[0] == 0) return 1;
    return 0;
}

int isFull(link queue){
    if(queue[0] == queue[MAX+1]) return 1;
    return 0;
}

void enqueue(link queue, int dato){
    queue[queue[MAX+1]] = dato;

    queue[MAX+1] = (queue[MAX+1] % MAX) + 1;
    if(queue[0] == 0) queue[0] = 1;
}

int dequeue(link queue){
    int dato = queue[queue[0]];

    queue[0] = (queue[0] % MAX) + 1;
    if(queue[0] == queue[MAX+1])
        defEmptyQueue(queue);
    
    return dato;
}

void printQueue(link queue){
    int dato;
    if(!isEmpty(queue)){
        dato = dequeue(queue);
        printf("%d ", dato);
        printQueue(queue);
        enqueue(queue, dato);
    }
}

void reverse(link queue){
    int dato;
    if(!isEmpty(queue)){
        dato = dequeue(queue);
        reverse(queue);
        enqueue(queue, dato);
    }
}

// 1) Elimina Dispari
void eliminaDispari(link queue){
    int tmp[MAX+2];
    int dato;
    defEmptyQueue(tmp);

    while(!isEmpty(queue)){
        dato = dequeue(queue);
        if(dato % 2 == 0) enqueue(tmp, dato);
    }

    while(!isEmpty(queue))
        dato = dequeue(tmp);
        enqueue(queue, dato);
}

int main(){
    // Coda 1
    int queue1[MAX+2];
    defEmptyQueue(queue1);

    for(int i = 0; i < MAX-2; i++) enqueue(queue1, i);
    printf("\nCoda: ");
    printQueue(queue1);

    // 1) Elimina Dispari
    eliminaDispari(queue1);
    printf("\nCoda senza dispari: ");
    printQueue(queue1);
}