#include <stdio.h>
#include <stdlib.h>

typedef Edge *link;
typedef struct Edge{
    int peso;
    int dest;
    int *dis
} Edge;

typedef struct Nodo{
    int dis;
    Edge *adj
} Nodo;

typedef struct Grafo{
    int dim;
    Nodo *arr;
} Grafo;

void creaGrafo(Grafo *graph, int dim){
    int i;
    graph->dim = dim;

    graph->arr = (Nodo *) calloc(graph->dim, sizeof(Nodo));
    if(!graph->arr) exit(EXIT_FAILURE);

    for(i = 0; i < graph->dim; i++){
        graph->arr[i].dis = 0;
        graph->arr[i].adj = NULL;
    }
}

link getLast(link head){
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;
    else return getLast(head->next);
}

link newArco(int dest, int peso, int *dis){
    link new = (link) malloc(sizeof(Edge));

    new->dest = dest;
    new->peso = peso;
    new->dis = dis;
    new->next = NULL;

    return new;
}

int esisteArco(link head, int dest){
    int check;
    if (head == NULL) return 0;
    if (head->dest == dest) return 1;
    else return esisteArco(head->next, dest);
}

void creaArco(Grafo graph, int src, int dest, int peso){
    link new, last;

    if (src > graph.dim - 1 || dest > graph.dim - 1) return;
    if (src < 0 || dest < 0) return;
    
    if (!esisteArco(graph.arr[src].adj, dest)){
        
        last = getLast(graph.arr[src].adj);
        new = newArco(dest, peso, &graph.arr[dest].dis);

        if (last == NULL)
            graph.arr[src].adj = new;
        else
            last->next = new;
    }
}

void disabilitaNodo(Grafo graph, int nodo){
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

void stampaGrafo(Grafo graph){
    int i;
    for(i = 0; i < graph.dim; i++){
        if(graph.arr[i].dis != 1){
            printf("%d: ", i);
            stampaADJ(graph.arr[i].adj);
        }
    }
}