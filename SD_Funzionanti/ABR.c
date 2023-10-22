#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo *link;
typedef struct Nodo{
    int dato;
    link sx;
    link dx;
}Nodo;

//Funzioni
link newNodo();
void insert(link *root, int value);
link search(link root, int value);
void delete(link *root, int value);
void inorder(link root);
void freeTree(link root);
void menu(link *root);


link newNodo(){
    link new = (link) malloc(sizeof(struct Nodo));
    if(!new) exit(EXIT_FAILURE);
    printf("Inserisci valore: ");
    scanf("%d", &new->dato);
    new->sx=NULL;
    new->dx=NULL;
    return new;
}

void insert(link *root, int value){
    if(*root == NULL){
        *root = (link) malloc(sizeof(struct Nodo));
        if(!*root) exit(EXIT_FAILURE);
        (*root)->dato = value;
        (*root)->sx = NULL;
        (*root)->dx = NULL;
    } else {
        if(value < (*root)->dato){
            insert(&(*root)->sx, value);
        } else if(value > (*root)->dato){
            insert(&(*root)->dx, value);
        }
    }
}

link search(link root, int value){
    if(root == NULL || root->dato == value){
        return root;
    }
    if(value < root->dato){
        return search(root->sx, value);
    } else {
        return search(root->dx, value);
    }
}

void delete(link *root, int value){
    if(*root == NULL) return;

    if(value < (*root)->dato){
        delete(&(*root)->sx, value);
    } else if(value > (*root)->dato){
        delete(&(*root)->dx, value);
    } else {
        if((*root)->sx == NULL){
            link temp = *root;
            *root = (*root)->dx;
            free(temp);
        } else if((*root)->dx == NULL){
            link temp = *root;
            *root = (*root)->sx;
            free(temp);
        } else {
            link temp = (*root)->dx;
            while(temp->sx != NULL){
                temp = temp->sx;
            }
            (*root)->dato = temp->dato;
            delete(&(*root)->dx, temp->dato);
        }
    }
}

void inorder(link root){
    if(root != NULL){
        inorder(root->sx);
        printf("%d ", root->dato);
        inorder(root->dx);
    }
}

void freeTree(link root){
    if(root != NULL){
        freeTree(root->sx);
        freeTree(root->dx);
        free(root);
    }
}

void menu(link *root) {
    int choice, value;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserisci un nodo\n");
        printf("2. Cerca un nodo\n");
        printf("3. Elimina un nodo\n");
        printf("4. Stampa l'albero (in ordine)\n");
        printf("5. Esci\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Inserisci il valore del nodo: ");
                scanf("%d", &value);
                insert(root, value);
                break;
            case 2:
                printf("Inserisci il valore del nodo da cercare: ");
                scanf("%d", &value);
                if(search(*root, value)) {
                    printf("Nodo trovato!\n");
                } else {
                    printf("Nodo non trovato.\n");
                }
                break;
            case 3:
                printf("Inserisci il valore del nodo da eliminare: ");
                scanf("%d", &value);
                delete(root, value);
                printf("Nodo eliminato (se esistente).\n");
                break;
            case 4:
                printf("Albero (in ordine): ");
                inorder(*root);
                printf("\n");
                break;
            case 5:
                printf("Uscita...\n");
                break;
            default:
                printf("Opzione non valida. Riprova.\n");
        }
    } while(choice != 5);
}

int main() {
    link root = NULL;
    menu(&root);
    freeTree(root);
    return 0;
}

