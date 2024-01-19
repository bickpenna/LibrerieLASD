/*
Scrivere una funzione ricorsiva che, dato uno stack di valori interi, restituisca il numero di valori pari
presenti. Stampare lo stack anche dopo la procedura
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
        printf("%d|",valore);
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

int conta_pari_ric(int S[], int count)
{
    if(empty_stack(S))
    {
        return count;
    }

    int valore=pop(S);

    if(valore%2==0)
    {
        count++;
    }

    count=conta_pari_ric(S,count);
    push(S,valore);

    return count;
}

int conta_pari(int S[])
{
    return conta_pari_ric(S,0);
}

int main()
{
    int S[MAX];

    new_stack(S);

    printf("PILA ORIGINALE\n");
    stampa_stack(S);

    int conteggio=conta_pari(S);

    printf("Il numero di elementi pari nella pila S è %d\n", conteggio);
}
