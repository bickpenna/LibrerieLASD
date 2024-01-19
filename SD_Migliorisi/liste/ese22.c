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

/* LISTA */

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

lista *insert_coda(lista *head, int info)
{
    if(empty_list(head))
    {
        head=new_elem(info);
    }
    else
    {
        head->next=insert_coda(head->next,info);
        head->next->prev=head;
    }

    return head;
}

void insert_testa(lista **head,int info)
{
    lista *nuovo_nodo=(lista *)malloc(sizeof(lista));

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
        printf
        ("Errore di allocazione\n");
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

        *head=insert_coda(*head,val);
        //*head=insertOrdLista(*head,val);
        //insert_testa(head,val);
    }
}

void elimina_elemento_lista(lista **head, int valore)
{
    if(*head==NULL)
    {
        return;
    }

    lista *tmp=*head;

    if(tmp->info==valore)
    {
        *head=tmp->next;
        
        if(tmp->next!=NULL)
        {
            tmp->next->prev=NULL;
        }

        free(tmp);
        return;
    }

    elimina_elemento_lista(&(tmp->next),valore);
}


/* ALBERO */
int vuoto(albero *radice)
{
    if(radice) return 0;
    else return 1;
}

albero *new_elemento(albero *sx, int inforadice, albero *dx)
{
    albero *tmp;

    tmp=(albero *)malloc(sizeof(albero));

    if(tmp)
    {
        tmp->sx=sx;
        tmp->inforadice=inforadice;
        tmp->dx=dx;
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

    if(vuoto(radice))
    {
        aux=(albero *)malloc(sizeof(albero));

        if(aux)
        {
            aux->sx=NULL;
            aux->inforadice=el;
            aux->dx=NULL;
            radice=aux;
        }
        else
        {
            printf("Errore di allocazione\n");
        }
    }
    else if (el < radice->inforadice)
    {
        radice->sx=inserisci(radice->sx,el);
    }
    else if (el > radice->inforadice)
    {
        radice->dx=inserisci(radice->dx,el);
    }

    return radice;
}

void visita_preordine(albero *radice)
{
    if(radice)
    {
        printf("%d ", radice->inforadice);
        visita_preordine(radice->sx);
        visita_preordine(radice->dx);
    }
}

void visita_ordine(albero *radice)
{
    if(radice)
    {
        visita_ordine(radice->sx);
        printf("%d ", radice->inforadice);
        visita_ordine(radice->dx);
    }
}

void visita_postordine(albero *radice)
{
    if(radice)
    {
        visita_postordine(radice->sx);
        visita_postordine(radice->dx);
        printf("%d ", radice->inforadice);
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
    int minimo=0;

    if(!vuoto(radice))
    {
        if(radice->sx==NULL)
        {
            minimo=radice->inforadice;
        }
        else
        {
            minimo=ricerca_minimo(radice->sx);
        }
    }

    return minimo;
}

void elimina(albero **radice, int el)
{
    albero *aux;
    aux=*radice;

    if(vuoto(*radice))
    {
        return;
    }

    if((*radice)->inforadice > el)
    {
        elimina(&((*radice)->sx), el);
    }
    else if((*radice)->inforadice < el)
    {
        elimina(&((*radice)->dx), el);
    }
    else
    {
        if(!((*radice)->sx) && (!((*radice)->dx)))
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
            elimina(&((*radice)->dx), (*radice)->inforadice);
        }
    }
}

void elimina_elemento_albero_lista(lista **head, albero **radice, int valore)
{
    elimina_elemento_lista(head,valore);
    elimina(radice, valore);
}

int main()
{
    lista *l=NULL;
    albero *abr=NULL;

    printf("CREO,INIZIALIZZO E STAMPO LA LISTA: \n");
    new_list(&l);

    stampa_lista(l);

    printf("RIMUOVO ELEMENTO LISTA : \n");

    int el_del;
    printf("Inserisci elemento che vuoi eliminare dalla lista: \n");
    scanf("%d", &el_del);

    elimina_elemento_lista(&l,el_del);

    printf("LISTA MODIFICATA: \n");
    stampa_lista(l);

    printf("\n\n");

    printf("CREO, INIZIALIZZO E STAMPO L'ALBERO: \n");
    new_albero(&abr);

    visita_ordine(abr);

    printf("RIMUOVO ELEMENTO ALBERO: \n");

    int el_del_albero;
    printf("Inserisci elemento che vuoi eliminare dall'albero: ");
    scanf("%d", &el_del_albero);
    
    elimina(&abr,el_del_albero);

    printf("ALBERO MODIFICATO: \n");
    visita_ordine(abr);

    printf("\n\n");

    int el_del_albero_lista;
    printf("INSERISCI VALORE DA ELIMINARE SIA DALL'ALBERO CHE DALLA LISTA:  \n");
    scanf("%d", &el_del_albero_lista);

    elimina_elemento_albero_lista(&l,&abr,el_del_albero_lista);

    printf("LISTA MODIFICATA: \n");
    stampa_lista(l);

    printf("\n");

    printf("ALBERO MODIFICATO: \n");
    visita_ordine(abr);
}