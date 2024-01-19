/*
Si consideri una coda Q, implementata con array Q[MAX+2], riempita con interi. Si
implementi la funzione ricorsiva void moltiplica (int Q[]) che, utilizzando una libreria di
funzioni di accesso alla coda (da implementare) prendendo in input Q, restituisce la
coda con gli elementi nello stesso ordine, sostituendo però ogni tripla di numeri
consecutivi (il resto è lasciato inalterato) con il loro prodotto, dando priorità agli
elementi più vicini alla testa. Si ricordi che la coda è una struttura dati che permette
l accesso ai suoi dati solo dalla testa.
Esempio: Coda iniziale 3|2|2|4|1|5|7|2 (3 testa della coda) coda finale 12|20|7|2|
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
        return;
    }
    else
    {
        int valore=dequeue(Q);
        printf("%d|",valore);
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

int queue_size(int Q[]) 
{
    int size = Q[MAX+1];
    return size;
}

void moltiplica(int Q[])
{
    if (empty_queue(Q))
    {
        return;
    }

    int valore1 = dequeue(Q);

    if (empty_queue(Q))
    {
        enqueue(Q, valore1);
        return;
    }

    int valore2 = dequeue(Q);

    if (empty_queue(Q))
    {
        enqueue(Q, valore2);
        enqueue(Q, valore1);
        return;
    }

    int valore3 = dequeue(Q);
    int prodotto = valore1 * valore2 * valore3;
    enqueue(Q, prodotto);

    moltiplica(Q);
}


int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("CODA ORIGINALE: \n");
    stampa_coda(Q);

    int n=queue_size(Q);
    printf("\nla lunghezza della coda è %d\n", n);

    moltiplica(Q);

    printf("CODA MODIFICATA: \n");
    stampa_coda(Q);
}