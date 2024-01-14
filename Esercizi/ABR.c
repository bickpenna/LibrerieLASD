#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo *link;
struct Nodo{
    int dato;
    link sx;
    link dx;
};

link newNodo(int dato){
    link new = (link) malloc(sizeof(struct Nodo));

    new->dato = dato;
    new->sx = NULL;
    new->dx = NULL;

    return new;
}

void insertABR(link *root, int dato){
    if(*root == NULL) *root = newNodo(dato);
    else{
        if(dato < (*root)->dato)
            insertABR(&(*root)->sx, dato);
        else if (dato > (*root)->dato)
            insertABR(&(*root)->dx, dato);
    }
}

link minABR(link root){
    if(root == NULL) return NULL;

    if(root -> sx != NULL) minABR(root->sx);
    return root;
}

void delNodo(link *root, int dato){
    if((*root) == NULL) return;

    if(dato < (*root)->dato)
        delNodo(&(*root)->sx, dato);
    else if (dato > (*root)->dato)
        delNodo(&(*root)->dx, dato);
    else{
        if((*root)->sx == NULL && (*root)->dx == NULL){
            free(*root);
            *root = NULL;
        }
        else if((*root)->sx == NULL){
            link tmp;
            tmp = *root;
            *root = (*root)->dx;
            free(tmp);
        }
        else if((*root)->dx == NULL){
            link tmp;
            tmp = *root;
            *root = (*root)->sx;
            free(tmp);
        }
        else{
            link min = minABR((*root)->dx);
            (*root)->dato = min->dato;
            delNodo(&(*root)->dx, min->dato);
        }
    }
}

void printInOrder(link root){
    if(root){
        printInOrder(root->sx);
        printf("%d ", root->dato);
        printInOrder(root->dx);
    }
}

int main(){
    // ABR 1
    link root = NULL;
    int dim = 5;
    srand(10);

    for(int i = 0; i<dim; i++)
        insertABR(&root, rand()%100);
    printInOrder(root);

    int del = 70;
    delNodo(&root, del);
    printf("\nSenza %d: ", del);
    printInOrder(root);
}