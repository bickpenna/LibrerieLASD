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
#include <limits.h>

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
        printf("FINE STACK\n");
    }
    else
    {
        valore=pop(S);
        printf("%d ", valore);
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

int ricerca_minimo(int S[])
{
    if(empty_stack(S))
    {
        return 0;
    }

    int minimo=S[1];
    int size=stack_size(S);
    
    for(int i=2; i<=size; i++)
    {
        if(S[i] < minimo)
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

void gioco_ric(int S1[], int S2[])
{
    if(empty_stack(S1) || empty_stack(S2))
    {
        if(empty_stack(S1))
        {
            printf("VINCE IL GIOCATORE 2.\n");
        }
        else
        {
            printf("VINCE IL GIOCATORE1.\n");
        }
        return;
    }

    int S1_size=stack_size(S1);
    int S2_size=stack_size(S2);

    if(!empty_stack(S1) && !empty_stack(S2))
    {

        int minimo_s1=ricerca_minimo(S1);
        int minimo_s2=ricerca_minimo(S2);
        int somma=0;
        int valore_s1=pop(S1);
        int valore_s2=pop(S2);

        somma=valore_s1+valore_s2;

        if(somma%2==0)
        {
            rimuovi_elemento(S1,minimo_s1);   
        }
        else
        {
            rimuovi_elemento(S2,minimo_s2);
        }
    }
    gioco_ric(S1,S2);
}

void gioco(int S1[], int S2[])
{
    gioco_ric(S1,S2);
}

int main()
{
    int S1[MAX];
    int S2[MAX];

    new_stack(S1);

    printf("STAMPO LO STACK: \n");
    stampa_stack(S1);

    printf("\n");

    new_stack(S2);

    printf("STAMPO LO STACK S2: \n");
    stampa_stack(S2);

    printf("\n");
    
    gioco(S1,S2);
}