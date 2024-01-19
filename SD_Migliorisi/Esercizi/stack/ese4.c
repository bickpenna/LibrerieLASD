/*
Si consideri uno Stack S, implementato con array S[MAX+1]. Si implementi la funzione
ricorsiva moltiplica che sostituisce ogni elemento di posizione i con il prodotto di tutti gli
elementi che lo precedono nello stack (dal bottom all elemento i). Si ricordi che lo stack è
una struttura dati che permette l accesso ai suoi dati solo dal top. Le funzioni di gestione
stack possono essere omesse.
Esempio: stack iniziale 4|3|1|2|5 (4 bottom dello stack) stack finale 4|12|12|24|120|
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
        printf("FINE CODA\n");
    }
    else
    {
        int valore=pop(S);
        printf("%d|", valore);
        stampa_stack(S);
        push(S,valore);
    }
}

int stack_size(int S[])
{
    int size=S[0];
    return size;
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

void moltiplica_ric(int S[], int prodotto)
{
    if(empty_stack(S))
    {
        return;
    }

    int valore=pop(S);

    moltiplica_ric(S,prodotto*valore);
    push(S,prodotto*valore);
}

void moltiplica(int S[])
{
    moltiplica_ric(S,1);
}

int main()
{
    int S[MAX+1];

    new_stack(S);

    printf("PILA ORIGINALE: \n");
    stampa_stack(S);

    moltiplica(S);

    printf("PILA MODIFICATA: \n");
    stampa_stack(S);
}