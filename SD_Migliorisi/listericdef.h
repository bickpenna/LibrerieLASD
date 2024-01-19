#ifndef LISTERIC_H_
#define LISTERIC_H_

struct el
{
    int info;
    struct el *next;
};
typedef struct el lista;


lista *newElem(int info);
lista *insertCoda(lista *head, int info);
lista *insertOrdLista(lista *head, int info);
void stampaLista(lista *head);
int lunghezzaLista(lista *head);
void deallocaLista(lista *head);
void stampaListaInversoStatic(lista *head);
void stampaListaInverso2(lista *head, int depth);
void stampaInverso(lista *head);
void stampaListaPostoDispari2(lista *head, int posto);
void stampaListaPostoDispari(lista *head);
lista *minimoElemento(lista *head);
lista *primoElementoPari(lista *head);
lista *minimoPariLista(lista *head);
lista *eliminatotElem(lista *head, int x);
lista *eliminaMinoriDi(lista *head, int y);
lista *ordinaLista(lista *head);
lista *spostaInTesta(lista *head,lista *minNodo);
lista *eliminaPunt(lista *head, lista *nodo);
lista *eliminaPunt_iter(lista *head, lista *nodo);




#endif // LISTERIC_H_
