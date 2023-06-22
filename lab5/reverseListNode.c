#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node_t;

node_t* makeNode(int data){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL){
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
} 
void printLinkedList(node_t* head){
    node_t* cur = head;
    while(cur != NULL){
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
node_t* reverseListNode(node_t* head){
    if (head == NULL || head->next == NULL){
        return head;
    }
    node_t* newHead =reverseListNode(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
int main(){
    int size;
    printf("Input list size:\n");
    scanf("%d", &size);
    printf("Input elements of the array:\n");   
    int data;
    node_t* head = NULL;
    node_t* cur = NULL;
    while (size > 0){
        scanf("%d", &data);
        if(head == NULL){
            head = makeNode(data);
            cur = head;
        }else{
            node_t* newNode = makeNode(data);
            cur->next = newNode;
            cur = cur->next;
        }
        size--;
    }
    printf("The list:\n");
    printLinkedList(head);
    node_t* reversed = reverseListNode(head);
    printf("The reversed list:\n");
    printLinkedList(reversed);
    return 0;

   
}

