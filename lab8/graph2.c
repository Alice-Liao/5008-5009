#include<stdio.h>
#include<stdlib.h>

#define MAX_V 4
typedef struct node{
    int vertex;
    struct node* next;
} node_t;

node_t* makeNode(int vertex){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->vertex = vertex;
    newNode->next = 0;
    return newNode;
}

void addEdge(node_t* adjList[], int i, int j){
    node_t* newNode = makeNode(j);
    newNode->next = adjList[i];
    adjList[i] = newNode;
}

void printAdjacencyMatrix(int adjMatrix[][MAX_V]){
    printf("Adjacency Matrix:\n");
    for(int i = 0; i < MAX_V; i++){
        for(int j = 0; j < MAX_V; j++){
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void printAdjacencyList(node_t* adjList[]){
    printf("Adjacency List:\n");
    for(int i = 0; i < MAX_V; i++){
        printf("%d: ", i);
        node_t* temp = adjList[i];
        while (temp != NULL){
            printf("%d->", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeAdjacencyList(node_t* adjList[]) {
    for (int i = 0; i < MAX_V; i++) {
        node_t* current = adjList[i];
        while (current != NULL) {
            node_t* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main(){
    int adjMatrix[MAX_V][MAX_V] = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0}
    };
    
    node_t* adjList[MAX_V];
    for (int i = 0; i < MAX_V; i++){
        adjList[i] = NULL;
        for(int j = 0; j < MAX_V; j++){
            if(adjMatrix[i][j] == 1){
                addEdge(adjList, i, j);
            }
        }
    }
    printAdjacencyMatrix(adjMatrix);
    printf("\n");
    printAdjacencyList(adjList);
    freeAdjacencyList(adjList);
    return 0;
}

