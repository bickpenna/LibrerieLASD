/*
Sia L una lista doppiamente puntata e non circolre e T un ABR. Si implementi una 
funzione che a. riempia con valori da tastiera le due strutture dati e ne stampi il contenuto.
b. Per ogni elemento della lista, si controlli se tale elemento è presente anche nell'albero e 
in tal caso eliminarlo sia dalla lista che dall'albero. c. Stampare le due strutture dati al 
termine dell'operazione precedente. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct el_lista
{
    struct el_lista *prev;
    int info;
    struct el_lista *next;
};
typedef struct el_lista lista;

struct el_albero
{
    struct el_albero *sx;
    int inforadice;
    struct el_albero *dx;
};
typedef struct el_albero albero;

/* FUNZIONI LISTA */
int empty_list(lista *head)
{
    return (head==NULL);
}

int lunghezza_lista(lista *head)
{
    if(empty_list(head))
    {
        return 0;
    }

    return 1+lunghezza_lista(head->next);
}

lista *new_elem(int info)
{
    lista *tmp;

    tmp=(lista *)malloc(sizeof(lista));

    if(tmp)
    {
        tmp->prev=NULL;
        tmp->info=info;
        tmp->next=NULL;
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return tmp;
}

lista *inserisci_coda(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_elem(info);
    }
    else
    {
        head->next=inserisci_coda(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void insert_testa(lista **head, int info)
{
    lista *nuovo_nodo;

    nuovo_nodo=(lista *)malloc(sizeof(lista));

    if(nuovo_nodo)
    {
        nuovo_nodo->prev=NULL;
        nuovo_nodo->info=info;
        nuovo_nodo->next=*head;

        if(*head!=NULL)
        {
            (*head)->prev=nuovo_nodo;
        }

        *head=nuovo_nodo;
    }
    else
    {
        printf("Errore di allocazione\n");
    }
}

void stampa_lista(lista *head)
{
    if(empty_list(head))
    {
        printf("FINE LISTA\n");
    }
    else
    {
        printf("%d<->", head->info);
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

        *head=inserisci_coda(*head,val);
        //*head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

void rimuovi(lista **head, int info)
{
    if(empty_list(*head))
    {
        return ;
    }

    if((*head)->info==info)
    {
        lista *tmp=*head;

        if((*head)->prev!=NULL)
        {
            (*head)->prev->next=(*head)->next;
        }

        if((*head)->next!=NULL)
        {
            (*head)->next->prev=(*head)->prev;
        }

        *head=(*head)->next;
        free(tmp);
        return;
    }

    rimuovi(&((*head)->next),info);
}


/* FUNZIONE PER ABR */
int is_empty(albero *radice)
{
    return (radice==NULL);
}

albero *new_elem_abr(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;

    tmp=(albero *)malloc(sizeof(albero));

    if(tmp)
    {
        tmp->dx=dx;
        tmp->inforadice=inforadice;
        tmp->sx=sx;
    }
    else
    {
        printf("Errore di allocazione\n");
    }

    return tmp;
}

albero *inserisci(albero *radice, int el)
{
    albero *aux;

    if(is_empty(radice))
    {
        aux=(albero *)malloc(sizeof(albero ));

        if(aux)
        {
            aux->dx=NULL;
            aux->inforadice=el;
            aux->sx=NULL;
            radice=aux;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }
    else if( el < radice->inforadice)
    {
        radice->sx=inserisci(radice->sx,el);
    }
    else if( el > radice->inforadice)
    {
        radice->dx=inserisci(radice->dx,el);
    }

    return radice;
}

void visita_ordine(albero *radice)
{
    if(!is_empty(radice))
    {
        visita_ordine(radice->sx);
        printf("%d ", radice->inforadice);
        visita_ordine(radice->dx);
    }
}


void new_albero(albero **radice) 
{
    int elementi;
    int val;

    printf("Quanti elementi si vogliono inserire? ");
    scanf("%d", &elementi);

    for (int i = 0; i < elementi; i++) 
    {
        printf("\nInserire elemento numero %d: ", i + 1);
        scanf("%d", &val);

        *radice=inserisci(*radice, val);
    }
}

int ricerca_minimo(albero *radice)
{
    int min=0;

    if(!is_empty(radice))
    {
        if(radice->sx==NULL)
        {
            min=radice->inforadice;
        }
        else
        {
            min=ricerca_minimo(radice->sx);
        }
    }

    return min;
}

void elimina(albero **radice, int el)
{
    albero *aux;
    aux=*radice;

    if(is_empty(*radice))
    {
        return;
    }

    if(el < (*radice)->inforadice)
    {
        elimina(&((*radice)->sx), el);
    }
    else if( el > (*radice)->inforadice)
    {
        elimina(&((*radice)->dx), el);
    }
    else
    {
        if(!((*radice)->sx && (!(*radice)->dx)))
        {
            free(*radice);
            *radice=NULL;
        }
        else if(((*radice)->sx) && (!((*radice)->dx)))
        {
            *radice=aux->sx;
        }
        else if(!((*radice)->sx) && ((*radice)->dx))
        {
            *radice=aux->dx;
        }
        else if((aux->dx==NULL) || (aux->sx==NULL))
        {
            free(aux);
            return;
        }
        else if(((*radice)->sx) && ((*radice)->dx))
        {
            (*radice)->inforadice=ricerca_minimo((*radice)->dx);
            elimina(&(*radice)->dx,(*radice)->inforadice);
        }
    }
}

void elimina_lista_albero(lista **head, albero **radice)
{
    if(empty_list(*head))
    {
        return;
    }

    lista *current=*head;

    while(current!=NULL)
    {
        int elemento_da_ricercare=current->info;

        if((*radice)->inforadice == elemento_da_ricercare)
        {
            elimina(radice,elemento_da_ricercare);
        }

        current=current->next;
    }
}

/* MAIN */
int main()
{
    lista *l=NULL;
    albero *abr=NULL;

    printf("CREO INIZIALIZZO E STAMPO LA LISTA: \n");

    new_list(&l);

    stampa_lista(l);

    printf("\n");

    printf("CREO INIZIALIZZO E STAMPO L'ALBERO: \n");

    new_albero(&abr);

    visita_ordine(abr);

    printf("\n");

    elimina_lista_albero(&l,&abr);

    printf("Lista dopo l'eliminazione:\n");
    stampa_lista(l);
    printf("Albero dopo l'eliminazione:\n");
    visita_ordine(abr);

    
}