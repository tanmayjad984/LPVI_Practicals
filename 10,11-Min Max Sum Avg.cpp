#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>


using namespace std;


// Function to generate random array
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}


// Function to find the minimum value in an array using parallel reduction
int findMin(int arr[], int n) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}


// Function to find the maximum value in an array using parallel reduction
int findMax(int arr[], int n) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}


// Function to find the sum of values in an array using parallel reduction
int findSum(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}


// Function to find the average value in an array using parallel reduction
double findAverage(int arr[], int n) {
    double avg = 0;
    #pragma omp parallel for reduction(+:avg)
    for (int i = 0; i < n; i++) {
        avg += arr[i];
    }
    avg /= n;
    return avg;
}


int main() {
    const int n = 10000;
    int arr[n];


    // Generate random array
    generateRandomArray(arr, n);


    // Find minimum value
    int min_val = findMin(arr, n);
    cout << "Minimum value: " << min_val << endl;


    // Find maximum value
    int max_val = findMax(arr, n);
    cout << "Maximum value: " << max_val << endl;


    // Find sum of values
    int sum = findSum(arr, n);
    cout << "Sum of values: " << sum << endl;


    // Find average value
    double avg = findAverage(arr, n);
    cout << "Average value: " << avg << endl;


    return 0;
}
