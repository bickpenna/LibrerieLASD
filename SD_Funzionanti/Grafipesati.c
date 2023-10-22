#include <stdio.h>
#include <stdlib.h>

int grafoCreato = 0;

typedef struct Edge *link;
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

//Funzioni
void errore(int i);
Edge *getLast(Edge *edge);
void creaGrafo(Grafo *graph);
void definisciArco(Edge **edge, int nodo2, int peso, int *dis);
void creaArco(Grafo graph);
void creaArchi(Grafo graph);
void elTesta(link *head);
void elArcoDIS(link *head);
void eliminaListaREC(link head);
void eliminaArchiDIS(Grafo graph);
void attNodo(Grafo graph);
void disNodo(Grafo graph);
void stampaADJ(Edge *head);
void stampaGrafo(Grafo graph);
void stampaGrafoRIC(Grafo graph);
void sceltaMenuGrafo(Grafo *graph, int val);
void menuGrafo(Grafo *graph);


void errore(int i){
    if (i == 1) printf("Errore di Allocazione. \n");
    if (i == 2) printf("Errore, nodo non fa parte del grafo\n");
    if (i == 3) printf("Errore generico\n");
    exit(1);
}

Edge *getLast(Edge *edge){
    if(edge == NULL) return NULL;
    if(edge->next == NULL) return edge;
    else return getLast(edge->next);
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

void elTesta(link *head){
    link tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void elArcoDIS(link *head) {
    if(!head || !*head) return;
    if (*(*head)->dis == 1) {
        elTesta(head);
        elArcoDIS(head);
    }
    else elArcoDIS(&(*head)->next);
}

void eliminaListaREC(link head){
    if (head == NULL) return;
    eliminaListaREC(head->next);
    free(head);
    head = NULL;
}

void eliminaArchiDIS(Grafo graph){
    for(int i = 0; i < graph.dim; i++){
        if (graph.arr[i].dis == 1) eliminaListaREC(graph.arr[i].adj);
        else elArcoDIS(&graph.arr[i].adj);
    }
}

void attNodo(Grafo graph){
    int i;
    printf("Nodo da attivare: ");
    scanf("%d", &i);
    graph.arr[i].dis = 0;
}

void disNodo(Grafo graph){
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

void stampaGrafoRIC(Grafo graph){
    if(graph.dim == 0) return;
    graph.dim --;
    stampaGrafoRIC(graph);
    if (graph.arr[graph.dim].dis != 1){
        printf("%d: ", graph.dim);
        stampaADJ(graph.arr[graph.dim].adj);
    }
}

int eSottografo(Grafo G, Grafo G_prime) {
    // Controllo preliminare sulla dimensione dei grafi
    if (G_prime.dim > G.dim) {
        return 0; // Falso
    }

    for (int i = 0; i < G_prime.dim; i++) {
        Nodo nodo_prime = G_prime.arr[i];
        
        if (nodo_prime.dis == 1) continue; // Ignora nodi disabilitati

        // Trova il nodo corrispondente in G
        if (i >= G.dim || G.arr[i].dis == 1) {
            return 0; // Nodo non esistente o disabilitato in G
        }

        Nodo nodo = G.arr[i];

        // Verifica gli archi per ogni nodo
        for (Edge *e_prime = nodo_prime.adj; e_prime != NULL; e_prime = e_prime->next) {
            int trovato = 0;
            for (Edge *e = nodo.adj; e != NULL; e = e->next) {
                if (e_prime->label == e->label && e_prime->peso == e->peso) {
                    trovato = 1;
                    break;
                }
            }
            if (!trovato) {
                return 0; // Arco non trovato
            }
        }
    }

    return 1; // Vero, G' è un sottografo di G
}


void sceltaMenuGrafo(Grafo *graph, int val) {
    switch(val) {
        case 1:
            if (!grafoCreato) {
                creaGrafo(graph);
                printf("Grafo creato con successo.\n");
                grafoCreato = 1;
            } else {
                printf("Grafo già creato.\n");
            }
            break;
        case 2:
            creaArchi(*graph);
            printf("Archi inseriti con successo.\n");
            break;
        case 3:
            disNodo(*graph);
            printf("Nodo disabilitato.\n");
            break;
        case 4:
            attNodo(*graph);
            printf("Nodo attivato.\n");
            break;
        case 5:
            printf("Archi eliminati.\n");
            eliminaArchiDIS(*graph);
            break;
        case 6:
            stampaGrafo(*graph);
            break;
        case 7:
            stampaGrafoRIC(*graph);
            break;
        case 8:
            //eliminaGrafo(graph);
            grafoCreato = 0;
            printf("Grafo eliminato.\n");
            break;
        case 0:
            printf("Uscita dal programma.\n");
            exit(0);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
}

void menuGrafo(Grafo *graph) {
    int val;

    printf("\n-- Menù delle operazioni sul Grafo --\n");

    if (!grafoCreato) {
        printf("1. Crea un grafo\n");
    }
    printf("2. Inserisci archi nel grafo\n");
    printf("3. Disabilita un nodo\n");
    printf("4. Attiva un nodo\n");
    printf("5. Elimina archi non attivi\n");
    printf("6. Stampa il grafo\n");
    printf("7. Stampa il grafo (versione ricorsiva)\n");
    printf("8. Elimina il grafo\n");
    printf("0. Esci\n");

    printf("-------------------------------\n");
    printf("Scelta: ");
    scanf("%d", &val);

    sceltaMenuGrafo(graph, val);
}


int main(){
    Grafo graph;

    while(1) menuGrafo(&graph);
}