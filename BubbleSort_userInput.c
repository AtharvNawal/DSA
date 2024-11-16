#include <stdio.h>

int main() {
    int n, i, j, temp;

    printf ("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d integers: ", n);  //input array elements
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Unsorted array: \n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (i = 0; i < n - 1; i++) {          // Bubble sort algorithm
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {     // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: \n");   // Print sorted array
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
