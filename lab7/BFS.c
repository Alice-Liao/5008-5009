#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node* left;
    int data;
    struct node* right;
}node_t;

node_t* makeNode(int data){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

typedef struct queue{
    unsigned capacity;
    unsigned size;
    unsigned front;
    node_t** array;
}queue_t;

queue_t* makeQueue(int capacity){
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    if (q == NULL){
        return NULL;
    }
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->array = (node_t*)malloc(q->capacity * sizeof(node_t));
    return q;
}

int isEmpty(queue_t* q){
    return (q->size == 0);
}

void enqueue(queue_t* q, node_t* node){
    if (q->size == q->capacity){

        printf("Queue is full.\n");
        return;
    }
    q->array[(q->front + q->size) % q->capacity] = node;
    q->size++;
}

node_t* dequeue(queue_t* q){
    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return NULL;
    }
    node_t* node = q->array[q->front];
    q->front = (q->front+1) % q->capacity;
    q->size--;
    return node;
}

node_t* createTree(int arr[], int n, int i) {
    if (i < n && arr[i] != -1){
        node_t* node = makeNode(arr[i]);
        node->left = createTree(arr, n, 2 * i + 1);
        node->right = createTree(arr, n, 2 * i + 2);
        return node;
    }
    return NULL;
}

void bfs(node_t* root){
    if (root == NULL) return;
    queue_t* q = makeQueue(1000);
    enqueue(q, root);
    while (!isEmpty(q)){
        node_t* node = dequeue(q);
        printf("%d ", node->data);
        if(node->left != NULL){
            enqueue(q, node->left);
        }
        if(node->right != NULL){
            enqueue(q, node->right);
        }
    }
    free(q);
}


int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    node_t* root = createTree(arr, n, 0);
    
    printf("BFS:\n");
    bfs(root);
    free(root);




    return 0;
}
