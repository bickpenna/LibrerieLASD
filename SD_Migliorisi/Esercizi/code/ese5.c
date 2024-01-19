/*
implementare coda Q, implementare funzione voi moltiplica2(intQ[]), che prendendo in input Q, restituisce
la coda con gli elementi nello stesso ordine, sostituendo però ogni coppia di numeri dispari consecutivi
con il doppio del loro prodotto.
esempio-> coda INIZIALE: 3|5|7|4|5|5 ----> coda FINALE: 30|7|4|50|
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

void moltiplica2_ricorsivo(int Q[])
{
    if(empty_queue(Q))
    {
        return;
    }

    int valore=dequeue(Q);
    moltiplica2_ricorsivo(Q);

    if(!empty_queue(Q) && valore%2!=0 && Q[Q[0]]%2!=0)
    {
        int valore_successivo=dequeue(Q);
        int prodotto_doppio=2*valore*valore_successivo;
        enqueue(Q,prodotto_doppio);
    }
    else
    {
        enqueue(Q,valore);
    }
}

void moltiplica2(int Q[])
{
    moltiplica2_ricorsivo(Q);
}

int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("CODA ORIGINALE: \n");
    stampa_coda(Q);

    moltiplica2(Q);

    printf("CODA MODIFICATA: \n");
    stampa_coda(Q);
}