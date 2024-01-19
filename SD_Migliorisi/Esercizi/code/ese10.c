/*
Si consideri una Coda Q, implementato con array Q[MAX]. Si implementi la
funzione ricorsiva void togliPositiviNegativi(int Q[MAX]) che elimina dalla
coda, a seconda della scelta, i numeri positivi o negativi. L’ordine della coda
deve essere invariato.
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
        printf("%d| ",valore);
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

void togli_positivi_negativi(int Q[])
{
    int tmp[MAX+1];

    inizializza_queue(tmp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);

        if(valore<0)
        {
            enqueue(tmp,valore);
        }
    }

    while(!empty_queue(tmp))
    {
        int val_temp=dequeue(tmp);
        enqueue(Q,val_temp);
    }
}

int main()
{
    int Q[MAX+1];

    new_queue(Q);

    printf("STAMPO CODA ORIGINALE: \n");
    stampa_queue(Q);

    printf("\n");

    printf("EFFETTUO OPERAZIONE E STAMPO LA CODA MODIFICATA: \n");

    togli_positivi_negativi(Q);

    stampa_queue(Q);
}