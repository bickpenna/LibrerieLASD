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

link findMin(link root){
    if(root == NULL) return NULL;
    while(root->sx != NULL){
        root = root->sx;
    }
    return root;
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

void preorder(link root){
    if(root != NULL){
        printf("%d ", root->dato);
        preorder(root->sx);
        preorder(root->dx);
    }
}

void inorder(link root){
    if(root != NULL){
        inorder(root->sx);
        printf("%d ", root->dato);
        inorder(root->dx);
    }
}

void postorder(link root){
    if(root != NULL){
        postorder(root->sx);
        postorder(root->dx);
        printf("%d ", root->dato);
    }
}

void freeTree(link root){
    if(root != NULL){
        freeTree(root->sx);
        freeTree(root->dx);
        free(root);
    }
}

int stampaMenu() {
    int scelta;
    printf("\n--- MENU ---\n");
    printf("1. Inserisci un nodo\n");
    printf("2. Cerca un nodo\n");
    printf("3. Cerca il minimo\n");
    printf("4. Elimina un nodo\n");
    printf("5. Stampa l'albero (in ordine)\n");
    printf("0. Esci\n");
    printf("Scegli un'opzione: ");
    scanf("%d", &scelta);
    return scelta;
}

void Menu(link *root) {
    int choice, value;
    choice = stampaMenu();
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
            link minNode = findMin(*root);
            if(minNode){
                printf("Nodo minimo: %d\n", minNode->dato);
            } else {
                printf("Albero vuoto.\n");
            }
            break;
        case 4:
            printf("Inserisci il valore del nodo da eliminare: ");
            scanf("%d", &value);
            delete(root, value);
            printf("Nodo eliminato (se esistente).\n");
            break;
        case 5:
            printf("Scegli il metodo di stampa:\n");
            printf("1. In order\n");
            printf("2. Preorder\n");
            printf("3. Postorder\n");
            printf("Scegli un'opzione: ");
            
            int stampa_choice;
            scanf("%d", &stampa_choice);

            switch(stampa_choice) {
                case 1:
                    printf("Albero (in order): ");
                    inorder(*root);
                    printf("\n");
                    break;
                case 2:
                    printf("Albero (preorder): ");
                    preorder(*root);
                    printf("\n");
                    break;
                case 3:
                    printf("Albero (postorder): ");
                    postorder(*root);
                    printf("\n");
                    break;
                default:
                    printf("Opzione non valida. Riprova.\n");
            }
            break;
        case 0:
            printf("Uscita...\n");
            break;
        default:
            printf("Opzione non valida. Riprova.\n");
    }
}


int main() {
    link root = NULL;
    while(1) menu(root);
    freeTree(root);
    return 0;
}

