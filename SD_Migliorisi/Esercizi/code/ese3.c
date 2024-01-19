/*
Si consideri una coda Q, implementata con array Q[MAX+2], riempita con interi. Si
implementi la funzione ricorsiva Somma(int Q[]) che, utilizzando una libreria di funzioni di
accesso alla coda, prendendo in input Q restituisce la coda con gli elementi nello stesso ordine,
aggiungendo però dopo ogni numero dispari nella coda (a partire dalla testa) la somma dei
dispari che lo precedono e dopo ogni numero pari la somma dei dei pari che lo precedono.
Esempio: coda iniziale 3|4|7|4|5|5 (3 in testa) – coda finale 3|3|4|4|7|10|4|8|5|15|5|20
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
    int valore;

    if(!empty_queue(Q))
    {
        valore=dequeue(Q);
        reverse(Q);
        enqueue(Q,valore);
    }
}

void stampa_coda(int Q[])
{
    if(empty_queue(Q))
    {
        printf("FINE CODA\n");
    }
    else
    {
        int valore=dequeue(Q);
        printf("%d->",valore);
        stampa_coda(Q);
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

void somma(int Q[])
{
    int temp[MAX+2];
    inizializza_queue(temp);

    int somma_pari=0;
    int somma_dispari=0;

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);

        if(valore%2==0)
        {
            somma_pari+=valore;
            enqueue(temp,somma_pari);
        }
        else
        {
            somma_dispari+=valore;
            enqueue(temp,somma_dispari);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}


int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("CODA ORIGINALE : \n");
    stampa_coda(Q);

    printf("\n\n");

    somma(Q);

    printf("CODA MODIFICATA: \n");
    reverse(Q);
    stampa_coda(Q);
}