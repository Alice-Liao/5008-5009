#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
int knapsack(int numberItem, int value[], int weights[], int capacity){
    int dp[numberItem+1][capacity+1];
    for (int i = 0; i <= numberItem; i++){
        for (int j = 0; j <= capacity; j++){
            if (i == 0 || j == 0){
                dp[i][j] = 0;
            }else if (weights[i-1] <= j){
                dp[i][j] = max(value[i-1] + dp[i-1][j - weights[i-1]], dp[i-1][j]);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[numberItem][capacity];
}

int main(){
    while (1) {
        int numberItem;
        printf("Number of items:\n");
        scanf("%d", &numberItem);
        printf("Item values:\n");

        int values[numberItem];
        for (int i = 0; i < numberItem; i++){
            scanf("%d", &values[i]);
        }

        int weights[numberItem];
        printf("Item weights:\n");
        for (int i = 0; i < numberItem; i++){
            scanf("%d", &weights[i]);
        }
    
        int capacity;
        printf("Knapsack weight capacity:\n");
        scanf("%d", &capacity);

        int maxValue;
        maxValue = knapsack(numberItem, values, weights, capacity);
        printf("Answer: Maximum value:\n%d", maxValue);
        printf("\n");
    }
    return 0;
}