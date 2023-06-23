#include<stdio.h>
#include<stdlib.h>


void merge(int array[], int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for(i = 0; i < n1; i++){
        L[i] = array[left + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = array[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2){
        if(L[i] <= R[j]){
            array[k] = L[i];
            i++;
        }else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        array[k] = R[j];
        k++;
        j++;

    }
}
void mergeSort(int array[], int left, int right){
    if (left >= right){
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

int binarySearch(int array[], int start, int end, int target){
    if (start > end){
        return -1;
    }
    int mid = start + (end - start) / 2;
    if(array[mid] == target){
        return mid;
    }else if(array[mid] > target){
        return binarySearch(array, start, mid - 1, target);
    }else {
        return binarySearch(array, mid + 1, end, target);
    }   
}
void printArray(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main(){
    printf("Input array size:\n");
    int size;
    scanf("%d", &size);
    printf("Input elements of the array:\n");
    int* array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++){
        scanf("%d", &array[i]);
    }
    printf("Input target:\n");
    int target;
    scanf("%d", &target);

    printf("The array:\n");
    printArray(array, size);

    printf("The target:\n");
    printf("%d\n", target);

    mergeSort(array, 0, size - 1);
    int pos = binarySearch(array, 0, size - 1, target);

    printf("Search result:\n%d\n", pos);
    free(array);
    return 0;
}
