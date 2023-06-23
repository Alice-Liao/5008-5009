#include <stdio.h>
#include <stdlib.h>


int convertToBinary(int num){
    int bi = 0, cnt = 0;
    while(num > 0){
        int remainder = num % 2;
        int temp = 1;
        for (int j = 0; j < cnt; j++){
            temp *= 10;
        }
        bi += remainder * temp;
        num /= 2;
        cnt ++;
    }
    return bi;
}

int convertToDecimal(int binary){
    int decimal = 0, base = 1;
    while (binary > 0){
        int last = binary % 10;
        binary = binary / 10;
        decimal += last * base;
        base = base * 2;
    }
    return decimal;
}

int linearSearch(int* array, int size, int target){
    for (int i = 0; i < size; i++){
        if (array[i] == target){
            return i;
        }
    }
    return -1;
}
void printArray(int array[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}


int main(){
    int size;
    printf("Input array size: \n");
    scanf("%d", &size);
    printf("Input elements of the array:\n");

    int* array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++){
        scanf("%d", &array[i]);
    }
    int target;
    printf("Input target:\n");
    scanf("%d", &target);
    
    printf("The array:\n");
    printArray(array, size);

    printf("The target:\n");
    printf("%d\n", target);
    
    int* convertedArr = malloc(size * sizeof(int));
    printf("Converted array:\n");
    for(int i = 0; i < size; i++){
        convertedArr[i] = convertToBinary(array[i]);
    }
    int convertedTarget = convertToBinary(target);
    printArray(convertedArr, size);
    printf("Converted target:\n%d\n", convertedTarget);

    int pos = linearSearch(array, size, target);
    printf("Search result:\n%d\n", pos);

    printf("Original array:\n");
    int* original = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++){
        original[i] = convertToDecimal(convertedArr[i]);
    }
    printArray(original, size);

    int originalTarget = convertToDecimal(convertedTarget);
    printf("Original target:\n%d\n", originalTarget);

    free(array);
    free(convertedArr);
    free(original);
    return 0;



}