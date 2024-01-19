#define MAX 10

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
    int valore;

    if(empty_queue(Q))
    {
        printf("FINE CODA");
    }
    else
    {
        valore=dequeue(Q);
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

void togli_positivi_negativi(int Q[])
{
    int temp[MAX+1];
    inizializza_queue(temp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);
        if(valore<0)
        {
            enqueue(temp,valore);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}

void raddoppia_dispari(int Q[])
{
    int temp[MAX+2];
    inizializza_queue(temp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);

        if(valore%2!=0)
        {
            valore*=2;
        }
        enqueue(temp,valore);
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
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

void elimina_dispari(int Q[])
{
    int temp[MAX+1];
    inizializza_queue(temp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);
        if(valore%2==0)
        {
            enqueue(temp,valore);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}

void raddoppiacoda(int Q[])
{
    int temp[MAX+2];
    inizializza_queue(temp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);
        enqueue(temp,valore);

        if(valore%2!=0)
        {
            enqueue(temp,valore);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}

void elimina_disapri(int Q[])
{
    int temp[MAX+1];
    inizializza_queue(temp);

    while(!empty_queue(Q))
    {
        int valore=dequeue(Q);

        if(valore%2==0)
        {
            enqueue(temp,valore);
        }
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
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

void raddoppia_dispari(int Q[])
{
    int temp[MAX+1];
    inizializza_queue(temp);

    int valore;

    while(!empty_queue(Q))
    {
        valore=dequeue(Q);
        
        if(valore%2!=0)
        {
            valore*=2;
        }
        enqueue(temp,valore);
    }

    while(!empty_queue(temp))
    {
        int val_temp=dequeue(temp);
        enqueue(Q,val_temp);
    }
}