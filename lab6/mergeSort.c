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

void printArray(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%d", array[i]);
        if (i != size - 1){
            printf(",");
        }
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int array[n];
    printf("Enter elements: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    printf("Input array:\n");
    printArray(array, n);

    mergeSort(array, 0, n - 1);

    printf("Output array:\n");
    printArray(array, n);
    return 0;

}
