struct el
{
    int info;
    struct el *next;
};
typedef struct el lista;

int empty_list(lista *head)
{
    return (head==NULL);
}

lista *new_elem(int info)
{
    lista *tmp;

    tmp=(lista *)malloc(sizeof(lista));

    if(tmp!=NULL)
    {
        tmp->info=info;
        tmp->next=NULL;
    }

    return tmp;
}

lista *insert_coda(lista *head,int info)
{
    if(head==NULL)
    {
        head=new_elem(info);
    }
    else
    {
        head->next=insert_coda(head->next,info);
    }
    return  head;
}

void stampa_lista(lista *head)
{
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d->", head->info);
        stampa_lista(head->next);
    }
}

void new_list(lista **head)
{
    int elementi;
    int val;

    printf("Quanti elementi si vogliono inserire? ");
    scanf("%d", &elementi);

    for(int i=0; i<elementi; i++)
    {
        printf("\nInserire elemento numero %d: ",i+1);
        scanf("%d", &val);

        *head=insert_coda(*head,val);
    }
}

void raddoppia_dispari(lista *head)
{
    if(empty_list(head))
    {
        return;
    }
    
    if(head->info%2!=0)
    {
        head->info=head->info*2;
    }

    raddoppia_dispari(head->next);
}

int lunghezzaLista(lista *head)
{
    if(empty_list(head))
    {
        return 0;
    }
    return 1+lunghezzaLista(head->next);
}

lista *elimina_mod10_ric(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=elimina_mod10_ric(head->next);

    if(head->info%10==0)
    {
        lista *tmp=head->next;
        free(head);
        return tmp;
    }
    else
    {
        return head;
    }
}

void elimina_mod10(lista **head_ref)
{
    *head_ref=elimina_mod10_ric(*head_ref);
}

int ricerca_elemento(lista *head, int el)
{
    if(empty_list(head))
    {
        return 0;
    }

    if(head->info==el)
    {
        return 1;
    }

    return ricerca_elemento(head->next,el);
}


lista *rimuovi_elemento(lista *head, int el)
{
    if(empty_list(head))
    {
        return head;
    }

    if(head->info==el)
    {
        lista *tmp=head->next;
        free(head);
        return tmp;
    }

    head->next=rimuovi_elemento(head->next,el);

    return head;
}

lista *insert(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_nodo(info);
    }
    else
    { 
        head->next=insert(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void insert_testa(lista **head, int info)
{
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));
    nuovo_nodo->info=info;
    nuovo_nodo->prev=NULL;
    nuovo_nodo->next=*head;

    if(*head!=NULL)
    {
        (*head)->prev=nuovo_nodo;
    }

    *head=nuovo_nodo;
}

void insert_testa(lista **head, int info)
{
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));
    
    if(nuovo_nodo)
    {
        nuovo_nodo->prev=NULL;
        nuovo_nodo->info=info;
        nuovo_nodo->next=*head;
    }
    
    if(*head!=NULL)
    {
        (*head)->prev=nuovo_nodo;
    }

    *head=nuovo_nodo;
}

lista *togli_negativi(lista *head) 
{
    if (empty_list(head)) 
    {
        return NULL;
    }

    head->next=togli_negativi(head->next);

    if (head->info < 0) 
    {
        lista *tmp = head;
        head = head->next;
        free(tmp);
    }

    return head;
}

lista *togli_positivi(lista *head)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=togli_positivi(head->next);

    if(head->info>0)
    {
        lista *tmp=head;
        head=head->next;
        free(tmp);
    }

    return head;
}

void rimuovi_negativi_e_inserisci_in_testa(lista **l1, lista **l2) 
{
    if(empty_list(*l1)) 
    {
        return;
    }

    lista *next = (*l1)->next;

    if ((*l1)->info < 0) 
    {
        insert_testa(l2, (*l1)->info); // Utilizzo della tua funzione di inserimento in testa
        *l1 = next;
        if (next != NULL) 
        {
            next->prev = NULL;
        }
    }
    else 
    {
        l1 = &((*l1)->next);
    }

    rimuovi_negativi_e_inserisci_in_testa(l1, l2);
}

void remove_negative_from_l1(lista **l1)
{
    if(empty_list(*l1))
    {
        return;
    }

    lista *next=(*l1)->next;

    if((*l1)->info <0)
    {
        *l1=next;
        if(next!=NULL)
        {
            next->prev=NULL;
        }
    }
    else
    {
        l1=&((*l1)->next);
    }

    remove_negative_from_l1(l1);
}

void remove_negative_from_l2(lista **l2)
{
    if(empty_list(*l2))
    {
        return;
    }

    lista *next=(*l2)->next;

    if((*l2)->info <0)
    {
        *l2=next;
        if(next!=NULL)
        {
            next->prev=NULL;
        }
    }
    else
    {
        l2=&((*l2)->next);
    }

    remove_negative_from_l2(l2);
}

lista *interleaving(lista *l1, lista *l2)
{
    if(empty_list(l1))
    {
        return l2;
    }

    if(empty_list(l2))
    {
        return l2;
    }

    lista *l1_next=l1->next;
    lista *l2_next=l2->next;

    l1->next=l2;
    l2->prev=l1;

    l2->next=interleaving(l1_next,l2_next);

    if(l2->next!=NULL)
    {
        l2->next->prev=l2;
    }

    return l1;
}

bool is_here(lista *head, int valore)
{
    lista *tmp=head;

    while(tmp!=NULL)
    {
        if(tmp->info==valore)
        {
            return true;
        }
        tmp=tmp->next;
    }

    return false;
}

void remove_duplicates(lista **l1)
{
    if (*l1 == NULL || (*l1)->next == NULL)
    {
        return; // La lista è vuota o ha solo un elemento, non ci sono duplicati da rimuovere
    }

    lista *current = *l1;

    while (current != NULL)
    {
        lista *next_unique = current->next;

        while (next_unique != NULL && next_unique->info == current->info)
        {
            lista *duplicate = next_unique;
            next_unique = next_unique->next;

            if (duplicate->prev != NULL) 
            {
                duplicate->prev->next = next_unique;
            }
            if (next_unique != NULL) 
            {
                next_unique->prev = duplicate->prev;
            }

            free(duplicate);
        }
        current = next_unique;
    }

    remove_duplicates(&((*l1)->next)); // Chiamata ricorsiva per il resto della lista
}

lista *rimuovi_elemento(lista *head, int num)
{
    if(empty_list(head))
    {
        return NULL;
    }

    head->next=rimuovi_elemento(head->next,num);

    if(head->info==num)
    {
        lista *tmp=head->next;
        if(tmp!=NULL)
        {
            tmp->prev=head->prev;
        }
        free(head);
        return tmp;
    }

    return head;
}

void togli_numero_ric(lista **l1, lista **l2)
{
    int size=lunghezza_lista(*l1);

    if(size==0 || lunghezza_lista(*l2)==0)
    {
        return;
    }

    *l2=rimuovi_elemento(*l2,size);

    /*lista *tmp=*l1;
    *l1=*l2;
    *l2=tmp;*/

    togli_numero_ric(l1,l2);
}

void togli_numero(lista **l1, lista **l2)
{
    togli_numero_ric(l1,l2);
}

lista *rimuovi_multipli2_l1(lista *l1,lista **l2)
{
    if(empty_list(l1))
    {
        return NULL;
    }

    l1->next=rimuovi_multipli2_l1(l1->next,l2);

    if(l1->info%2==0)
    {
        insert_testa(l2,l1->info);
        lista *tmp=l1->next;

        if(tmp!=NULL)
        {
            tmp->prev=l1->prev;
        }

        free(l1);
        return tmp;
    }
    return l1 ;
}

lista *rimuovi_multipli5_l2(lista *l2,lista **l1)
{
    if(empty_list(l2))
    {
        return NULL;
    }

    l2->next=rimuovi_multipli5_l2(l2->next,l1);

    if(l2->info%5==0)
    {
        insert_testa(l1,l2->info);
        lista *tmp=l2->next;

        if(tmp!=NULL)
        {
            tmp->prev=l2->prev;
        }

        free(l2);
        return tmp;
    }
    return l2 ;
}

lista *rimuovi_negativi_l1(lista *l1, lista **l2)
{
    if(empty_list(l1))
    {
        return NULL;
    }

    l1->next=rimuovi_negativi_l1(l1->next,l2);

    if(l1->info<0)
    {
        inserisci_testa(l2,l1->info);
        lista *tmp=l1->next;

        if(tmp!=NULL)
        {
            tmp->prev=l1->prev;
        }

        free(l1);
        return tmp;
    }

    return l1;
}

lista *rimuovi_positivi_l2(lista *l2, lista **l1)
{
    if(empty_list(l2))
    {
        return NULL;
    }

    l2->next=rimuovi_positivi_l2(l2->next,l1);

    if(l2->info>0)
    {
        inserisci_testa(l1,l2->info);
        lista *tmp=l2->next;

        if(tmp!=NULL)
        {
            tmp->prev=l2->prev;
        }

        free(l2);
        return tmp;
    }

    return l2;
}

lista *interleaving(lista *l1,lista *l2)
{
    if(empty_list(l1) || empty_list(l2))
    {
        printf("NON E' POSSIBILE INTERLEAVVING.")
        return NULL;
    }

    int size_l1=lunghezza_lista(l1);
    int size_l2=lunghezza_lista(l2);

    if(size_l1 != size_l2)
    {
        printf("NON E' POSSIBILE INTERLEAVVING.");
        return NULL;
    }

    lista *l1_next=l1->next;
    lista *l2_next=l2->next;

    l1->next=l2;
    l2->prev=l1;

    l2->next=interleaving(l1_next,l2_next);

    if(l2->next!=NULL)
    {
        l2->next->prev=l2;
    }

    return l1;
}