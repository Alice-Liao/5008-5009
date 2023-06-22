#include<stdio.h>
#include<stdlib.h>


void swap(int* a, int* b){
    int t = *a;
    *a  = *b;
    *b = t;
}

int partition(int nums[], int low, int high){
    int pivot = nums[low];
    int i = low + 1;
    int j = high;
    while (1){
        while(i <= j && nums[i] < pivot){
            i++;
        }
        while(nums[j] > pivot){
            j--;
        }
        if(i >= j){
            break;
        }
        else{
            swap(&nums[i], &nums[j]);
        }
    }
    swap(&nums[low], &nums[j]);
    return j;
}


void quickSort(int nums[], int start, int end){
    if (start >= end){
        return;
    }
    int pivot = partition(nums, start, end);
    quickSort(nums, start, pivot - 1);
    quickSort(nums, pivot + 1, end);
}



void printArray(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%d", array[i]);
        if (i != size -1){
            printf(",");
        }
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int nums[n];
    printf("Enter the element: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &nums[i]);
    }
    printf("Input array:\n");
    printArray(nums, n);

    quickSort(nums, 0, n - 1);

    printf("Output array: \n");
    printArray(nums, n);


    return 0;
}