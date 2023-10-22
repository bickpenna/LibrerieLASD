#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node
{
    int val;
    struct Node* sx;
    struct Node* dx;
} Node;

void vuoto(Node** rad);
void newABR(Node** rad);
void newNode(Node** nuovo, int value);
void v_preOrder(Node* radice);
void v_inOrder(Node* radice);
void v_postOrder(Node* radice);
void insertInABR(Node** root, int value);
void delNode(Node** root, int value);
void findMinimum(Node* root, Node** minNode);
void searchNode(Node* radice, int r, int* trovato);
void searchNode_min(Node* radice, int* min);
void freeTree(Node** root);
void printMenu();
void printTree(Node *rad);
void menu();

void vuoto(Node** rad)
{
    if (*rad)
        *rad = NULL;
}

void newABR(Node** rad)
{
    int n=0, elem=0;

    printf("Inserisci il numero di elementi: ");
    scanf("%d", &n);

    printf("Inserisci gli elementi (senza valori uguali e tutti positivi):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Inserisci il [%d] elemento:", i + 1);
        scanf("%d", &elem);
        insertInABR(rad, elem);
    }
}

void newNode(Node** nuovo, int value)
{
    *nuovo = (Node*)malloc(sizeof(Node));
    (*nuovo)->val = value;
    (*nuovo)->sx = NULL;
    (*nuovo)->dx = NULL;
}

void v_preOrder(Node* radice)
{
    if (radice)
    {
        printf("%d ", radice->val);
        v_preOrder(radice->sx);
        v_preOrder(radice->dx);
    }
}

void v_inOrder(Node* radice)
{
    if (radice)
    {
        v_inOrder(radice->sx);
        printf("%d ", radice->val);
        v_inOrder(radice->dx);
    }
}

void v_postOrder(Node* radice)
{
    if (radice)
    {
        v_postOrder(radice->sx);
        v_postOrder(radice->dx);
        printf("%d ", radice->val);
    }
}

void insertInABR(Node** root, int value)
{
    if (*root == NULL)
    {
        newNode(root, value);
        return;
    }

    if (value < (*root)->val)
        insertInABR(&(*root)->sx, value);
    else if (value > (*root)->val)
        insertInABR(&(*root)->dx, value);
}

void delNode(Node** root, int value)
{
    if (*root == NULL)
        return;

    if (value < (*root)->val)
        delNode(&(*root)->sx, value);
    else if (value > (*root)->val)
        delNode(&(*root)->dx, value);
    else
    {
        if ((*root)->sx == NULL && (*root)->dx == NULL)
        {
            free(*root);
            *root = NULL;
        }
        else if ((*root)->sx == NULL)
        {
            Node* temp = *root;
            *root = (*root)->dx;
            free(temp);
        }
        else if ((*root)->dx == NULL)
        {
            Node* temp = *root;
            *root = (*root)->sx;
            free(temp);
        }
        else
        {
            Node* minNode = NULL;
            findMinimum((*root)->dx, &minNode);
            (*root)->val = minNode->val;
            delNode(&(*root)->dx, minNode->val);
        }
    }
}

void findMinimum(Node* root, Node** minNode)
{
    if (root == NULL)
        return;

    if (root->sx != NULL)
        findMinimum(root->sx, minNode);
    else
        *minNode = root;
}

void searchNode(Node* radice, int r, int* trovato)
{
    if (radice)
    {
        if (radice->val == r)
        {
            *trovato = 1;
            return;
        }
        else if (radice->val > r)
            searchNode(radice->sx, r, trovato);
        else
            searchNode(radice->dx, r, trovato);
    }
}

void searchNode_min(Node* radice, int* min)
{
    if (radice)
    {
        if (radice->sx)
            searchNode_min(radice->sx, min);
        else
            *min = radice->val;
    }
}

void freeTree(Node** root)
{
    if (*root == NULL)
        return;

    freeTree(&(*root)->sx);
    freeTree(&(*root)->dx);

    free(*root);
    *root = NULL;
}
void printMenu(){
    printf("Digitare:\n");
    printf("[1] per la stampare in PreOrder\n");
    printf("[2] per la stampare InOrder\n");
    printf("[3] per la stampare in PostOrder\n");
}

void printTree(Node *rad){
    int scelta=-1;
    while(scelta<1 || scelta>4){
        printMenu();
        scanf("%d", &scelta);
        switch (scelta){
        case 1:
            v_preOrder(rad);
            break;
        case 2:
            v_inOrder(rad);
            break;
        case 3:
            v_postOrder(rad);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }
    }
    
}

void menu(){
        printf("Scegli tra:\n");
        printf("1. Creare un ABR di interi\n");
        printf("2. Aggiungere un nodo ad un ABR\n");
        printf("3. Cercare un valore nell'ABR\n");
        printf("4. Cercare il min nell'ABR\n");
        printf("5. Stampare l'ABR\n");
        printf("6. Eliminare un elemento nell'ABR\n");
        printf("0. Uscita\n");
        printf("----------------------\n");
}

int main()
{
    Node* root = NULL;
    int scelta=-1, value=-1;

    while (scelta!=0){
        menu();
        scanf("%d", &scelta);

        switch (scelta) {
            case 0:
                freeTree(&root);
                printf("Uscita...\n");
                exit(-1);
                break;
            case 1:
                newABR(&root);
                printf("ABR creato con successo.\n");
                break;
            case 2:
                printf("Valore da inserire: ");
                scanf("%d", &value);
                insertInABR(&root, value);
                break;
            case 3:
                printf("Valore da cercare: ");
                scanf("%d", &value);
                int trovato = 0;
                searchNode(root, value, &trovato);
                if (trovato)
                    printf("Il valore è presente nell'albero.\n");
                else
                    printf("Il valore non è presente nell'albero.\n");
                break;
            case 4:
                int min;
                searchNode_min(root, &min);
                printf("Il valore min presente nell'albero è: %d\n", min);
                break;
            case 5:
                printTree(root);
                printf("\n");
                break;
            case 6:
                printf("Valore da eliminare: ");
                scanf("%d", &value);
                delNode(&root, value);
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
                break;
        }
    } 

    return 0;
}