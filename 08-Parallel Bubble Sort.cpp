#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// Bubble Sort algorithm
void bubbleSort(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

// Function to check if array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

// Function to measure execution time
double measureExecutionTime(void (*sortFunction)(int[], int), int arr[], int n) {
    double start_time, end_time;
    start_time = omp_get_wtime();
    sortFunction(arr, n);
    end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    const int n = 10000;
    int arr1[n], arr2[n];
    int n_threads = omp_get_max_threads();

    // Generate random arrays
    generateRandomArray(arr1, n);
    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i]; // Copying arr1 to arr2
    }

    // Measure execution time of Bubble Sort
    double bubbleSortSequentialTime = measureExecutionTime(bubbleSort, arr1, n);
    double bubbleSortParallelTime = measureExecutionTime(bubbleSort, arr2, n);

    // Print results
    cout << "Bubble Sort execution time with " << n_threads << " threads: " << bubbleSortParallelTime << " seconds" << endl;
    cout << "Bubble Sort execution time without parallelism: " << bubbleSortSequentialTime << " seconds" << endl;

    // Check if arrays are sorted
    if (isSorted(arr1, n)) {
        cout << "Array 1 is sorted" << endl;
    } else {
        cout << "Array 1 is not sorted" << endl;
    }

    if (isSorted(arr2, n)) {
        cout << "Array 2 is sorted" << endl;
    } else {
        cout << "Array 2 is not sorted" << endl;
    }

    return 0;
}
