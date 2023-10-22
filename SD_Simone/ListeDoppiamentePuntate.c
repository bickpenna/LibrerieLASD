#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* prev;
    int val;
    struct Node* next;
} Node;

Node* newNode();
void newList(Node** head);
Node* getLast(Node* head);
void insNode(Node** head);
void insAtIndex(Node** head, Node* new, int i);
void* insHead(Node** head, Node* new);
void insTail(Node* head, Node* new);
Node* removeHead(Node* head);
void removeTail(Node* head);

void printList(Node* head);
void reversePrintList(Node* tail);
void freeNode(Node* node);
void freeList(Node* head);
void help();

void main() {
    int scelta = -1;
    Node* head = NULL;
    while (scelta != 0) {
        help();
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                newList(&head);
                break;
            case 2:
                insNode(&head);
                break;
            case 3:
                head = removeHead(head);
                break;
            case 4:
                removeTail(head);
                break;
            case 5:
                printList(head);
                break;
            case 6:
                reversePrintList(getLast(head));
                break;
            case 7:
                freeList(head);
                break;
            case 0:
                if (head != NULL) {
                    freeList(head);
                }
                printf("Uscita\n");
                break;
            default:
                break;
        }
    }
}

Node* newNode() {
    Node* new = (Node*)malloc(sizeof(Node*));
    new->next = NULL;
    new->prev = NULL;
    printf("Inserire il valore del nodo: ");
    scanf("%d", &new->val);
    return new;
}

void newList(Node** head) {
    int n = 0;
    printf("Inserire il numero di elementi della lista: ");
    scanf("%d", &n);
    while (n < 1) {
        printf("Inserire il numero di elementi della lista [minimo 1]: ");
        scanf("%d", &n);
    }
    for (int i = 0; i < n; i++) {
        if (*head == NULL) {
            *head = newNode();
        } else {
            Node* tmp = newNode();
            tmp->prev = getLast(*head);
            tmp->prev->next = tmp;
        }
    }
}

Node* getLast(Node* head) {
        if (head->next == NULL) {
        return head;
    } else {
        return getLast(head->next);
    }
}

void insNode(Node** head) {
    int scelta = -1;
    while (scelta < 1 || scelta > 3) {
        printf("Digitare [1] per inserire un nodo in testa: \n");
        printf("Digitare [2] per inserire un nodo a un determinato indice: \n");
        printf("Digitare [3] per inserire un nodo in coda: \n");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                printf("Il nodo verra' inserito in testa\n");
                insHead(head, newNode());
                break;
            case 2:
                int i = 0;
                printf("Digitare l'indice a cui si desidera inserire il nodo: ");
                scanf("%d", &i);
                if (i == 0) {
                    insHead(head, newNode());
                } else {
                    insAtIndex(head, newNode(), i - 1);
                }
                break;
            case 3:
                printf("Il nodo verra' inserito in coda\n");
                insTail(*head, newNode());
                break;
        }
    }
}

void insAtIndex(Node** head, Node* new, int i) {
    if (i == 0) {
        (*head)->next->prev = new;
        new->next = (*head)->next;
        (*head)->next = new;
        new->prev = (*head);
    } else if ((*head)->next == NULL) {
        insTail(*head, new);
    } else {
        insAtIndex(&(*head)->next, new, i - 1);
    }
}

void* insHead(Node** head, Node* new) {
    (*head)->prev = new;
    new->next = *head;
    (*head) = new;
    printf("Nodo %d inserito in testa\n", new->val);
    return new;
}

void insTail(Node* head, Node* new) {
    Node* tail = getLast(head);
    tail->next = new;
    new->prev = tail;
    printf("Nodo %d inserito in coda\n", new->val);
}

Node* removeHead(Node* head) {
    Node* temp = head;
    head = head->next;
    head->prev=NULL;
    printf("Rimozione head [Nodo %d]\n", temp->val);
    freeNode(temp);
    return head;
}

void removeTail(Node* head) {
    Node* temp = getLast(head);
    temp->prev->next = NULL;
    printf("Rimozione tail [Nodo %d]\n", temp->val);
    freeNode(temp);
}

void printList(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    } else {
        printf("%d --> ", head->val);
        printList(head->next);
    }
}

void reversePrintList(Node* tail) {
    if (tail == NULL) {
        printf("NULL\n");
        return;
    } else {
        printf("%d --> ", tail->val);
        reversePrintList(tail->prev);
    }
}

void freeNode(Node* node) {
    node->next = NULL;
    node->prev = NULL;
    node->val = 0;
    free(node);
}

void freeList(Node* head) {
    if (head->next == NULL) {
        head->next = NULL;
        head->prev = NULL;
        head->val = 0;
        free(head);
        head = NULL;
        return;
    } else {
        freeList(head->next);
        head->next = NULL;
        head->prev = NULL;
        head->val = 0;
        free(head);
        head = NULL;
    }
}

void help() {
    printf("Digitare [1] per creare una nuova lista\n");
    printf("Digitare [2] per inserire un nodo\n");
    printf("Digitare [3] per rimuovere il nodo in testa\n");
    printf("Digitare [4] per rimuovere il nodo in coda\n");
    printf("Digitare [5] per stampare la lista\n");
    printf("Digitare [6] per stampare la lista invertita\n");
    printf("Digitare [7] per deallocare la lista\n");
    printf("Digitare [0] per uscire\n");
}
