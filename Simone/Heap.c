#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[i] < arr[l])
        largest = l;

    if (r < n && arr[largest] < arr[r])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
    printf("--HEAP SORT--\n");
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void buildHeap(int arr[], int n) {
    printf("------ BUILD HEAP ------\n");
    for (int i = n / 2; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int main() {
    int prova[10] = {42, 37, 3, 7, 20, 40, 20, 25, 18, 1};
    printf("Array iniziale: ");
    printArray(prova, 10);

    buildHeap(prova, 10);

    printf("Heap costruito: ");
    printArray(prova, 10);

    heapSort(prova, 10);

    printf("Array ordinato: ");
    printArray(prova, 10);
}

