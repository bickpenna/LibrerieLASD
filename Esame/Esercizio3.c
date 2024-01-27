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
void creaGrafoAL(Grafo *graph, int dim);
link getLast(link head);
int esisteArcoGAL(link head, int dest);
link newArcoGAL(int dest, int peso, int *dis);
void creaArcoGAL(Grafo graph, int src, int dest, int peso);
void stampaADJ(link head);
void stampaGrafoAL(Grafo graph);
// Grafo Matrice di Adiacenza
void creaADM(Matrice *matrix, int dim);
void creaGrafoAM(GrafoAM *graph, int dim);
void creaArcoGAM(GrafoAM graph, int src, int dest, int peso);
void stampaGrafoAM(GrafoAM graph);
// Sottrazione dei grafi
GrafoAM sottraiGrafiM(Grafo graph1, GrafoAM graph2);
void aggiornaPeso(link head, int dest, int *peso);
Grafo sottraiGrafiADJ(Grafo graph1, GrafoAM graph2);
// Menu
int printMenu();
void menu(Grafo *graph1, GrafoAM *graph2);


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

int esisteArcoGAL(link head, int dest){
    if (head == NULL) return 0;
    if (head->dest == dest) return 1;
    else return esisteArcoGAL(head->next, dest);
}

link newArcoGAL(int dest, int peso, int *dis){
    link new = (link) malloc(sizeof(Edge));

    new->dest = dest;
    new->peso = peso;
    new->dis = dis;
    new->next = NULL;

    return new;
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

// G1 - G2
int verificaArco(link head, int dest, int *peso){
    if (head == NULL) return 0;
    if (head->dest == dest){
        *peso = head->peso - *peso;
        return 1;
    }
    return verificaArco(head->next, dest, peso);
}

GrafoAM sottraiGrafiM(Grafo graph1, GrafoAM graph2){
    GrafoAM DM;
    creaGrafoAM(&DM, graph2.dim);
    int peso;

    for(int src = 0; src<graph2.dim; src++){
        for(int dest = 0; dest<graph2.dim; dest++){
            peso = graph2.matrix[src][dest];
            if(verificaArco(graph1.arr[src].adj, dest, &peso)){
                if(peso > 0)
                    creaArcoGAM(DM, src, dest, peso);
            }
        }
    }
    return DM;
}

// G2 - G1
void aggiornaPeso(link head, int dest, int *peso){
    if (head == NULL) return;
    if (head->dest == dest){
        *peso = *peso - head->peso;
        return;
    }
    aggiornaPeso(head->next, dest, peso);
}

Grafo sottraiGrafiADJ(Grafo graph1, GrafoAM graph2){
    Grafo DL;
    creaGrafoAL(&DL, graph2.dim);
    int peso;

    for(int src = 0; src<graph2.dim; src++){
        for(int dest = 0; dest<graph2.dim; dest++){
            peso = graph2.matrix[src][dest];
            aggiornaPeso(graph1.arr[src].adj, dest, &peso);
            if(peso > 0)
                creaArcoGAL(DL, src, dest, peso);
        }
    }
    return DL;
}

int printMenu(){
    int scelta;

    printf("\nMENU\n");
    
    printf("1) Stampa Grafo Lista di Adiacenza\n");
    printf("2) Stampa Grafo Matrice di Adiacenza\n");
    printf("3) Aggiungi Arco al Grafo Lista di Adiacenza\n");
    printf("4) Aggiungi Arco al Grafo Matrice di Adiacenza\n");
    printf("5) Calcola Differenza Grafi (Lista - Matrice)\n");
    printf("6) Calcola Differenza Grafi (Matrice - Lista)\n");
    
    printf("99) ESCI\n");

    printf("\nScelta: ");
    scanf("%d", &scelta);
    return scelta;
}

void menu(Grafo *graph1, GrafoAM *graph2){
    int scelta = printMenu();
    int src, dest, peso;

    switch(scelta) {
        case 1:
            printf("Grafo Lista di Adiacenza: \n");
            stampaGrafoAL(*graph1);
            break;
        case 2:
            printf("Grafo Matrice di Adiacenza: \n");
            stampaGrafoAM(*graph2);
            break;
        case 3:
            printf("Inserisci origine, destinazione e peso dell'arco (ES: 0 1 5): ");
            scanf("%d %d %d", &src, &dest, &peso);
            creaArcoGAL(*graph1, src, dest, peso);
            break;
        case 4:
            printf("Inserisci origine, destinazione e peso dell'arco (ES: 0 1 5): ");
            scanf("%d %d %d", &src, &dest, &peso);
            creaArcoGAM(*graph2, src, dest, peso);
            break;
        case 5:
            printf("Calcolo Differenza Grafi (Lista - Matrice)\n");
            GrafoAM DM = sottraiGrafiM(*graph1, *graph2);
            stampaGrafoAM(DM);
            break;
        case 6:
            printf("Calcolo Differenza Grafi (Matrice - Lista)\n");
            Grafo DL = sottraiGrafiADJ(*graph1, *graph2);
            stampaGrafoAL(DL);
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
    int dim;
    Grafo graph1;
    GrafoAM graph2;

    printf("Inserisci la dimensione dei grafi: ");
    scanf("%d", &dim);
    creaGrafoAL(&graph1, dim);
    creaGrafoAM(&graph2, dim);

    while(1) menu(&graph1, &graph2);
}