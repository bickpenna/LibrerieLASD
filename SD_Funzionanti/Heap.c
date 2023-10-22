#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int capacity;
    int count;
} Heap;

// Function prototypes
Heap* createHeap(int initialCapacity);
void push(Heap *heap, int value);
int pop(Heap *heap);
int peek(Heap *heap);
void heapify(int arr[], int n);
void destroyHeap(Heap *heap);

// Internal utility functions
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void resize(Heap *heap) {
    int newCapacity = heap->capacity * 2;
    heap->arr = (int *)realloc(heap->arr, newCapacity * sizeof(int));
    heap->capacity = newCapacity;
}

static void percolateDown(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        percolateDown(arr, n, smallest);
    }
}

Heap* createHeap(int initialCapacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->arr = (int *)malloc(initialCapacity * sizeof(int));
    heap->capacity = initialCapacity;
    heap->count = 0;
    return heap;
}

void push(Heap *heap, int value) {
    if (heap->count == heap->capacity) {
        resize(heap);
    }
    heap->arr[heap->count++] = value;

    int childIndex = heap->count - 1;
    int parentIndex = (childIndex - 1) / 2;
    while (childIndex > 0 && heap->arr[childIndex] < heap->arr[parentIndex]) {
        swap(&heap->arr[childIndex], &heap->arr[parentIndex]);
        childIndex = parentIndex;
        parentIndex = (childIndex - 1) / 2;
    }
}

int pop(Heap *heap) {
    if (heap->count == 0) {
        printf("The heap is empty!\n");
        return -1; // Return -1 as error value, assuming negative values are invalid for the heap
    }

    int minValue = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->count];
    percolateDown(heap->arr, heap->count, 0);

    return minValue;
}

int peek(Heap *heap) {
    if (heap->count == 0) {
        printf("The heap is empty!\n");
        return -1; // Return -1 as error value, assuming negative values are invalid for the heap
    }
    return heap->arr[0];
}

void heapify(int arr[], int n) {
    int startIndex = (n / 2) - 1;
    for (int i = startIndex; i >= 0; i--) {
        percolateDown(arr, n, i);
    }
}

void destroyHeap(Heap *heap) {
    free(heap->arr);
    free(heap);
}

// Main and menu functions
void displayMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Push value into heap\n");
    printf("2. Pop value from heap\n");
    printf("3. Peek at top of heap\n");
    printf("4. Heapify array\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main() {
    Heap *heap = createHeap(10);
    int choice, value;
    int arr[10];
    int n;

    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(heap, value);
                break;
            case 2:
                printf("Popped value: %d\n", pop(heap));
                break;
            case 3:
                printf("Peek value: %d\n", peek(heap));
                break;
            case 4:
                printf("Enter number of elements (max 10): ");
                scanf("%d", &n);
                printf("Enter %d integers: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                heapify(arr, n);
                printf("Heapified array: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    destroyHeap(heap);
    return 0;
}
