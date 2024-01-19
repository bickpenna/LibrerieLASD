/*
Si considerino due Stack S1 e S2, implementati con array S1[MAX] e S2[MAX], e
riempiti con interi da 1 a 9. Si implementi la funzione ricorsiva void gioco, che
indipendentemente dalla implementazione della struttura dati Stack, prendendo in
input i due Stack, effettui un gioco nel seguente modo:
Ad ogni turno del gioco si considera la somma modulo 10 dei valori al top dei due Stack.
Se tale somma è minore di 5, vince il primo Stack, altrimenti vince il secondo. Ad ogni
iterazione, si rimuove il top dallo Stack perdente. Perde lo Stack che finisce per primo i
suoi valori. La funzione termina indicando lo Stack vincente, che ritorna come all’inizio
del gioco, mentre quello perdente risulta vuoto. Si ricordi che lo Stack è una struttura dati
che permette l’accesso solo al top. Scrivere tutte le funzioni utilizzate. Non utilizzare altre
strutture dati.
Esempio: Sia S1=|4|7|9| e S2 = |2|9|. Risposta: S2 vince.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

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
        printf("FINE CODA");
    }
    else
    {
        int valore=pop(S);
        printf("%d|",valore);
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

void gioco_ric(int S1[], int S2[])
{
    if (empty_stack(S1) || empty_stack(S2)) 
    {
        if (empty_stack(S1)) 
        {
            printf("\nSONO LO STACK S2, IL VINCITORE\n");
        } else 
        {
            printf("\nSONO LO STACK S1, IL VINCITORE\n");
        }
        return;
    }

    int somma=0;
    int valore_s1=pop(S1);
    int valore_s2=pop(S2);

    somma=(valore_s1+valore_s2)%10;

    if(somma<5)
    {
        push(S1,valore_s1);
    }
    else
    {
        push(S2,valore_s2);
    }

    gioco_ric(S1,S2);
}

void gioco(int S1[],int S2[])
{
    gioco_ric(S1,S2);
}

int main()
{
    int S1[MAX+1];
    int S2[MAX+1];

    new_stack(S1);
    new_stack(S2);

    printf("PILA 1: \n");
    stampa_stack(S1);

    printf("PILA 2: \n");
    stampa_stack(S2);

    gioco(S1,S2);

    printf("\n\n");

    printf("PILA 1 DOPO GIOCO: \n");
    stampa_stack(S1);

    printf("\n\n");

    printf("PILA 2 DOPO GIOCO: \n");
    stampa_stack(S2);
}