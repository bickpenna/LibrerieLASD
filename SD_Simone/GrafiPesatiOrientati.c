#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int label;
    int weight;
    int disabled; // Se è uguale a 1, è disabilitato
    struct Edge* next;
} Edge;

typedef struct Graph {
    int nvert;
    struct Edge** adj_list;
} Graph;

int isEmpty(Graph *g);
Edge* newEdge(int label, int weight);
Edge** initAdjList(Graph* g);
void newGraph(Graph** g);
void printGraph(Graph* g);
Edge* getLast(Edge* head);
void addEdge(Graph** g);
void addVert(Graph** g);
void removeEdge(Graph** g);
void removeVertex(Graph** g);
void deleteEdge(Edge** del);
void deleteGraph(Graph** g);
void activateVert(Graph** g);
void esercizio(Graph** g);
void help();

//Ritorna 1 se il grafo ha 0 vertici, cioè se è vuoto
int isEmpty(Graph *g){
    if(g==NULL){
        return 1;
    } else return 0;
}

Edge* newEdge(int label, int weight) {
    Edge* new = (Edge*)malloc(sizeof(Edge));
    new->label = label;
    new->weight = weight;
    new->disabled = 0;
    new->next = NULL;
    return new;
}

Edge** initAdjList(Graph* g) {
    g->adj_list = (Edge**)malloc(g->nvert * sizeof(Edge*));
    for (int i = 0; i < g->nvert; i++) {
        g->adj_list[i] = newEdge(i, 0);
    }
    return g->adj_list;
}

void newGraph(Graph** g) {
    if (!isEmpty(*g)) {
        int s = -1;
        printf("Esiste già un grafo allocato con [%d] vertici, sei sicuro di volerne allocare uno nuovo?\n [0] No, [1] Sì\n", (*g)->nvert);
        scanf("%d", &s);
        if (s == 0) return;
    }
    *g = (Graph*)malloc(sizeof(Graph));
    printf("Inserisci il numero di vertici: ");
    scanf("%d", &(*g)->nvert);
    (*g)->adj_list = initAdjList(*g);
}

void printGraph(Graph* g) {
    if (isEmpty(g)) {
        printf("Il grafo è vuoto.\n");
        return;
    } else {
        Edge* temp = NULL;
        printf("Il grafo ha [%d] vertici.\n", g->nvert);
        for (int i = 0; i < g->nvert; i++) {
            temp = g->adj_list[i];
            if (g->adj_list[i]->disabled != 1) {
                while (temp) {
                    if (!temp->disabled) {
                        if (temp->label == i) {
                            printf("%d ", temp->label);
                        } else {
                            printf("--[%d]--> %d ", temp->weight, temp->label);
                        }
                    }
                    temp = temp->next;
                }
                printf("---> NULL\n");
            }
        }
    }
}

Edge* getLast(Edge* head) {
    if (head->next == NULL) {
        return head;
    } else {
        return getLast(head->next);
    }
}

void addEdge(Graph** g) {
    int source = -1, dest = -1, weight = 0;
    if (isEmpty(*g)) {
        printf("Devi prima creare un grafo.\n");
        newGraph(g);
    }
    printf("Inserisci il vertice da cui esce l'arco (da [0] a [%d]):\n", (*g)->nvert - 1);
    scanf("%d", &source);
    while (source >= (*g)->nvert || source < 0) {
        printf("Inserisci il vertice da cui esce l'arco (da [0] a [%d]):\n", (*g)->nvert - 1);
        scanf("%d", &source);
    }
    printf("Inserisci il vertice in cui entra l'arco (da [0] a [%d] e diverso da se stesso [%d]):\n", (*g)->nvert - 1, source);
    scanf("%d", &dest);
    while (dest >= (*g)->nvert || dest < 0 || source == dest) {
        printf("Inserisci il vertice in cui entra l'arco (da [0] a [%d] e diverso da se stesso [%d]):\n", (*g)->nvert - 1, source);
        scanf("%d", &dest);
    }
    printf("Inserisci il peso dell'arco (maggiore o uguale a 0):\n");
    scanf("%d", &weight);
    while (weight < 0) {
        printf("Inserisci il peso dell'arco (maggiore o uguale a 0):\n");
        scanf("%d", &weight);
    }
    if ((*g)->adj_list[source] == NULL) {
        (*g)->adj_list[source] = newEdge(dest, weight);
    } else {
        getLast((*g)->adj_list[source])->next = newEdge(dest, weight);
    }
    printf("Arco da [%d] a [%d] con peso {%d} creato correttamente.\n", source, dest, weight);
}

void addVert(Graph** g) {
    if (isEmpty(*g)) {
        printf("Il grafo è vuoto, creane uno ora.\n");
        newGraph(g);
    } else {
        printf("Il grafo passerà da [%d] a [%d] vertici.\n", (*g)->nvert, (*g)->nvert + 1);
        (*g)->nvert++;
        (*g)->adj_list = realloc((*g)->adj_list, (*g)->nvert * sizeof(Edge*));
        (*g)->adj_list[(*g)->nvert - 1] = NULL;
    }
}

void removeEdge(Graph** g) {
    if (isEmpty(*g)) {
        printf("Il grafo è vuoto.\n");
    } else {
        int caso = -1;
        int source = 0, dest = 0;
        while (caso != 0) {
            printf("Inserisci il vertice da cui esce l'arco:\n");
            scanf("%d", &source);
            printf("Inserisci il vertice in cui entra l'arco:\n");
            scanf("%d", &dest);
            if (source >= 0 && source < (*g)->nvert && dest >= 0 && dest < (*g)->nvert) {
                caso = 0;
            } else {
                printf("Errore, i vertici devono avere valori compresi tra 0 e %d.\n", (*g)->nvert - 1);
            }
        }
        if ((*g)->adj_list[source] == NULL) {
            printf("Errore, il vertice di partenza non ha archi uscenti.\n");
        } else {
            Edge* temp = (*g)->adj_list[source];
            while (temp != NULL && temp->label != dest) {
                temp = temp->next;
            }
            if (temp == NULL) {
                printf("Errore, arco non trovato.\n");
            } else {
                temp->disabled = 1;
            }
        }
    }
}

void removeVertex(Graph** g) {
    if (isEmpty(*g)) {
        printf("Il grafo non ha vertici.\n");
        return;
    } else {
        int check = 0, label = 0;
        while (check == 0) {
            printf("Il vertice con label più grande è: %d\n", (*g)->nvert - 1);
            printf("Inserisci un vertice da rimuovere (disabilitare):\n");
            scanf("%d", &label);
            if (label >= 0 && label < (*g)->nvert) {
                check++;
            }
        }
        Edge* temp = NULL;
        if (!(*g)->adj_list[label]) {
            (*g)->adj_list[label] = newEdge(label, 0);
            (*g)->adj_list[label]->disabled = 1;
        } else {
            (*g)->adj_list[label]->disabled = 1;
        }
        for (int i = 0; i < (*g)->nvert; i++) {
            if ((*g)->adj_list[i]) {
                temp = (*g)->adj_list[i];
                while (temp) {
                    if (temp->label == label) {
                        temp->disabled = 1;
                    }
                    temp = temp->next;
                }
            }
        }
    }
}

void deleteEdge(Edge** del) {
    (*del)->disabled = 0;
    (*del)->label = 0;
    (*del)->weight = 0;
    (*del)->next = NULL;
    free(*del);
}

void deleteGraph(Graph** g) {
    if (isEmpty((*g))) {
        printf("Il grafo non è allocato.\n");
        return;
    } else {
        Edge* temp = NULL, *del = NULL;
        for (int i = 0; i < (*g)->nvert; i++) {
            temp = (*g)->adj_list[i];
            while (temp->next != NULL) {
                del = temp;
                temp = temp->next;
                deleteEdge(&del);
            }
        }
        free((*g)->adj_list);
        (*g)->nvert = 0;
        free((*g));
        *g = NULL; // Questo perché isEmpty() non funzionerebbe bene dopo la deallocazione
    }
}

void activateVert(Graph** g) {
    if (isEmpty(*g)) {
        printf("Il grafo è vuoto.\n");
        return;
    }
    int vert = -1;
    printf("Inserisci un vertice compreso tra [0] e [%d]: ", (*g)->nvert - 1);
    scanf("%d", &vert);
    while (vert < 0 || vert >= (*g)->nvert) {
        printf("Inserisci un vertice compreso tra [0] e [%d]: ", (*g)->nvert - 1);
        scanf("%d", &vert);
    }
    if ((*g)->adj_list[vert]->disabled != 1) {
        printf("Il vertice è già attivo.\n");
    } else {
        int check = 0;
        for (int i = 0; i < (*g)->nvert; i++) {
            Edge* temp = (*g)->adj_list[i];
            while (temp) {
                if (temp->label == vert && temp->disabled == 1) {
                    temp->disabled = 0;
                    check++;
                }
                temp = temp->next;
            }
        }
        if (check > 0) {
            printf("Il vertice [%d] è stato riattivato.\n", vert);
        }
    }
}

// Rimuove tutti gli archi con peso pari e tutti i vertici con grado uscente dispari
void esercizio(Graph** g) {
    if (isEmpty(*g)) {
        printf("Grafo non allocato.\n");
    } else {
        Edge* temp = NULL;
        int uscenti = 0;
        for (int i = 0; i < (*g)->nvert; i++) {
            uscenti = 0;
            temp = (*g)->adj_list[i]->next;
            while (temp) {
                uscenti++;
                if (temp->weight % 2 == 0 && temp->weight != 0) {
                    temp->disabled = 1;
                }
                temp = temp->next;
            }
            if (uscenti % 2 != 0) {
                (*g)->adj_list[i]->disabled = 1;
            }
        }
    }
}

void help() {
    printf("Digitare [1] per creare un nuovo grafo\n");
    printf("Digitare [2] per inserire un arco\n");
    printf("Digitare [3] per inserire un nuovo vertice\n");
    printf("Digitare [4] per eliminare un arco\n");
    printf("Digitare [5] per eliminare un vertice\n");
    printf("Digitare [6] per stampare il grafo\n");
    printf("Digitare [7] per riattivare un vertice\n");
    printf("Digitare [8] per deallocare il grafo\n");
    printf("Digitare [0] per uscire\n");
}

int main() {
    Graph* g = NULL;
    int choice = -1;

    while (choice != 0) {
        help();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                newGraph(&g);
                break;
            case 2:
                addEdge(&g);
                break;
            case 3:
                addVert(&g);
                break;
            case 4:
                removeEdge(&g);
                break;
            case 5:
                removeVertex(&g);
                break;
            case 6:
                printGraph(g);
                break;
            case 7:
                activateVert(&g);
                break;
            case 8:
                deleteGraph(&g);
                break;
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    }

    return 0;
}
