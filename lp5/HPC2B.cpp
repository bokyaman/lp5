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
