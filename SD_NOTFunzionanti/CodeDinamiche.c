#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
struct Nodo{
    int val;
    link next;
};

//Funzioni

void enqueue(link *coda, int e);
int dequeue(link *coda);
void stampa(link *coda);

void stampaMenu();
void menu(int *coda);


link allcoaElemento(int e){
    link new = (link) malloc(sizeof(struct Nodo));
    if(!new) exit(EXIT_FAILURE);
    new->val=e;
    new->next=NULL
}

void enqueue(link *coda, int e){
    link new = allocaElemento(e);
    if(*coda = NULL) 
}


int main(){
    link coda=NULL;

    while(1){
        menu(&coda);
    }
}