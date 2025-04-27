#include<iostream>     // For input/output operations
#include<queue>        // For using queue data structure
#include<stdlib.h>     // Standard library (though not directly needed here)
#include<omp.h>        // OpenMP library for parallelism

using namespace std;

// Class definition for a binary tree node
class node {
public:
    node *left;        // Pointer to left child
    node *right;       // Pointer to right child
    int data;          // Data stored in node
};

// Class definition for BFS operations
class BFS {
public:
    node *insert(node*, int);   // Function to insert a node into the tree
    void BFS_Fuction(node*);    // Function to perform BFS traversal
};

// Function to insert a node into BST
node* insert(node* root, int data) 
{
    if (root == NULL) {
        root = new node;
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

// Function to perform Breadth-First Search (BFS) using OpenMP parallelism
void BFS_Fuction(node* head)
{
    queue<node*> q;    // Create a queue for BFS
    q.push(head);      // Push root node into queue
    int qsize;         // Variable to hold current queue size

    while (!q.empty())
    {
        qsize = q.size();    // Number of nodes in the current level

        // Parallel processing of nodes in the queue
        #pragma omp parallel for
        for (int i = 0; i < q.size(); i++) // Note: q.size() can change inside loop (unsafe)
        {
            node *currNode;

            // Critical section to safely pop from queue
            #pragma omp critical
            {
                currNode = q.front();  // Get front node
                q.pop();               // Remove front node
                cout << "\t" << currNode->data; // Print node data
            }

            // Critical section to safely push child nodes into queue
            #pragma omp critical
            {
                if (currNode->left) {
                    q.push(currNode->left);  // Enqueue left child
                }
                if (currNode->right) {
                    q.push(currNode->right); // Enqueue right child
                }
            }
        }
    }
}

// Main function
int main()
{
    node *root = NULL;   // Initialize root pointer
    int num;             // To store node value
    char ans;            // (Unused in the code)
    int n;               // Number of nodes

    cout << "How many nodes"; // Ask user for number of nodes
    cin >> n;

    // Insert n nodes into the BST
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the code " << i;
        cin >> num;
        root = insert(root, num);
    }

    double start = omp_get_wtime(); // Start timing
    BFS_Fuction(root);              // Perform BFS traversal
    double end = omp_get_wtime();    // End timing

    cout << "\nExecution Time: " << (end - start) << " seconds\n"; // Output execution time
}






//This code implements a basic Binary Search Tree (BST) with Breadth-First Search (BFS) traversal, using parallel processing with OpenMP to speed up the BFS traversal. Let me explain it in simpler terms:

### What the Code Does:
1. **Binary Tree Setup**: It creates a binary tree, where each node has a left and right child, as well as data.
2. **BFS Traversal**: The BFS algorithm is used to traverse the tree level by level. Each node at a certain level is processed before moving to the next level.
3. **Parallel Processing**: The BFS operation is sped up using OpenMP parallelism, which allows parts of the algorithm to run in parallel (at the same time), thus reducing execution time.

### Step-by-Step Explanation:

1. **Includes Libraries**:
   - `iostream`: For input/output operations.
   - `queue`: To use a queue (FIFO) for BFS.
   - `stdlib.h`: Standard library (not used here directly).
   - `omp.h`: OpenMP library for parallel processing.

2. **Node Structure**:
   - A `node` class is defined with three parts:
     - `left`: Pointer to the left child.
     - `right`: Pointer to the right child.
     - `data`: The value stored in the node.

3. **BFS Class**:
   - This class contains two methods:
     - `insert`: To insert a new node into the tree.
     - `BFS_Fuction`: To perform the BFS traversal and print node values.

4. **Insert Function**:
   - This function inserts a new node into the binary search tree.
   - It places values smaller than the current node to the left and larger values to the right.

5. **BFS_Fuction (Breadth-First Search)**:
   - A queue is used to process nodes level by level.
   - It starts by pushing the root node into the queue.
   - For each node, it processes its left and right children, adding them to the queue for future processing.
   - The BFS traversal is parallelized using OpenMP. It processes nodes in parallel at each level of the tree.

6. **Parallelization**:
   - The line `#pragma omp parallel for` is where the parallel processing happens. However, there’s a potential issue because `q.size()` can change while iterating through the queue (unsafe), and OpenMP doesn’t handle that well in this case.
   - The critical sections (`#pragma omp critical`) ensure that only one thread at a time can modify the queue, which avoids data corruption.

7. **Main Function**:
   - The main function first asks the user how many nodes they want to insert.
   - It then inserts these nodes into the binary search tree.
   - Finally, it calls `BFS_Fuction` to print the nodes level by level.
   - It also measures and prints the execution time of the BFS operation.

### Potential Issues:
- The loop in `BFS_Fuction` (`for (int i = 0; i < q.size(); i++)`) is problematic because `q.size()` may change during the loop (as items are popped from the queue). This can cause undefined behavior. A safer way would be to queue nodes in a separate step and then process them.

### Summary:
This program creates a binary tree, performs a breadth-first traversal to visit all the nodes, and attempts to speed up the traversal using parallel processing with OpenMP. However, there's a minor issue with how the queue is handled in parallel processing.