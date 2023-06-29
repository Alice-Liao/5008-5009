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

node_t* createTree(int arr[], int n, int i){
    if (i < n && arr[i] != -1){
        node_t* node = makeNode(arr[i]);
        node->left = createTree(arr, n, 2 * i + 1);
        node->right = createTree(arr, n, 2 * i + 2);
        return node;
    }
    return NULL;
}

void printPreorder(node_t* root){
    if (root == NULL){
        return;
    }
    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(node_t* root){
    if(root == NULL){
        return;
    }
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

void printPostorder(node_t* root){
    if (root == NULL){
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->data);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    node_t* root = createTree(arr, n, 0);
    
    printf("Preorder:\n");
    printPreorder(root);
    printf("\n");

    printf("Inorder:\n");
    printInorder(root);
    printf("\n");

    
    printf("Postorder:\n");
    printPostorder(root);
    printf("\n");

    free(root);


    return 0;
}


