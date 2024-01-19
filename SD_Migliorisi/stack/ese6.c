/*
Si consideri uno Stack S, implementato con array S[MAX]. Si implementi la funzione
ricorsiva void raddoppia Stack(int S[MAX]) che raddoppia le occorrenze di ogni
elemento nello stack lasciando invariato l’ordine degli elementi. Si ricorda che lo stack è
una struttura dati che permette l’accesso ai suoi dati solo dal top.
Esempio: stack iniziale 1|3|3|6|2 -- stack finale 1|1|3|3|3|3|6|6|2|2
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

void raddoppiaStackRicorsivo(int S[], int temp[]) 
{
    if (empty_stack(S))
    {
        while (!empty_stack(temp)) 
        {
            int valore = pop(temp);
            push(S, valore);
            push(S, valore);
        }
        return;
    }

    int valore = pop(S);
    push(temp, valore);
    raddoppiaStackRicorsivo(S, temp);
}

void raddoppiaStack(int S[]) 
{
    int temp[MAX];
    inizializza_stack(temp);
    raddoppiaStackRicorsivo(S, temp);
}

int main()
{
    int S[MAX+1];

    new_stack(S);

    printf("PILA ORIGINALE: \n");
    stampa_stack(S);

    raddoppiaStack(S);

    printf("PILA MODIFICATA: \n");
    stampa_stack(S);
}