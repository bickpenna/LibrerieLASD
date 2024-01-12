#include <stdio.h>
#include <stdlib.h>

typedef struct Edge *link;
typedef struct Edge{
    int dest;
    int peso;
    int *dis;
    struct Edge *next;
} Edge;

typedef struct Nodo{
    int dis;
    Edge *adj;
} Nodo;

typedef struct Grafo{
    int dim;
    Nodo *arr;
} Grafo;

typedef int **Matrice;
typedef struct GrafoAM{
    int dim;
    Matrice matrix;
}GrafoAM;

// Grafo Lista di Adiacenza
void creaGrafoAL(Grafo *graph, int dim){
    int i;
    graph->dim = dim;
    graph->arr = (Nodo*) calloc(graph->dim, sizeof(Nodo));
    if(!graph->arr) exit(EXIT_FAILURE);

    for(i = 0; i < dim; i++){
        graph->arr[i].dis = 0;
        graph->arr[i].adj = NULL;
    }
}

link getLast(link head){
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

link newArcoGAL(int dest, int peso, int *dis){
    link new = (link) malloc(sizeof(Edge));

    new->dest = dest;
    new->peso = peso;
    new->dis = dis;
    new->next = NULL;

    return new;
}

int esisteArcoGAL(link head, int dest){
    int check;
    if (head == NULL) return 0;
    if (head->dest == dest) return 1;
    else return esisteArcoGAL(head->next, dest);
}

void creaArcoGAL(Grafo graph, int src, int dest, int peso){
    link last, newEdge;

    if (src > graph.dim -1 || dest > graph.dim -1) return;
    else if (!esisteArcoGAL(graph.arr[src].adj, dest)) {
        
        last = getLast(graph.arr[src].adj);
        newEdge = newArcoGAL(dest, peso, &graph.arr[dest].dis);

        if (last == NULL)
            graph.arr[src].adj = newEdge;
        else
            last->next = newEdge;
    }
}

void disNodoGAL(Grafo graph, int nodo){
    graph.arr[nodo].dis = 1;
}

void stampaADJ(link head){
    if(head == NULL){
        printf("NULL \n");
        return;
    }

    if(*head->dis != 1)
        printf("%d (%d) -> ", head->dest, head->peso);
    
    stampaADJ(head->next);
}

void stampaGrafoAL(Grafo graph){
    int i;
    for(i = 0; i < graph.dim; i++){
        if(graph.arr[i].dis != 1){
            printf("%d: ", i);
            stampaADJ(graph.arr[i].adj);
        }
    }
}

// Grafo Matrice di Adiacenza
void creaADM(Matrice *matrix, int dim){
    int i;
    *matrix = (Matrice) calloc(dim, sizeof(int *));
    
    for(i=0; i<dim; i++){
        (*matrix)[i] = (int *) calloc(dim, sizeof(int));
    }
}

void creaGrafoAM(GrafoAM *graph, int dim){
    graph->dim = dim;
    creaADM(&graph->matrix, graph->dim);
}

void creaArcoGAM(GrafoAM graph, int src, int dest, int peso){
    graph.matrix[src][dest] = peso;
}

void disNodoGAM(GrafoAM graph, int nodo){
    int i;
    for(i = 0; i < graph.dim; i++){
        graph.matrix[nodo][i] = 0;
        graph.matrix[i][nodo] = 0;
    }
}

void stampaGrafoAM_Matrix(GrafoAM graph){
    int i, j;

    for(i = 0; i < graph.dim; i++){
        for(j = 0; j < graph.dim; j++){
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }
}

void stampaGrafoAM(GrafoAM graph){
    int i, j;

    for(i = 0; i < graph.dim; i++){
        printf("%d: ", i);
        for(j = 0; j < graph.dim; j++){
            if(graph.matrix[i][j] != 0)
                printf("%d (%d) -> ", j, graph.matrix[i][j]);
        }
        printf("NULL \n");
    }
}

// Esercizio
void creaGrafoComune(GrafoAM *graph3, Grafo graphL, GrafoAM graphM){
    if(graphL.dim <= graphM.dim)
        creaGrafoAM(graph3, graphL.dim);
    else
        creaGrafoAM(graph3, graphM.dim);

    int src, dest;

    for(src = 0; src < graphM.dim; src++){
        for(dest = 0; dest < graphM.dim; dest++){
            if(graphM.matrix[src][dest] != 0){
                if(esisteArcoGAL(graphL.arr[src].adj, dest)){
                    creaArcoGAM((*graph3), src, dest, graphM.matrix[src][dest]);
                }
            }
        }
    }    
}

int main(){
    int dim = 4;
    
    Grafo graphL;
    creaGrafoAL(&graphL, dim);

    creaArcoGAL(graphL, 0, 1, 1);
    creaArcoGAL(graphL, 1, 2, 1);
    creaArcoGAL(graphL, 1, 3, 1);
    creaArcoGAL(graphL, 2, 3, 1);

    printf("Grafo AL: \n");
    stampaGrafoAL(graphL);

    GrafoAM graphM;
    creaGrafoAM(&graphM, dim);

    creaArcoGAM(graphM, 0, 1, 1);
    creaArcoGAM(graphM, 1, 2, 1);
    creaArcoGAM(graphM, 1, 3, 1);
    creaArcoGAM(graphM, 2, 3, 1);

    printf("\nGrafo AM: \n");
    stampaGrafoAM(graphM);

    GrafoAM graph3;
    creaGrafoComune(&graph3, graphL, graphM);

    printf("\nGrafo 3: \n");
    stampaGrafoAM(graph3);

}