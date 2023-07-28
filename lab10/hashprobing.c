#include<stdlib.h>
#include<stdio.h>
// linear probing, quadratic probing, double hashing function
// let user choose function and values
// free memory
#define SIZE 10

typedef struct Node{
    int key;
    int val;
}Node;

Node* makeNode(int key, int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->val = val;
    return newNode;
}

Node* HashTable[SIZE];

int h1(int key){
    return key % SIZE;
}

int h2(int key){
    return 7 - (key % 7);
}

void insertLinearProbing(int key, int val){
    int index = h1(key);
    int i = 0;
    while (HashTable[h1(index + i)] != NULL && ++i < SIZE);
    if (i == SIZE){
        printf("Hash table is full\n");
        return;
    }
    Node* newNode = makeNode(key, val);
    HashTable[h1(index + i)] = newNode;
}

void insertQuadraticProbing(int key, int val){
    int index = h1(key);
    int i = 0;
    while (HashTable[(index + i*i)%SIZE] != NULL && ++i < SIZE);
    if (i == SIZE){
        printf("Hash table if full\n");
        return;
    }
    Node* newNode = makeNode(key, val);
    HashTable[(index + i*i)%SIZE] = newNode;
}

void insertDoubleHashing(int key, int val){
    int index = h1(key);
    int i = 0;
    while (HashTable[(index + i * h2(key))%SIZE] != NULL && ++i < SIZE);
    if (i == SIZE){
        printf("Hash table is full\n");
        return;
    }
    Node* newNode = makeNode(key, val);
    HashTable[(index + i * h2(key))%SIZE] = newNode;
}

void printHashTable(){
    for (int i = 0; i < SIZE; i++){
        if (HashTable[i] != NULL){
            printf("Index: %d, Key: %d, Value: %d\n", i, HashTable[i]->key, HashTable[i]->val);
        }
        else{
            printf("Index: %d, Emtpy\n", i);
        }
        printf("\n");
    }
}

void clearHashTable(){
    for (int i = 0; i < SIZE; i++){
        if (HashTable[i] != NULL){
            free(HashTable[i]);
            HashTable[i] = NULL;
        }
    }
}

int main(){
    
    int key, val, choice;

    printf("Choose collision resolution method (1-Linear Probing, 2-Quadratic Probing, 3-Double Hashing, 4-Print Table, 5-Exit): ");
    scanf("%d", &choice);
    while (choice != 5){

        switch (choice)
        {
        case 1: 
            printf("Enter key and value to insert: ");
            scanf("%d %d", &key, &val);
            insertLinearProbing(key, val);
            break;

        case 2:
            printf("Enter key and value to insert: ");
            scanf("%d %d", &key, &val);
            insertQuadraticProbing(key, val);
            break;
        case 3:
            printf("Enter key and value to insert: ");
            scanf("%d %d", &key, &val);
            insertDoubleHashing(key, val);
            break;
        case 4: 
            printHashTable();
            break;
        
        case 5:
            printf("Exiting");
            break;
        default:
            printf("Invalid option\n");
            break;
        }
        printf("Choose collision resolution method (1-Linear Probing, 2-Quadratic Probing, 3-Double Hashing, 4-Print Table, 5-Exit): ");
        scanf("%d", &choice);
    }
    clearHashTable();
    return 0;
}
