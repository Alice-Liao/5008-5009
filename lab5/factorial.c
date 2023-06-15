#include <stdio.h>
#include <stdlib.h>

int factorial(int number){
    if (number == 0){
        return 1;
    }
    else{
        return number * factorial(number - 1);
    }
}

int main(){
    int number;
    printf("Input the number for factorial calculation:\n");
    scanf("%d", &number);
    int result = factorial(number);
    printf("The factorial of is %d.", result);
    return 0;
}
