#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

// Merge function to combine two sorted halves of the array
void marge(int a[], int i1, int j1, int i2, int j2)
{
  int i = i1;
  int j = i2;
  int temp[10000];  // Temporary array to hold merged elements
  int k = 0;
  
  // Merge the two halves into temp[]
  while (i <= j1 && j <= j2)
  {
    if (a[i] < a[j])
    {
      temp[k++] = a[i++];
    }
    else
    {
      temp[k++] = a[j++];
    }
  }
  
  // Copy remaining elements from the first half (if any)
  while (i <= j1)
  {
    temp[k++] = a[i++];
  }
  
  // Copy remaining elements from the second half (if any)
  while (j <= j2)
  { 
    temp[k++] = a[j++];
  }
  
  // Copy the sorted elements back to the original array
  for (i = i1, j = 0; i <= j2; i++, j++)
  {
    a[i] = temp[j];
  }
}

// Parallel merge sort function
void margesort(int a[], int i, int j)
{
  int mid;
  if (i < j)
  {
    mid = (i + j) / 2;
    
    // Use OpenMP to run the recursive merge sort on two sections in parallel
    #pragma omp parallel sections
    {
      #pragma omp section
      margesort(a, i, mid);
      
      #pragma omp section
      margesort(a, mid + 1, j);
    }
    
    // Merge the two sorted halves
    marge(a, i, mid, mid + 1, j);
  }
}

// Sequential merge sort function (for comparison)
void margeSort_seq(int a[], int i, int j)
{
  int mid;
  if (i < j)
  {
    mid = (i + j) / 2;
    
    // Recursively divide and sort the halves
    margeSort_seq(a, i, mid);
    margeSort_seq(a, mid + 1, j);
    
    // Merge the sorted halves
    marge(a, i, mid, mid + 1, j);
  }
}

int main()
{
  int *a, *b, n = 1000;  // Declare the arrays and size of the array
  
  // Dynamically allocate memory for two arrays of size n
  a = new int[n];
  b = new int[n];
  
  // Initialize the arrays with random values
  for (int i = 0; i < n; i++)
  {
    a[i] = rand() % 1000;  // Random numbers between 0 and 999
    b[i] = a[i];  // Copy original array to 'b' for sequential sort
  }
  
  // Print the original unsorted array
  cout << "Original array:" << endl;
  for (int i = 0; i < n; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
  
  // Timing the parallel merge sort
  double start = omp_get_wtime();  // Start timer for parallel merge sort
  margesort(a, 0, n - 1);  // Perform parallel merge sort on array 'a'
  double end = omp_get_wtime();  // End timer for parallel merge sort
  
  // Timing the sequential merge sort
  double start1 = omp_get_wtime();  // Start timer for sequential merge sort
  margeSort_seq(b, 0, n - 1);  // Perform sequential merge sort on array 'b'
  double end1 = omp_get_wtime();  // End timer for sequential merge sort
  
  // Print the sorted array after parallel merge sort
  cout << "Sorted array (Parallel Merge Sort):" << endl;
  for (int p = 0; p < n; p++)
  {
    cout << a[p] << " ";  // Print each element of the sorted array
  }
  cout << endl;
  
  // Print the sorted array after sequential merge sort
  cout << "Sorted array (Sequential Merge Sort):" << endl;
  for (int p = 0; p < n; p++)
  {
    cout << b[p] << " ";  // Print each element of the sorted array
  }
  cout << endl;
  
  // Print the execution times for both parallel and sequential sorting
  cout << "Time for Parallel Merge Sort: " << (end - start) << " seconds" << endl;
  cout << "Time for Sequential Merge Sort: " << (end1 - start1) << " seconds" << endl;
  
  // Free the allocated memory for arrays
  delete[] a;
  delete[] b;

  return 0;
}


//This program is comparing the performance of **parallel** and **sequential** **merge sort** algorithms on an array of random numbers. Let's break it down simply:

### Key Concepts:

1. **Merge Sort**: 
   - This is a "divide and conquer" sorting algorithm. It splits the array into two halves, sorts each half recursively, and then merges the sorted halves back together.
   
2. **Parallel Merge Sort**: 
   - By using **OpenMP**, the program can perform the sorting of the two halves in **parallel** (at the same time), which can speed up the sorting process when there are multiple processors available.

3. **Sequential Merge Sort**:
   - This is the regular (non-parallel) version of merge sort, where the two halves are sorted one after the other.

### Step-by-Step Explanation:

#### 1. **Merge Function** (`marge`):
   - This function merges two **sorted** halves of the array into a single sorted array.
   - **Inputs**: The array `a[]`, and two pairs of indices `(i1, j1)` and `(i2, j2)` representing the two halves of the array.
   - It compares the elements from the two halves and puts the smaller one into a temporary array, then copies the elements back to the original array.

#### 2. **Parallel Merge Sort Function** (`margesort`):
   - This function divides the array into two halves and sorts each half **recursively** using **parallel** processing (using OpenMP's `#pragma omp parallel sections`).
   - Each of the two halves is sorted in parallel, and after both halves are sorted, they are merged together using the `marge` function.

#### 3. **Sequential Merge Sort Function** (`margeSort_seq`):
   - This function performs the regular **sequential** merge sort where each half is sorted one after the other, and then they are merged using the `marge` function.
   - This is used for comparison with the parallel version.

#### 4. **Main Function**:
   - **Array Initialization**: 
     - Two arrays `a[]` and `b[]` are created, both of size `n` (1000 elements).
     - The arrays are filled with random numbers between 0 and 999.
     - Array `b[]` is copied from `a[]` to be used for **sequential merge sort**.
   
   - **Printing the Original Array**: 
     - The original (unsorted) array `a[]` is printed.

   - **Timing Parallel Merge Sort**: 
     - The `margesort` function is called to perform parallel merge sort on array `a[]`.
     - The execution time for the parallel merge sort is measured using `omp_get_wtime()`.

   - **Timing Sequential Merge Sort**: 
     - The `margeSort_seq` function is called to perform sequential merge sort on array `b[]`.
     - The execution time for the sequential merge sort is also measured.

   - **Printing the Sorted Arrays**: 
     - After sorting, both the arrays `a[]` (parallel sorted) and `b[]` (sequential sorted) are printed.

   - **Printing Execution Times**: 
     - The program prints the time taken for both the parallel and sequential merge sorts.

   - **Memory Cleanup**: 
     - The memory allocated for the arrays is freed using `delete[]`.

### Example Output:
- The program will print:
  1. The **original unsorted array**.
  2. The **sorted array** after parallel merge sort.
  3. The **sorted array** after sequential merge sort.
  4. The **time** it took for both the parallel and sequential merge sort.

### Why Parallel Merge Sort?
- The **parallel merge sort** allows the array to be divided and processed in **parallel**, using multiple processors or cores if available, which can significantly **speed up the sorting** for large arrays. On the other hand, **sequential merge sort** only processes the halves one at a time, which can take longer for large arrays.

### Summary:
- The program compares **parallel** and **sequential merge sort** algorithms on an array of random numbers.
- The **parallel version** uses OpenMP to split the task into two parts that run simultaneously, potentially reducing sorting time.
- It measures and compares the **execution times** for both sorting methods and prints the sorted arrays to verify correctness.