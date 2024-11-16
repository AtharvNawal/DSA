#include <stdio.h>

void swap(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int j = high;
    int i=low+1;
                                // for (i = low+1; i <= high; i++) {
                                //     if(arr[i]>pivot){
                                //         if(arr[j]>pivot){
                                //             j--;
                                //         }
                                //         else{
                                //             swap(&arr[i],&arr[j]);
                                //             i++;
                                //             j--;
                                //         }
                                //     }
                                // }
    while (i < j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return (j);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int arr[] = { 10, 7, 8, 9, 1, 5,90 };
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    printf("Sorted Array\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}