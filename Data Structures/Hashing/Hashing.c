#include <stdio.h>
#include <stdlib.h>

/* 
This code is for linear probing. 
Check the comments at the end of the file to know the changes to be made for quadratic probing and double hashing.
*/

typedef struct {
    int *hashTable;
    int N;
} Hash;

Hash *construct(int N) {
    Hash *h = (Hash *)malloc(sizeof(Hash));
    h->N = N;
    h->hashTable = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        h->hashTable[i] = -1;
    return h;
}
int hash1(Hash *h, int value) {
    return (value % h->N);
}
int search(Hash *h, int value) {
    int probe = hash1(h, value);
    for (int i = 0; i < h->N; i++) {
        int ind = (probe + i) % h->N;
        if (h->hashTable[ind] == -1)
            return -1;
        if (h->hashTable[ind] == value)
            return ind;
    }
    return -1;
}
int insert(Hash *h, int value) {
    if (search(h, value) != -1)
        return 1;
    int probe = hash1(h, value);
    for (int i = 0; i < h->N; i++) {
        int ind = (probe + i) % h->N;
        if (h->hashTable[ind] == -1 || h->hashTable[ind] == -2) {
            h->hashTable[ind] = value;
            return 1;
        }
    }
    return 0;
}

void delete(Hash *h, int value) {
    int ind = search(h, value);
    if (ind == -1)
        return;
    h->hashTable[ind] = -2;
}

void printHash(Hash *h) {
    for (int i = 0; i < h->N; i++) {
        printf("[%d] -> ", i);
        if (h->hashTable[i] == -1)
            printf("EMPTY\n");
        else if (h->hashTable[i] == -2)
            printf("DELETED\n");
        else
            printf("%d\n", h->hashTable[i]);
    }
}

int main(void) {
    int N = 10;
    Hash *h = construct(N);

    printf("______Linear Probing_______\n\n");

    int x[] = {8, 28, 18, 87, 7};
    int n = sizeof(x) / sizeof(int);
    printf("______Insertion______\n");
    printf("Keys: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
        insert(h, x[i]);
    }
    printf("\n\n");
    printf("______Hash Table_______\n");

    printHash(h);

    printf("\nSearching:\n");
    int key = 87;
    int ind = search(h, key);
    if (ind != -1)
        printf("  %d found at index %d\n", key, ind);
    else
        printf("  %d not found\n", key);

    key = 88;
    ind = search(h, key);
    if (ind != -1)
        printf("  %d found at index %d\n", key, ind);
    else
        printf("  %d not found\n", key);

    printf("\nDeleting 8...\n");
    delete(h, 8);

    printf("\n______Hash Table_______\n");
    printHash(h);

    printf("\nSearching for 28...\n");
    key = 28;
    ind = search(h, key);
    if (ind != -1)
        printf("  %d found at index %d\n", key, ind);
    else
        printf("  %d not found\n", key);

    printf("\nInsert 88...\n");
    insert(h, 88);
    printHash(h);

    return 0;
}

/* 
Quadratic Probing:
int ind = (probe + i) % h->N;
Should be changed to
int ind = (probe + i*i) % h->N;
*/

/*
Double Hashing:
We need a second hash function

int hash2(Hash *h, int value) {
    return q - (value % q);
}
Where q is a prime number and q < N

int ind = (probe + i) % h->N;
Should be changed to
int ind = (probe + i * hash2(h, value)) % h->N;
*/