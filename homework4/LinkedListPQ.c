#include<stdio.h>
#include<stdlib.h>


#define MAX_SIZE 100


typedef struct listNode{
    int data;
    int priority;
    struct listNode* next;
}listNode_t;

listNode_t* head = NULL;
int size = 0;

listNode_t* makeNode(int data, int priority){
    listNode_t* newNode = (listNode_t*)malloc(sizeof(listNode_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(){
    return head == NULL;
}

void enqueue(int data, int priority){
    listNode_t* newNode = makeNode(data, priority);
    if (newNode == NULL){
        return;
    }
    if (size >= MAX_SIZE){
        return;
    }
    if (head == NULL || head->priority > priority){
        newNode->next = head;
        head = newNode;
    }else{
        listNode_t* pointer = head;
        while (pointer->next != NULL && pointer->next->priority < priority){
            pointer = pointer->next;
        }
        newNode->next = pointer->next;
        pointer->next = newNode;
    }
    size++;
}

int dequeue(){
    if (head == NULL){
        printf("Queue is empty.\n");
        return -1;
    }
    listNode_t* temp = head;
    int priority = temp->priority;
    int data = temp->data;
    head = head->next;
    size--;
    printf("Deque priority %d and data %d\n", temp->priority, temp->data);
    free(temp);
    return 0;
}

int isFull(){
    return size >= MAX_SIZE;
}
void printListNode(){
    if (head == NULL){
        printf("Empty priority queue.\n");
        return;
    }
    listNode_t* tmp = head;
    while (tmp != NULL){
        printf("priority: %d    data: %d\n", tmp->priority, tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}
int main(){
    int choice, data, priority;
    do {
        printf("\n1.Enqueue\n2.Dequeue\n3.Check if Empty\n4.Check if Full\n5.Print LinkedList\n6.Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
             case 1:
                printf("Enter data and its priority: ");
                scanf("%d %d", &data, &priority);
                enqueue(data, priority);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                if(isEmpty()){
                    printf("Queue is empty.\n");
                }else{
                    printf("Queue is not empty.\n");
                }
                break;
            case 4:
                if(isFull()){
                    printf("Queue is Full.\n");
                }else{
                    printf("Queue is not Full.\n");
                }
                break;
            case 5:
                printListNode();
                break;
            case 6:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }     
    }while (choice != 6);

    return 0;
}

