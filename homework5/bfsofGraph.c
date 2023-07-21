#include<stdio.h>
#include<stdlib.h>

#define n 9

void bfs(int graph[n][n], int start){
    int visited[n] = {0};
    int queue[n], front = 0, rear = -1;
    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear){
        int vertex = queue[front++];
        printf("%d ", vertex);
        
        for(int i = 0; i < n; i++){
            if(graph[vertex][i] && !visited[i]){
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }

    


}

int main(){

    int graph[n][n] = {
        {0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    printf("BFS traversal: \n");

    bfs(graph, 0);

    return 0;
}