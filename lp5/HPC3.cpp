#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

// Function to find the minimum value in the array using OpenMP reduction
void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;  // Initialize min_value to the maximum possible integer
  // OpenMP parallel for loop with a reduction on the min_value variable
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];  // Update the minimum value if a smaller value is found
    }
  }
  cout << "Minimum value: " << min_value << endl;  // Output the minimum value
}

// Function to find the maximum value in the array using OpenMP reduction
void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;  // Initialize max_value to the minimum possible integer
  // OpenMP parallel for loop with a reduction on the max_value variable
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];  // Update the maximum value if a larger value is found
    }
  }
  cout << "Maximum value: " << max_value << endl;  // Output the maximum value
}

// Function to find the sum of the array elements using OpenMP reduction
void sum_reduction(int arr[], int n) {
  int sum = 0;  // Initialize sum to zero
  // OpenMP parallel for loop with a reduction on the sum variable
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add the array elements to the sum
  }
  cout << "Sum: " << sum << endl;  // Output the sum of elements
}

// Function to calculate the average of the array elements using OpenMP reduction
void average_reduction(int arr[], int n) {
  int sum = 0;  // Initialize sum to zero
  // OpenMP parallel for loop with a reduction on the sum variable
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add the array elements to the sum
  }
  // Output the average by dividing the sum by the total number of elements
  cout << "Average: " << (double)sum / n << endl;  
}

int main() {
  int *arr, n;
  
  // Prompt the user for the number of elements
  cout << "\nEnter total number of elements => ";
  cin >> n;
  
  arr = new int[n];  // Dynamically allocate memory for the array
  
  // Prompt the user to input the elements of the array
  cout << "\nEnter elements => ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];  // Read each element of the array from the user
  }

  // Call the functions for min, max, sum, and average
  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);

  delete[] arr;  // Deallocate memory used for the array

  return 0;
}
