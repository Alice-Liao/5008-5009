#include<stdio.h>
#include<stdlib.h>


int changeCoins(int coins[], int number, int amount){
    int dp[amount + 1];
    for(int i = 0; i < amount + 1; i++){
        dp[i] = amount + 1;
    }
    dp[0] = 0;
    
    for (int i = 0; i < amount + 1; i++){
        for (int j = 0; j < number; j++){
            if (i >= coins[j]){
                int sub_res = dp[i - coins[j]];
                if(sub_res != amount + 1 && sub_res + 1 < dp[i]){
                    dp[i] = sub_res + 1;
                }
            }

        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

int main(){
    int number;
    int amount;
    printf("Number of values of coins:\n");
    scanf("%d", &number);
    int coins[number];
    printf("Coins:\n");
    for (int i = 0; i < number; i++){
        scanf("%d", &coins[i]);
    }
    printf("Amount:\n");
    scanf("%d", &amount);

    
    int ans = changeCoins(coins, number, amount);
    printf("Answer:\n%d\n", ans);

    return 0;
}