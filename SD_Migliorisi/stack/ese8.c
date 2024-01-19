/*
Siano S1,S2 stack statici di interi di taglia MAX+1.
Scrivere una funzione void gioco(int S1[], int S2[]) che utilizzando solo procedure ricorsive, esegua il
seguente gioco a turni una sola volta per posizione (se gli stack hanno lo stesso numero di elementi):
per ogni turno/posizione i, si confronta la somma di tutti gli elementi dalla base fino ad i tra i due stack e si
toglie l'elemento i-esimo dallo stack la cui somma è minore (nessuno se pari). Gli stack modificati vanno
stampati alla fine del gioco e va riportato se e quale dei due stack ha più elementi.
Attenzione: Mantenere l'ordine degli elementi. Permettere il riempimento manuale.
Esempio: Per S1=3|7|3| e Q2=4|1|9|, il gioco è vinto da S2, con stack finali S1=7 e S2=4|9.
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
    int valore;

    if(empty_stack(S))
    {
        printf("FINE PILA\n");
    }
    else
    {
        valore=pop(S);
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

int somma_elementi(int S[], int i)
{
    int somma=0;
    for(int j=0; j<=i; j++)
    {
        somma+=S[j];
    }
    return somma;
}

void rimuovi_elemento(int S[], int i) 
{
    int size = stack_size(S);
    if (i < 0 || i >= size) 
    {
        printf("Indice non valido\n");
        return;
    }

    for (int j = i; j < size - 1; j++)
    {
        S[j] = S[j + 1];
    }

    S[size - 1] = 0;
    S[0] = S[0] - 1;
}

void gioco_ric(int S1[], int S2[], int i)
{
    int sizeS1=stack_size(S1);
    int sizeS2=stack_size(S2);

    if(sizeS1 != sizeS2)
    {
        return;
    }

    int somma_S1=somma_elementi(S1,i);
    int somma_S2=somma_elementi(S2,i);

    if(somma_S1<somma_S2)
    {
        rimuovi_elemento(S1,i);
    }
    else if(somma_S1>somma_S2)
    {
        rimuovi_elemento(S2,i);
    }

    gioco_ric(S1,S2,i+1);
}

void gioco(int S1[], int S2[])
{
    gioco_ric(S1,S2,0);
}

int main()
{
    int S1[MAX+1];
    int S2[MAX+1];

    new_stack(S1);
    new_stack(S2);

    printf("PRIMA PILA: \n");
    stampa_stack(S1);

    printf("SECONDA PILA: \n");
    stampa_stack(S2);

    gioco(S1,S2);

    printf("PRIMA PILA MODIFICATA: \n");
    stampa_stack(S1);
    
    printf("SECONDA PILA MODIFICATA: \n");
    stampa_stack(S2);
}