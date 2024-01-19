/*
Si considerino una coda Q, implementati con array Q[MAX+2], come vista a lezione.
Si implementi la funzione ricorsiva void rimuovi(int Q[]) che presa la coda rimuova gli
elementi dispari in posizione dispari e gli elementi pari se sono in posizioni pari e
maggiori dell'elemento che segue nella coda (prima della rimozione). Attenzione, l'ordine
degli elementi nella coda deve risultare invariato, non si devono usare strutture dati di
appoggio e la funzione principale non ha altri parametri oltre la coda. Si ricorda che la
coda è una struttura dati che permette l’accesso ai suoi dati solo dalla testa. Scrivere tutte
le funzioni utilizzate.
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
        printf("%d->", valore);
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

void rimuovi_ricorsivo(int Q[], int pos)
{
    if(empty_queue(Q))
    {
        return;
    }

    int valore=dequeue(Q);
    rimuovi_ricorsivo(Q,pos+1);

    int valore_successivo;

    if(empty_queue(Q))
    {
        valore_successivo=0;
    }
    else
    {
        valore_successivo=Q[Q[0]];
    }

    if(!((pos%2==0 && valore%2==0 && valore > valore_successivo) || (pos%2!=0 && valore%2!=0)))
    {
        enqueue(Q,valore);
    }
}

void rimuovi(int Q[])
{
    rimuovi_ricorsivo(Q,1);
}

int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("CODA ORIGINALE: \n");
    stampa_coda(Q);

    rimuovi(Q);

    printf("CODA MODIFICATA: \n");
    reverse(Q);
    stampa_coda(Q);
}