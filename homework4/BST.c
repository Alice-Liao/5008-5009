#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct treenode{
    int val;
    struct treenode* left;
    struct treenode* right;

}treenode_t;


treenode_t* makeNode(int val){
    treenode_t* newNode = (treenode_t*)malloc(sizeof(treenode_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

treenode_t* insert(treenode_t* root, int val){
    if(root == NULL){
        return makeNode(val);
    }
    if(val > root->val){
        root->right = insert(root->right, val);
    }else if (val < root->val){
        root->left = insert(root->left, val);
    }
    return root;
}

treenode_t* buildTree(int array[], int len){
    treenode_t* root = NULL;
    for (int i = 0; i < len; i++){
        root = insert(root, array[i]);
    }
    return root;
}

int binarySearch(treenode_t* root, double target){
    int closeVal = root->val;
    while (root != NULL){
        if (fabs(target - root->val) < fabs(target - closeVal)){
            closeVal = root->val;
        }
        root = target < root->val ? root->left : root->right;
    }
    return closeVal;
}

void printTree(treenode_t* root){

}

int main(){
    //test case:
    //printf("test case:\nint array[] = {4,2,5,1,3}  double target = 3.714286");
    //int array[] = {4,2,5,1,3};
    //int len = sizeof(array) / sizeof(array[0]);
    //treenode_t* root = buildTree(array, len);

    //double target = 3.714286;
    //int closeVal = binarySearch(root, target);
    //printf("%d\n", closeVal);
    //free(root);
     
    while (1){
        int size;
        printf("Enter the number of elements in the BST:\n");
        scanf("%d", &size);
    
        int val[size];
        printf("Enter the values for the BST:\n");
        for (int i = 0; i < size; i++){
            scanf("%d", &val[i]);
        }
        treenode_t* user_root = buildTree(val, size);
        double user_target;
        printf("Enter the target value:\n");
        scanf("%lf", &user_target);

        int res = binarySearch(user_root, user_target);
        printf("Closest number: %d\n", res);
        free(user_root);
    }
    
    return 0;


}
