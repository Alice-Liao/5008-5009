#include<stdlib.h>
#include<stdio.h>
// take input from user: chain size and number of val, and vals
// free memory 
typedef struct node{
    int data;
    struct node* next;
}node_t;

node_t* makeNode(int data){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

typedef struct LinkedList{
    node_t* head;
}LinkedList_t;

typedef struct HashTable{
    LinkedList_t* array;
    int size;
}HashTable_t;

HashTable_t* makeHash(int size){
    HashTable_t* newHash = (HashTable_t*)malloc(sizeof(HashTable_t));
    if (newHash == NULL){
        return NULL;
    }
    newHash->array = (LinkedList_t*)malloc(sizeof(LinkedList_t) * size);
    if (newHash->array == NULL){
        free(newHash);
        return NULL;
    }
    for (int i = 0; i < size; i++){
        newHash->array[i].head = NULL;
    }

    newHash->size = size;
    return newHash;
}

void insert(HashTable_t* hash, int size, int data){
    if (hash == NULL){
        return;
    }
    
    node_t* newNode = makeNode(data);
    if(newNode == NULL){
        return; 
    }

    int position = data % size;
    node_t* temp = hash->array[position].head;
    node_t* prev = NULL;

    if (temp == NULL || temp->data >= data){
        newNode->next = temp;
        hash->array[position].head = newNode;
    }else{
        while (temp != NULL && temp->data < data){
            prev = temp;
            temp = temp->next;
        }
        newNode->next = temp ;
        prev->next = newNode;
    }
}

void printHash(HashTable_t* hash, int size){
    printf("The table:\n");
    if (hash == NULL){
        return;
    }
    node_t* temp = NULL;
    for (int i = 0; i < size; i++){
        printf("Chain[%d]", i);
        temp = hash->array[i].head;
        while (temp != NULL){
            printf("->%d", temp->data);
            temp = temp->next;
        }
        printf("->NULL\n");
    }

}

void freeHash(HashTable_t* hash, int size){
    for (int i = 0; i < size; i++){
        node_t*  temp = hash->array[i].head;
        while (temp != NULL){
            node_t* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(hash->array);
    free(hash);
}


int main(){
    int size;
    printf("Input chain size:\n");
    scanf("%d", &size);

    int number;
    printf("Input Number of values:\n");
    scanf("%d", &number);
     

    HashTable_t* newHash = makeHash(size);

    printf("Input Values:\n");
    int arr[number];
    for (int i = 0; i < number; i++){
        scanf("%d", &arr[i]);
        insert(newHash, size, arr[i]);
    }
    printf("\n");

    printHash(newHash, size);
    freeHash(newHash, size);
    return 0;
}


