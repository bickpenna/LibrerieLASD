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
    }
    printf("%d -> ", head->dato);
    stampaLista(head->next);
}

link newNodo(){
    link new = (link) malloc(sizeof(struct Nodo));
    printf("Inserisci il valore: ");
    scanf("%d", &new->dato);
    new->next = NULL;
    return new;
}

link getLast(link head){
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

void insTesta(link *head){
    link new = newNodo();
    new->next = *head;
    *head = new;
}

void insCoda(link *head){
    link new = newNodo();
    if(*head == NULL) *head = new;
    else getLast(*head)->next = new;
}

void insIndice(link *head, int i){
    if (i < 0) return;

} //DA FINIRE



void elIndice(link *head, int n){
    if(!head || !*head || n < 1) return;
    if (n == 1){
        link temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    elIndice(&(*head)->next, n-1);
}

void creaLista(link *head){
    int n = 0;
    printf("Inserire dimensione della lista: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        insCoda(head);
    }
}

void eliminaListaREC(link head){
    if (head == NULL) return;
    eliminaListaREC(head->next);
    free(head);
}

void eliminaLista(link *head){
    eliminaListaREC(*head);
    *head = NULL;
}

//-------MENÙ-------

void sceltaM(link *head, int val) {
    int indice;

    switch(val) {
        case 1:
            creaLista(head);
            printf("Lista creata con successo.\n");
            break;
        case 2:
            insTesta(head);
            printf("Elemento inserito in testa alla lista.\n");
            break;
        case 3:
            insCoda(head);
            printf("Elemento inserito in coda alla lista.\n");
            break;
        case 4:
            printf("Inserisci l'indice: ");
            scanf("%d", &indice);
            insIndice(head, indice);
            printf("Elemento inserito nella lista all'indice %d.\n", indice);
            break;
        case 5:
            printf("Lista:\n");
            stampaLista(*head);
            break;
        case 6:
            eliminaLista(head);
            printf("La lista è stata cancellata.\n");
            break;
        case 7:
            printf("Elimina all'indice: ");
            scanf("%d", &indice);
            elIndice(head, indice);
            printf("Elemento eliminato nella posizione %d.\n", indice);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }

    if(val != 5 && val != 6) {
        printf("Lista:\n");
        stampaLista(*head);
    }
}


void menu(link *head){
    int val;
    printf("\n-- Menù delle operazioni --\n");
    printf("1. Crea una lista\n");
    printf("2. Inserisci in testa alla lista\n");
    printf("3. Inserisci in coda alla lista\n");
    printf("4. Inserisci nel mezzo della lista\n");
    printf("5. Stampa la lista\n");
    printf("6. Elimina la lista\n");
    printf("7. Elimina un elemento nel mezzo della lista\n");
    printf("0. Esci\n");
    printf("---------------------------\n");
    printf("Scelta: ");
    scanf("%d", &val);

    sceltaM(head, val);
}

//------------------


int main(){
    link head=NULL;

    while(1) menu(&head);
}