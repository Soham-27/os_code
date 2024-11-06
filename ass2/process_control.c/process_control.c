#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to perform Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    int arr[MAX_SIZE];
    pid_t pid=fork();
    
    
    printf("Enter the number of elements (max %d):\n", MAX_SIZE);
    scanf("%d", &n); // Removed space in format string
    if (n > MAX_SIZE || n <= 0) { // Check for valid input
        printf("Please enter a valid number of elements.\n");
        return 1; // Exit with error
    }
    
    
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]); // Changed to use &arr[i]
    }

    // Display the unsorted array
    printf("Unsorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    // Sort the array using Bubble Sort
    bubble_sort(arr, n);

    // Display the sorted array
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    return 0;
}
		
