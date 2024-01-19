/*
Si considerino due stack S1 e S2, implementati con array S1[MAX+1] e S2[MAX+1],
entrambi riempiti con interi. Si implementi la funzione ricorsiva void gioca (int S1[],
int S2[]) che, utilizzando una libreria di funzioni di accesso agli stack (da implementare)
prendendo in input i due stack, simuli il seguente gioco.
a. Se i due stack non hanno lo stesso numero di elementi, vince lo stack con più
elementi.
b. Se invece i due stack hanno uguale numero di elementi, partendo dalla base, si
confrontano ad ogni turno i numeri allo stesso livello. Se la loro somma è dispari, si
elimina l’elemento di S1, se, invece è pari si elimina l’elemento di S2.
Esempio: S1 iniziale |3|2|4|10| (3 bottom dello stack) – S2 iniziale |6|2|18| (6 bottom dello
stack). Vince S1. Se invece S2 è |6|2|18|4|, allora S1 finale |2|4|10|– S2 finale |6|
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

int stack_size(int S[]) 
{
    int size = S[0];
    return size;
}


void gioca_ric(int S1[], int S2[])
{

    if(empty_stack(S1) && empty_stack(S2))
    {
        return;
    }

    int sizeS1=stack_size(S1);
    int sizeS2=stack_size(S2);

    if(!empty_stack(S1) && !empty_stack(S2))
    {
        if(sizeS1 != sizeS2)
        {
            if(sizeS1 > sizeS2)
            {
                printf("Lo stack S1 è più grande e vince il gioco\n");
            }
            else
            {
                printf("Lo stack S2 è più grande e vince il gioco\n");
            }
        }
        else
        {
            int somma=0;
            int valore_s1=pop(S1);
            int valore_s2=pop(S2);

            somma=valore_s1+valore_s2;

            if(somma%2==0)
            {
                gioca_ric(S1,S2);
                push(S2,valore_s2);
            }
            else
            {
                gioca_ric(S1,S2);
                push(S1,valore_s1);
            }
        } 
    }
}

void gioca(int S1[], int S2[])
{
    gioca_ric(S1,S2);
}


int main()
{
    int S1[MAX+1];
    int S2[MAX+1];

    new_stack(S1);
    new_stack(S2);

    printf("STAMPA DELLA PRIMA PILA: \n");
    stampa_stack(S1);

    printf("\n");

    printf("STAMPA DELLA SECONDA PILA: \n");
    stampa_stack(S2);

    int tagliaS1=stack_size(S1);
    int tagliaS2=stack_size(S2);

    printf("La pila S1 misura %d\n", tagliaS1);
    printf("La pila S2 misura %d\n", tagliaS2);

    gioca(S1,S2);

    printf("CODA S1 MODIFICATA: \n");
    stampa_stack(S1);

    printf("CODA S2 MODIFICATA: \n");
    stampa_stack(S2);

    return 0;
}