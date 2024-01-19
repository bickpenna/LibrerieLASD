/*
Scrivere una funzione in C che data una coda Q di interi, modifichi Q in modo che 
sostituisca ad ogni coppia di valori pari consecutivi, il doppio della loro somma
La funzione restituisce la coda cosi modificata
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
        return;
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
    if(empty_queue(Q))
    {
        printf("FINE CODA\n");
    }
    else
    {
        int valore=dequeue(Q);
        printf("%d |", valore);
        stampa_queue(Q);
        enqueue(Q,valore);
    }
}

void inizializza_queue(int Q[])
{
    Q[0]=0;
    Q[MAX+1]=1;
}

void new_queue(int Q[])
{
    int num_elementi;
    int valore;

    inizializza_queue(Q);

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

void modifica_queue(int Q[])
{
    if(empty_queue(Q))
    {
        return;
    }

    int prev_value=dequeue(Q);
    int curr_value;
    int new_value;
    int enqueue_prev=1;
   
    do
    {
        prev_value = dequeue(Q);

        if (empty_queue(Q))
        {
            if (enqueue_prev)
            {
                enqueue(Q, prev_value);
            }
            break;
        }

        curr_value = dequeue(Q);

        if (prev_value % 2 == 0 && curr_value % 2 == 0)
        {
            new_value = (prev_value + curr_value) * 2;
            enqueue(Q, new_value);
            enqueue_prev = 0;
        }
        else
        {
            if (enqueue_prev)
            {
                enqueue(Q, prev_value);
            }

            prev_value = curr_value;
            enqueue_prev = 1;
        }
    } while (!empty_queue(Q));

}

int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("CODA ORIGINALE\n");
    stampa_queue(Q);

    printf("\n");

    modifica_queue(Q);

    printf("CODA MODIFICATA: \n");
    reverse(Q);
    stampa_queue(Q);

    return 0;
}