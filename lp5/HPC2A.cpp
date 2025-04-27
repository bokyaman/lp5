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
