/*
Si considerino due stack Pari e Dispari, implementatati con array, riempiti con interi.
Si implementi la funzione ricorsiva void gioca che, utilizzando una libreria di funzioni
proceda a turni nel modo seguente. Ad ogni turno calcola la somma di Pari+Dispari se la
somma è pari si toglie da Pari il numero minimo, altrimenti si toglie da Dispari. Il gioco
finisce quando uno degli stack diventa vuoto. Si ricordi che la coda è una struttura dati
che permette l’accesso ai suoi dati solo dalla testa. Si implementi una funzione che
permetta di stampare ogni round.
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

int stack_size(int S[])
{
    int size=S[0];
    return size;
}

int elemento_minimo(int S[])
{
    if(empty_stack(S))
    {
        printf("Lo stack è vuoto\n");
        return -1;
    }

    int minimo=S[1];

    for(int i=2; i<=stack_size(S);i++)
    {
        if(S[i]<minimo)
        {
            minimo=S[i];
        }
    }
    return minimo;
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
        S[size - 1] = 0;
        S[0] = S[0] - 1;
    }
}

void rimuovi_minimo(int S[]) 
{
    int size = stack_size(S);
    int min_index = 0;

    for (int i = 1; i < size; i++)
    {
        if (S[i] < S[min_index]) 
        {
            min_index = i;
        }
    }

    rimuovi_elemento(S, min_index);
}

int somma_stack(int S[])
{
    int somma=0;
    int size=stack_size(S);

    for(int i=0; i<=size; i++)
    {
        somma+=S[i];
    }
    return somma;
}

void gioco_ric(int pari[], int dispari[])
{
    if(empty_stack(pari) || empty_stack(dispari))
    {
        return;
    }

    int somma=somma_stack(pari)+somma_stack(dispari);

    if(somma%2==0)
    {
        rimuovi_minimo(pari);
    }
    else
    {
        rimuovi_minimo(dispari);
    }
}

void gioco(int pari[], int dispari[])
{
    gioco_ric(pari,dispari);
}

int main()
{
    int pari[MAX+1];
    int dispari[MAX+1];

    new_stack(pari);
    new_stack(dispari);

    printf("PILA PARI: \n");
    stampa_stack(pari);

    int minimo_p=elemento_minimo(pari);

    printf("L'elemento minimo di Pari è %d\n",minimo_p);

    int somma_p=somma_stack(pari);

    printf("La somma degli elementi dello stack Pari è %d\n", somma_p);

    stampa_stack(dispari);

    int minimo_d=elemento_minimo(dispari);

    printf("L'elemento minimo di Disapri è %d\n",minimo_d);

    int somma_d=somma_stack(dispari);

    printf("La somma degli elementi dello stack Dispari è %d\n", somma_d);

    gioco(pari,dispari);

    printf("Stack pari e dispari dopo il gioco: \n");
    stampa_stack(pari);
    printf("\n");
    stampa_stack(dispari);
}