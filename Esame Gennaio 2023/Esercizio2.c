#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
struct Nodo{
    int dato;
    link prec;
    link next;
};

// Lista DLL
link getLast(link head);
link newNodo(int dato);
void insTesta(link *head, int dato);
void insCoda(link *head, int dato);
void delTesta(link *head);
void stampaLista(link head);
// Shuffle
void delHeaven(link *head);
void inserisciInOrdine(link *head, int dato);
void inserisciInL1(link *L1, link *L2);
void shuffle(link *L1, link *L2);
// Menu
int printMenu();
void menu(link *L1, link *L2);


// Liste Doppiamente Concatenate
link getLast(link head){
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

link newNodo(int dato){
    link new = (link) malloc(sizeof(struct Nodo));
    if(!new) exit(EXIT_FAILURE);

    new->dato = dato;
    new->prec = NULL;
    new->next = NULL;
    return new;
}

void insTesta(link *head, int dato){
    link new = newNodo(dato);
    new->next = *head;
    if (*head != NULL){
        new->prec = (*head)->prec;
        (*head)->prec = new;
    }

    *head = new;
}

void insCoda(link *head, int dato){
    if(*head == NULL){
        insTesta(head, dato);
        return;
    }
    link last = getLast(*head);
    link new = newNodo(dato);

    new->prec = last;
    last->next = new;
}

void delTesta(link *head){
    link tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void stampaLista(link head){
    if(head == NULL){
        printf("NULL \n");
        return;
    }
    printf("%d -> ", head->dato);
    stampaLista(head->next);
}

// Shuffle
void delHeaven(link *head){
    if(head == NULL || *head == NULL) return;
    
    if((*head)->dato % 2 == 0) {
        delTesta(head);
        delHeaven(head);
    } else if ((*head)->next != NULL) {
        delHeaven(&(*head)->next);
    }
}

void inserisciInOrdine(link *head, int dato){
    if(head == NULL || *head == NULL) return;
    if((*head)->dato > dato){
        insTesta(head, dato);
        return;
    }
    if((*head)->next == NULL){
        insCoda(head, dato);
        return;
    }
    inserisciInOrdine(&(*head)->next, dato);
}

void inserisciInL1(link *L1, link *L2){
    if(L1 == NULL || L2 == NULL) return;
    if(*L2 == NULL) return;
    inserisciInOrdine(L1, (*L2)->dato);
    inserisciInL1(L1, &(*L2)->next);
}

void shuffle(link *L1, link *L2){
    delHeaven(L1);
    delHeaven(L2);

    inserisciInL1(L1, L2);
}

// Menu
int printMenu(){
    int scelta;

    printf("\nMENU\n");
    printf("1) Stampa Struttura 1\n");
    printf("2) Stampa Struttura 2\n");
    printf("3) Aggiungi Elemento a Struttura 1\n");
    printf("4) Aggiungi Elemento a Struttura 2\n");
    printf("5) Shuffle!!\n");
    
    printf("99) ESCI!!\n");

    printf("\nScelta: ");
    scanf("%d", &scelta);
    return scelta;
}

void menu(link *L1, link *L2){
    int scelta = printMenu();
    int dato;
    switch(scelta) {
        case 1:
            printf("Struttura 1: ");
            stampaLista(*L1);
            break;
        case 2:
            printf("Struttura 2: ");
            stampaLista(*L2);
            break;
        case 3:
            printf("Elemento da aggiungere alla prima struttura: ");
            scanf("%d", &dato);
            insCoda(L1, dato);

            printf("Struttura 1: ");
            stampaLista(*L1);
            break;
        case 4:
            printf("Elemento da aggiungere alla seconda struttura: ");
            scanf("%d", &dato);
            insCoda(L2, dato);

            printf("Struttura 2: ");
            stampaLista(*L2);
            break;
        case 5:
            shuffle(L1, L2);
            printf("SHUFFLE!!: ");
            stampaLista(*L1);
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

int main(){
    link L1 = NULL;
    link L2 = NULL;

    while(1) menu(&L1, &L2);
}