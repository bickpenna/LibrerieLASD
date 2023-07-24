#include <stdio.h>
#include <stdlib.h>

int listaCreata = 0;

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
    if(!new) exit(EXIT_FAILURE);
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

void insIndice(link *head, int n){
    if(!head || !*head || n < 1) return;
    if (n == 1 || ((*head)->next == NULL && n == 2)){
        insTesta(head);
        return;
    }
    insIndice(&(*head)->next, n-1);
}

void elTesta(link *head){
    link tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void elCoda(link *head){
    if ((*head)->next == NULL) elTesta(head);
    else elCoda(&(*head)->next);
}

void elIndice(link *head, int n){
    if(!head || !*head || n < 1 || (*head)->next == NULL && n > 1) return;
    if (n == 1){
        elTesta(head);
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
            if (!listaCreata) {
                creaLista(head);
                printf("Lista creata con successo.\n");
                listaCreata = 1;
            } else {
                printf("La lista è già stata creata.\n");
            }
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
            elTesta(head);
            printf("Elemento in testa eliminato.\n");
            break;
        case 6:
            elCoda(head);
            printf("Elemento in coda eliminato.\n");
            break;
        case 7:
            printf("Elimina all'indice: ");
            scanf("%d", &indice);
            elIndice(head, indice);
            printf("Elemento eliminato nella posizione %d.\n", indice);
            break;
        case 8:
            eliminaLista(head);
            printf("La lista è stata cancellata.\n");
            break;
        case 9:
            printf("Lista:\n");
            stampaLista(*head);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }

    if(val != 9 && val != 8) {
        printf("Lista:\n");
        stampaLista(*head);
    }
}

void menu(link *head){
    int val;

    printf("\n-- Menù delle operazioni --\n");

    if (!listaCreata) {
        printf("1. Crea una lista\n");
    }
    printf("2. Inserisci in testa alla lista\n");
    printf("3. Inserisci in coda alla lista\n");
    printf("4. Inserisci nel mezzo della lista\n");
    printf("5. Elimina elemento in testa\n");
    printf("6. Elimina elemento in coda\n");
    printf("7. Elimina un elemento nel mezzo della lista\n");
    printf("8. Elimina la lista\n");
    printf("9. Stampa la lista\n");
    printf("0. Esci\n");

    printf("---------------------------\n");
    printf("Scelta: ");
    scanf("%d", &val);

    sceltaM(head, val);
}

//------------------


int main(){
    link head = NULL;

    while(1) menu(&head);
}