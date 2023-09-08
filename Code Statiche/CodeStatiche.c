#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void errore(int e){
    if (e == 1) printf("Coda piena, nessun inserimento");
    if (e == 2) printf("Coda vuota, nessun elemento rimosso");
}

void defCoda(int *coda){
    coda[0] = 0; //TESTA
    coda[MAX+1] = coda[0] + 1; //CODA
}

int empty(int *coda){
    if (coda[0] == coda[MAX +1]) return 1;
    else return 0;
}

int full(int *coda){
    if ((coda[MAX+1] + 1) % MAX == coda[0]) return 1;
    else return 0;
}

void enqueue(int *coda, int e){
    if(!full(coda)){
            coda[coda[MAX+1]] = e;
            coda[MAX+1] = (coda[MAX+1] + 1) % MAX;
    } else errore(1);
}

int dequeue(int *coda){
    int e;
    if(!empty(coda)){
        e = coda[coda[0]];
        coda[0] = (coda[0] + 1) % MAX;
        return e;
    } else errore(2);
    return -1;
}

void stampa(int *coda){
    int e;
    if(!empty(coda)){
        e = dequeue(coda);
        printf("%d, ", e);
        stampa(coda);
        enqueue(coda, e);
    }
}

void stampaMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Inserisci un elemento\n");
    printf("2. Rimuovi un elemento\n");
    printf("3. Stampa la coda\n");
    printf("4. Esci\n");
    printf("Scegli un'opzione: ");
}

void menu(int *coda) {
    int scelta, valore;
    stampaMenu();
    scanf("%d", &scelta);
    switch (scelta) {
        case 1:
            printf("Inserisci il valore: ");
            scanf("%d", &valore);
            enqueue(coda, valore);
            break;
        case 2:
            valore = dequeue(coda);
            if (valore != -1) {
                printf("Valore rimosso: %d\n", valore);
            }
            break;
        case 3:
            printf("Coda: ");
            stampa(coda);
            printf("\n");
            break;
        case 4:
            exit(0);
        default:
            printf("Scelta non valida! Riprova.\n");
            break;
    }
}

int main(){
    int coda[MAX+2];
    defCoda(coda);
    while(1) menu(coda);
}