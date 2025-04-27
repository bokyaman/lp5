#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<ctime>
using namespace std;

// Function to perform Bubble Sort in parallel
void bubble(int *a, int n)
{
  // Outer loop runs 'n' times (length of the array)
  for (int i=0; i<n; i++)
  {
    // Odd-even indexing, first is set to 0 for even passes and 1 for odd passes
    int first = i%2;
    
    // Parallel for loop where each thread handles either even or odd indexed elements
    #pragma omp parallel for
    for (int j=first; j<n-1; j+=2)
    {
      // Swap the elements if they are out of order
      if (a[j] > a[j+1])
      {
        swap(a[j], a[j+1]);
      }
    }
  }
}

// Swap function to swap two elements
void swap(int &a, int &b)
{
  int test;
  test = a;
  a = b;
  b = test;
}

int main()
{
  // Declare two arrays, 'a' and 'b', for sorting
  int *a,*b , n =10000;  // 'n' is the size of the array
  
  a = new int[n];  // Allocate memory for array 'a'
  b = new int[n];  // Allocate memory for array 'b'

  // Initialize arrays with random values between 0 and 9999
  for(int i=0; i<n; i++)
  {
    a[i] = rand() % 10000;
    b[i] = a[i];  // Copy the contents of 'a' to 'b' for comparison
  }
  
  // Sequential Bubble Sort to sort array 'b'
  double start = omp_get_wtime();  // Start timer for sequential bubble sort
  for (int i=0; i<n; i++)  // Outer loop for bubble sort
  {
    for (int j=0; j<n-1; j++)  // Inner loop for comparing adjacent elements
    { 
      // Swap if elements are in wrong order
      if (b[j] > b[j+1])
      {
        swap(b[j], b[j+1]);
      }
    }
  }
  double end = omp_get_wtime();  // End timer for sequential bubble sort

  // Parallel Bubble Sort to sort array 'a'
  double start1 = omp_get_wtime();  // Start timer for parallel bubble sort
  bubble(a, n);  // Perform bubble sort on array 'a' in parallel
  double end1 = omp_get_wtime();  // End timer for parallel bubble sort
  
  // Output the sorted array 'a' to check if sorting is correct (for first 10 elements)
  for (int i=0 ; i<n; i++)
  {
    cout << a[i] << "\t";  // Print each element
    if (i % 10 == 0)  // Print a new line every 10 elements for readability
    {
      cout << endl;
    }
  }

  // Display the time taken for both sequential and parallel sorting
  cout << "\nSequential time: " << (end - start) << endl;
  cout << "Parallel time: " << (end1 - start1) << endl;
}


//This program compares the performance of **sequential bubble sort** and **parallel bubble sort** on an array of random numbers. The program uses **OpenMP** to parallelize the bubble sort algorithm, which is typically slow for large arrays. Here’s a simple breakdown of how the program works:

### Key Concepts:

1. **Bubble Sort**: 
   - This is a basic sorting algorithm where you repeatedly compare adjacent elements in the array and swap them if they are out of order.
   - The algorithm continues this process until the entire array is sorted.

2. **Parallelization**: 
   - The program uses **OpenMP** to run parts of the bubble sort algorithm in parallel, meaning multiple threads (or processors) can work on sorting different parts of the array at the same time.

### Step-by-Step Explanation:

#### 1. **Libraries**:
   - `iostream`: For input and output operations.
   - `stdlib.h`: For generating random numbers.
   - `omp.h`: For OpenMP functions (used to parallelize the program).
   - `ctime`: For timing the execution.

#### 2. **Bubble Sort Function (Parallel)**:
   - The `bubble` function is a parallel version of bubble sort. Here's how it works:
     - **Outer loop**: The algorithm runs for `n` iterations where `n` is the number of elements in the array.
     - **Odd-Even Indexing**: In bubble sort, each pass compares adjacent pairs of elements. The algorithm alternates between even and odd indexed pairs using a `first` variable. This helps split the workload for parallel processing.
     - **Parallel Loop**: OpenMP's `#pragma omp parallel for` directive runs the inner loop in parallel, with each thread handling either even or odd indexed pairs of elements.

#### 3. **Swap Function**:
   - The `swap` function is used to exchange two elements in the array when they are out of order. It temporarily stores one element and swaps the values.

#### 4. **Main Function**:
   - **Array Initialization**: 
     - Two arrays `a` and `b` are declared. `a` is for parallel sorting, and `b` is for sequential sorting.
     - Both arrays are initialized with random numbers (between 0 and 9999).
   
   - **Sequential Bubble Sort**: 
     - The `for` loops in the main function perform a traditional (sequential) bubble sort on array `b`. It compares adjacent elements and swaps them until the array is sorted.
     - The time taken for the sequential sort is measured using `omp_get_wtime()`.

   - **Parallel Bubble Sort**:
     - The `bubble` function is called to sort array `a` using the parallel bubble sort.
     - The time taken for the parallel sort is also measured.

   - **Printing the Sorted Array**:
     - The sorted array `a` is printed to check if the sorting is correct. Only the first few elements are printed for readability.

   - **Display Execution Time**:
     - The program outputs the time taken for both the sequential and parallel bubble sorts, allowing you to compare the performance.

#### 5. **Output**:
   - The sorted array `a` is printed to the console.
   - The program prints the time it took to sort the array using sequential and parallel bubble sort. This helps to see how much faster the parallel version is compared to the traditional method.

### Example Execution:

- Suppose you have an array of size `10` with random values. 
- The program will:
  - Sort the array using the traditional (sequential) bubble sort and measure the time.
  - Then, it will sort the array using the parallel bubble sort and measure the time again.
  - Finally, it will print both the sorted array and the time taken for each sort.

### Why Parallel Bubble Sort?

- **Bubble Sort** is not the most efficient sorting algorithm, but parallelizing it with OpenMP allows multiple threads to work on different parts of the array at the same time. This can speed up the sorting process for large arrays.
  
### Summary:

- This program compares **sequential** and **parallel** bubble sort algorithms on a random array of integers.
- The **sequential bubble sort** sorts the array one element at a time, while the **parallel bubble sort** tries to speed up the sorting by processing different parts of the array at the same time.
- The program measures and prints the execution time for both sorting methods and prints the sorted array to check if it is correct.
