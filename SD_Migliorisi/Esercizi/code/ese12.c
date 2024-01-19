/*
Data una coda statica di elementi positivi, caricata da tasteria, scrivere una funzione che rimuove 
dalla coda tutte le occorrenze del numero due. La funzione deve restituire la coda modificata e il minimo della
coda
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int empty_queue(int Q[])
{
    return Q[0]==0;
}

int full_queue(int Q[])
{
    return Q[0]==Q[MAX+1];
}

void enqueue(int Q[], int valore)
{
    Q[Q[MAX+1]]=valore;

    if(Q[0]==0)
    {
        Q[0]=1;
    }

    Q[MAX+1]=(Q[MAX+1]%MAX)+1;
}

int dequeue(int Q[])
{
    int valore=Q[Q[0]];

    Q[0]=(Q[0]%MAX)+1;

    if(Q[0]==Q[MAX+1])
    {
        Q[0]=0;
        Q[MAX+1]=1;
    }

    return valore;
}

void reverse(int Q[])
{
    if(empty_queue(Q))
    {
        return ;
    }
    else
    {
        int valore=dequeue(Q);
        reverse(Q);
        enqueue(Q,valore);
    }
}

void stampa_queue(int Q[])
{
    int valore;

    if(empty_queue(Q))
    {
        printf("FINE CODA\n");
    }
    else
    {
        valore=dequeue(Q);
        printf("%d ", valore);
        stampa_queue(Q);
        enqueue(Q,valore);
    }
}

void inizializza_coda(int Q[])
{
    Q[0]=0;
    Q[MAX+1]=1;
}

void new_queue(int Q[])
{
    int num_elementi;
    int valore;

    inizializza_coda(Q);

    printf("Quanti elementi vuoi insierire (MAX %d elementi): ", MAX);
    scanf("%d", &num_elementi);

    while(num_elementi > MAX)
    {
        printf("\n max %d elementi: ", MAX);
        scanf("%d", &num_elementi);
    }

    while(num_elementi>0)
    {
        printf("Insersci un valore: ");
        scanf("%d", &valore);
        enqueue(Q,valore);
        num_elementi--;
    }
}

void rimuovi_occ2(int Q[])
{
    int temp[MAX+1];
    inizializza_coda(temp);

    int valore;

    while(!empty_queue(Q))
    {
        valore=dequeue(Q);

        if(valore!=2)
        {
            enqueue(temp, valore);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}

int ricerca_minimo(int Q[])
{
    int min=Q[Q[0]];

    if(empty_queue(Q))
    {
        return 0;
    }

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);

        if(valore < min)
        {
            min=valore;
        }
    }

    return min;
}

int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("STAMPO CODA INIZIALE: \n");
    stampa_queue(Q);

    printf("\n");

    rimuovi_occ2(Q);

    printf("CODA MODIFICATA: \n");
    reverse(Q);
    stampa_queue(Q);

    printf("\n");
    int minimo_coda=ricerca_minimo(Q);

    printf("IL MINIMO DELLA CODA è %d\n", minimo_coda);
}