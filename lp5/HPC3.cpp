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


//This program performs **parallel computations** on an array of integers to find the **minimum**, **maximum**, **sum**, and **average** of its elements using **OpenMP** for parallel processing. Here’s a simple explanation of what each part of the program does:

### Key Concepts:

1. **OpenMP**: 
   - This is a library used for **parallel programming**. It allows the program to run multiple tasks at the same time, making operations faster when there are many tasks (like processing a large array).

2. **Reduction**:
   - A reduction is a technique used in parallel programming where each thread computes part of a result and then combines those results. In this program, we use **OpenMP reduction** to safely calculate the **minimum**, **maximum**, **sum**, and **average** without data conflicts between multiple threads.

### Breakdown of the Program:

#### 1. **min_reduction** Function (Finds Minimum Value):
   - The program initializes `min_value` to the largest possible integer (`INT_MAX`).
   - It uses the `#pragma omp parallel for reduction(min: min_value)` directive to parallelize the loop that checks each element of the array.
   - Each thread looks at parts of the array and updates the `min_value` if it finds a smaller value.
   - After all threads have finished, the smallest value is printed.

#### 2. **max_reduction** Function (Finds Maximum Value):
   - The program initializes `max_value` to the smallest possible integer (`INT_MIN`).
   - Similar to the `min_reduction` function, this one uses `#pragma omp parallel for reduction(max: max_value)` to parallelize the loop and find the largest value in the array.
   - It prints the largest value after all threads finish their work.

#### 3. **sum_reduction** Function (Finds Sum of Elements):
   - The program initializes `sum` to 0.
   - It uses `#pragma omp parallel for reduction(+: sum)` to parallelize the loop and accumulate the sum of all array elements.
   - Once all threads are done, the sum is printed.

#### 4. **average_reduction** Function (Finds Average Value):
   - This function also calculates the sum of the array using parallel reduction, just like `sum_reduction`.
   - After the sum is calculated, the average is computed by dividing the sum by the number of elements (`n`).
   - The average is then printed.

#### 5. **main** Function:
   - The user is prompted to enter the number of elements (`n`) in the array.
   - The program dynamically allocates memory for the array (`arr`) and takes user input for the array elements.
   - The program then calls the four functions (`min_reduction`, `max_reduction`, `sum_reduction`, and `average_reduction`) to perform the calculations.
   - Finally, the allocated memory for the array is freed using `delete[]`.

### Example:
1. **Input**:
   ```
   Enter total number of elements => 5
   Enter elements => 10 5 20 15 30
   ```

2. **Output**:
   ```
   Minimum value: 5
   Maximum value: 30
   Sum: 80
   Average: 16
   ```

### Why Use OpenMP Here?
- **OpenMP** allows us to **parallelize** the calculations, meaning the program can potentially perform the operations faster, especially if the array size is large and there are multiple CPU cores available.

### Summary:
- The program takes an array of numbers, then **parallelizes** the calculations to find the **minimum**, **maximum**, **sum**, and **average** of the array elements using **OpenMP reduction**.
- This method ensures that the program works efficiently, utilizing multiple CPU cores for faster processing when handling large arrays.


