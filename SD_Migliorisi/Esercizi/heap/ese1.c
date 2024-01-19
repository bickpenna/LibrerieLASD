/* 
FUNZIONAMENTO HEAP CON HEAPIFY 
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void swap(int *a, int *b)
{
    int temp= *b;
    *b=*a;
    *a=temp;
}

void heapify(int array[], int size, int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left < size && array[left] > array[largest])
    {
        largest=left;
    }

    if(right < size && array[right] > array[largest])
    {
        largest=right;
    }

    if(largest != i)
    {
        swap(&array[i], &array[largest]);
        heapify(array,size,largest);
    }
}

void build_heap(int array[], int size)
{
    int last_non_leaf_node=size/2 - 1;

    for(int i=last_non_leaf_node; i>=0; i--)
    {
        heapify(array,size,i);
    }
}

void heap_sort(int arr[], int n)
{
    build_heap(arr,n);

    for(int i=n-1; i>0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr,i,0);
    }
}

int main() 
{
    int array[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Array prima dell'ordinamento:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    heap_sort(array, size);

    printf("Array dopo l'ordinamento:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}