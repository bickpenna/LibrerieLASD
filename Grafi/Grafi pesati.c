#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int label;
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

void errore(int i){
    if (i == 1) printf("Errore di Allocazione. \n");
    if (i == 2) printf("Errore, nodo non fa parte del grafo\n");
    if (i == 3) printf("Errore generico\n");
    exit(1);
}

void creaGrafo(Grafo *graph){
    printf("Definisci la grandezza del grafo: ");
    scanf("%d", &graph->dim);

    graph->arr = (Nodo*) calloc(graph->dim,sizeof (Nodo));
    if(!graph->arr) errore(1);

    for (int i = 0; i < graph->dim; ++i) {
        graph->arr[i].dis = 0;
        graph->arr[i].adj = NULL;
    }
}

void definisciArco(Edge **edge, int nodo2, int peso, int *dis){
    (*edge) = (Edge *) malloc((sizeof (Edge)));
    if(!*edge) errore(1);

    (*edge)->label = nodo2;
    (*edge)->peso = peso;
    (*edge)->dis = dis;
    (*edge)->next = NULL;
}

Edge *getLast(Edge *edge){
    if(edge == NULL) return NULL;
    if(edge->next == NULL) return edge;
    else return getLast(edge->next);
}

void creaArco(Grafo graph){
    int nodo1, nodo2, peso;
    Edge *last, *newEdge;
    printf("Scrivi un arco: (Nodo1 -> Nodo2, Peso)\n");
    scanf("%d -> %d, %d", &nodo1, &nodo2, &peso);

    if(nodo1 > graph.dim-1 || nodo2 > graph.dim-1) errore(2);
    else{
        last = getLast(graph.arr[nodo1].adj);
        definisciArco(&newEdge, nodo2, peso, &graph.arr[nodo2].dis);

        if (last == NULL) graph.arr[nodo1].adj = newEdge;
        else last->next = newEdge;
    }
}

void creaArchi(Grafo graph){
    int archi;
    printf("Numeri di archi da inserire: ");
    scanf("%d", &archi);

    for(int i = 0; i<archi; i++){
        creaArco(graph);
    }
}

void disNod(Grafo graph){
    int i;
    printf("Nodo da disabilitare: ");
    scanf("%d", &i);
    graph.arr[i].dis = 1;
}

void stampaADJ(Edge *head){
    if(head == NULL){
        printf("NULL \n");
        return;
    }

    if(*head->dis != 1) printf("%d (%d) -> ", head->label, head->peso);

    stampaADJ(head->next);
}

void stampaGrafo(Grafo graph){
    for(int i = 0; i < graph.dim; i++){
        if(graph.arr[i].dis != 1) {
            printf("%d: ", i);
            stampaADJ(graph.arr[i].adj);
        }
    }
}

int main(){
    Grafo graph;

    creaGrafo(&graph);
    creaArchi(graph);
    stampaGrafo(graph);
    disNod(graph);
    stampaGrafo(graph);
}