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
        printf("FINE PILA\n");
    }
    else
    {
        int valore=pop(S);
        printf("%d|", valore);
        stampa_stack(S);
        push(S,valore);
    }
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

void togli_da_stack(int S[], int el)
{
    if(empty_stack(S))
    {
        return;
    }

    int valore=pop(S);

    if(valore!=el)
    {
        togli_da_stack(S,el);
        push(S,valore);
    }
}

int conta_pari_ric(int S[], int count)
{
    if(empty_stack(S))
    {
        return count;
    }

    int valore=pop(S);

    if(valore%2==0)
    {
        count++;
    }

    count=conta_pari_ric(S,count);
    push(S,valore);

    return count;
}

int conta_pari(int S[])
{
    return conta_pari_ric(S,0);
}

int stack_size(int S[]) 
{
    int size = S[0];
    return size;
}


void gioca_ric(int S1[], int S2[])
{

    if(empty_stack(S1) && empty_stack(S2))
    {
        return;
    }

    int sizeS1=stack_size(S1);
    int sizeS2=stack_size(S2);

    if(!empty_stack(S1) && !empty_stack(S2))
    {
        if(sizeS1 != sizeS2)
        {
            if(sizeS1 > sizeS2)
            {
                printf("Lo stack S1 è più grande e vince il gioco\n");
            }
            else
            {
                printf("Lo stack S2 è più grande e vince il gioco\n");
            }
        }
        else
        {
            int somma=0;
            int valore_s1=pop(S1);
            int valore_s2=pop(S2);

            somma=valore_s1+valore_s2;

            if(somma%2==0)
            {
                gioca_ric(S1,S2);
                push(S2,valore_s2);
            }
            else
            {
                gioca_ric(S1,S2);
                push(S1,valore_s1);
            }
        } 
    }
}

void gioca(int S1[], int S2[])
{
    gioca_ric(S1,S2);
}

void moltiplica_ric(int S[], int prodotto)
{
    if(empty_stack(S))
    {
        return;
    }

    int valore=pop(S);

    moltiplica_ric(S,prodotto*valore);
    push(S,prodotto*valore);
}

void moltiplica(int S[])
{
    moltiplica_ric(S,1);
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

int somma_elementi(int S[], int i)
{
    int somma=0;
    for(int j=0; j<=i; j++)
    {
        somma+=S[j];
    }
    return somma;
}

void gioco_ric(int S1[], int S2[], int i)
{
    int sizeS1=stack_size(S1);
    int sizeS2=stack_size(S2);

    if(sizeS1 != sizeS2)
    {
        return;
    }

    int somma_S1=somma_elementi(S1,i);
    int somma_S2=somma_elementi(S2,i);

    if(somma_S1<somma_S2)
    {
        rimuovi_elemento(S1,i);
    }
    else if(somma_S1>somma_S2)
    {
        rimuovi_elemento(S2,i);
    }

    gioco_ric(S1,S2,i+1);
}

void gioco(int S1[], int S2[])
{
    gioco_ric(S1,S2,0);
}

int elemento_minimo(int S[])
{
    if(empty_stack(S))
    {
        printf("Lo stack è vuoto\n");
        return -1;
    }

    int minimo=S[1];

    for(int i=2; i<=stack_size(S);i++)
    {
        if(S[i]<minimo)
        {
            minimo=S[i];
        }
    }
    return minimo;
}

void gioco_ric(int pari[], int dispari[])
{
    if(empty_stack(pari) || empty_stack(dispari))
    {
        return;
    }

    int somma=somma_stack(pari)+somma_stack(dispari);

    if(somma%2==0)
    {
        rimuovi_minimo(pari);
    }
    else
    {
        rimuovi_minimo(dispari);
    }
}

void gioco(int pari[], int dispari[])
{
    gioco_ric(pari,dispari);
}


