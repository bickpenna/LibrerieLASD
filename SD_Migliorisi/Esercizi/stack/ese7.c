/*
Si considerino due stack Diritto e Rovescio, implementatati con array, riempiti con
interi. Si implementi la funzione ricorsiva void check che controlli se Diritto è un
vettore inverso di Rovescio. Ripetere la stessa operazione nel caso le strutture siano code.
Si implementi una funzione che permetta di caricare in modo manuale e random i valori
nelle strutture dati e di stamparne il contenuto prima e dopo l'esecuzione
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool check_ric(int diritto[], int rovescio[])
{
    if(empty_stack(diritto) && empty_stack(rovescio))
    {
        return true;
    }

    if(empty_stack(diritto) || empty_stack(rovescio))
    {
        return false;
    }

    int val_dir=pop(diritto);
    int val_rov=pop(rovescio);

    return val_dir==val_rov && check_ric(diritto,rovescio);
}

bool check(int diritto[], int rovescio[])
{
    return check_ric(diritto,rovescio);
}

int main()
{
    int dir[MAX+1];
    int rov[MAX+1];

    new_stack(dir);
    new_stack(rov);

    printf("STAMPO PILA DIRITTO: \n");
    stampa_stack(dir);

    printf("STAMPO PILA ROVESCIO: \n");
    stampa_stack(rov);

    if(check(dir,rov))
    {
        printf("GLI STACK DIRITTO E ROVESCIO SONO GLI STESSI.\n");
    }
    else
    {
        printf("GLI STACK DIRITTO E ROVESCIO SONO DIVERSI.\n");
    }
}