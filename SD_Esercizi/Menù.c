#include <stdio.h>

void menu(int dato){
    switch(dato) {
        case 0:
        
            rintf("Struttura: \n");

            break;
        case 1:
            printf("Struttura: \n");
            break;
        case 2:
            printf("Elemento aggiunto: \n");

            rintf("Struttura: \n");
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

void printMenu(){
    int dato;

    printf("0) Crea Struttura\n");
    printf("1) Stampa Struttura\n");
    printf("2) Aggiungi Elemento\n");
    
    printf("99) ESCI!!\n");

    scanf("%d", &dato);
    menu(dato);
}