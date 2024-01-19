/*
Si consideri uno Stack S, implementato con array S[MAX+1]. Si implementi la funzione ricorsiva
void togli_da_Stack(int S[], int el)
che elimini dallo stack S tutti gli elementi uguali ad el lasciando 
invariato l ordine degli altri elementi. 
Non utilizzare altre strutture dati di appoggio.
Non utilizzate accessi diretti all array, ma servitevi solo delle 
funzioni implementate per la gestione degli stack. 
Si ricordi che lo stack è una struttura dati che permette l accesso 
ai suoi dati solo dal top
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int empty_stack(int S[])
{
    return S[0]==0;
}

int full_stack(int S[])
{
    return S[0]==MAX;
}

void push(int S[], int valore)
{
    S[0]=S[0]+1;
    S[S[0]]=valore;
}

int pop(int S[])
{
    S[0]=S[0]-1;
    return S[S[0]+1];
}

void stampa_stack(int S[])
{
    if(empty_stack(S))
    {
        printf("FINE PILA\n");
    }
    else
    {
        int valore=pop(S);
        printf("%d|", valore);
        stampa_stack(S);
        push(S,valore);
    }
}

void inizializza_stack(int S[])
{
    S[0]=0;
}

void new_stack(int S[])
{
	int num_elementi;
	int valore;

	inizializza_stack(S);
	int i=1;

	printf("Quanti elementi (max %d elementi): " ,MAX);
	scanf("%d", &num_elementi);

	while(num_elementi>MAX)
	{
		printf("\n MAX %d elementi : ", MAX);
		scanf("%d", &num_elementi);
	}

	while(num_elementi>0)
 	{
		printf(" inserire un valore : ", i++);
		scanf("%d", &valore);
		push(S,valore);
		--num_elementi;
	}
}

void togli_da_stack(int S[], int el)
{
    if(empty_stack(S))
    {
        return;
    }

    int valore=pop(S);

    if(valore!=el)
    {
        togli_da_stack(S,el);
        push(S,valore);
    }
}

int main()
{
    int S[MAX+1];

    new_stack(S);

    printf("PILA ORIGINALE: \n");
    stampa_stack(S);

    int elemento=5;

    togli_da_stack(S,elemento);

    printf("PILA MODIFICATA: \n");
    stampa_stack(S);
}