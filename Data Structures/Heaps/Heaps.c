#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int arr[100];
    int n;
} Heap;

Heap* newHeap();
void shiftUp(int* arr, int i);
void insertHeap(Heap* h , int val);
void shiftDown(int* arr, int n, int i);
void swap(int* arr, int i, int j);
void pop(Heap* h);

int main(){
    Heap* h = newHeap();
    // Insert elements
    insertHeap(h, 50);
    insertHeap(h, 30);
    insertHeap(h, 70);
    insertHeap(h, 10);
    insertHeap(h, 90);
    insertHeap(h, 20);
    printf("Heap after insertion:\n");
    for(int i = 0; i < h->n; i++){
        printf("%d ", h->arr[i]);
    }
    // Pop maximum
    printf("\n\nPopped: %d\n", h->arr[0]);
    pop(h);
    printf("Heap after first pop:\n");
    for(int i = 0; i < h->n; i++){
        printf("%d ", h->arr[i]);
    }
    // Pop again
    printf("\n\nPopped: %d\n", h->arr[0]);
    pop(h);
    printf("Heap after second pop:\n");
    for(int i = 0; i < h->n; i++){
        printf("%d ", h->arr[i]);
    }
    printf("\n");
    free(h);
    return 0;
}

Heap* newHeap(){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->n = 0;
    return h;
}

void shiftUp(int* arr, int i){
    int parent = (i-1)/2;
    if(i>0 && arr[parent] < arr[i]){
        swap(arr, parent, i);
        shiftUp(arr , parent);
    }
}

void insertHeap(Heap* h , int val){
    h->arr[h->n] = val;
    shiftUp(h->arr,h->n);
    h->n++;
}

void shiftDown(int* arr, int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if( l < n && arr[l] > arr[largest]){
        largest = l;
    }

    if(r < n && arr[r] > arr[largest] ){
        largest = r;
    }

    if(largest != i){
        swap(arr, largest, i);
        shiftDown(arr , n , largest);
    }
}


void pop(Heap* h){
    if(h->n == 0){
        return;
    }
    h->n--;
    h->arr[0] = h->arr[h->n];
    shiftDown(h->arr , h->n , 0 );
}

void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}