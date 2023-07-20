#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
struct Nodo {
    int dato;
    link next;
};

void stampaLista(link head){
    if(head == NULL){
        printf("NULL \n");
        return;
    } else {
        printf("%d -> ", head->dato);
        stampaLista(head->next);
    }
}

link newNodo(){
    link new = (link) malloc(sizeof(struct Nodo));
    new->dato = 0;
    new->next = NULL;
    return new;
}

link getLast(link head){
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

link creaLista(){
    link head = NULL;
    int n = 0;
    printf("Inserire dimensione della lista: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        link new = newNodo();
        printf("Inserisci il %d° valore: ", i+1);
        scanf("%d", &new->dato);
        if(head == NULL) head = new;
        else getLast(head)->next=new;
    }
    return head;
}

int main(){
    link head;

    head = creaLista();
    stampaLista(head);
}