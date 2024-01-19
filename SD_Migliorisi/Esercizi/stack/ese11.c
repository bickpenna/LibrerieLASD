/*
Si considerino due Stack SI S2,2 implementati con array SIIMAXI e S2[MAXl, e
riempiti con interi da t a 9. Si i!nplementi la funzione ricorsiva void gioco, che
indipendentemente dalla implementazione della struttura dati Stack, prendendo in
input i due Stack, effettui un gi0C(.i fiel seguente modo:
Ad ogni turno del gioco si considera la somma modulo 10 dei valori al top dei due Stack
Se tale somma è minore di 5, vinee, il primo Stack, altrimenti vince il secondo. Ad ogni
iterazione, si rimuove il top dallo Stack perdente.
iiidieatxWWStackmyinçentÇ ebe ritorna come all 'inizio
del gioco, mentre quello perdente risulta vuoto, _Si ricordi che lo Stack è una struttura dati
- che permette l'accesso solo al top. Se -vere tutte le funzioni utilizzate- Non utilizzare altre
-strutture dati.
Esempio: Sia e S? isposult S? vince.:
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int is_empty(int S[])
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

    if(is_empty(S))
    {
        printf("FINE PILA\n");
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

int top(int S[])
{
    if(!is_empty(S))
    {
        return S[S[0]];
    }
}

void gioco_ric(int S1[], int S2[])
{
    if(is_empty(S1) || is_empty(S2))
    {
        if(is_empty(S1))
        {
            printf("S2 VINCITORE\n");
        }
        else if(is_empty(S2))
        {
            printf("S1 VINCITORE\n");
        }
        return ;
    }

    int size1=stack_size(S1);
    int size2=stack_size(S2);

    if(!is_empty(S1) && !is_empty(S2))
    {
        int somma=0;

        int val_S1=pop(S1);
        int val_S2=pop(S2);

        somma=val_S1+val_S2;

        if(somma%10<5)
        {
            push(S1,val_S1);
        }
        else
        {
            push(S2,val_S2);
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

    printf("CREO,INIZIALIZZO E STAMPO IL PRIMO STACK S1: \n");
    new_stack(S1);

    stampa_stack(S1);

    printf("\n");

    printf("CREO, INIZIALIZZO E STAMPO IL SECONDO STACK S2: \n");
    new_stack(S2);

    stampa_stack(S2);

    printf("\n");

    printf("GIOCO\n");

    gioco(S1,S2);

    printf("S1 E S2 ALLA FINE DEL GIOCO: \n");
    stampa_stack(S1);

    printf("\n");

    stampa_stack(S2);
}