#include<iostream>     // Include input-output stream for basic operations
#include<stack>        // Include stack data structure for DFS implementation
#include<stdlib.h>     // For memory allocation functions
#include<omp.h>        // Include OpenMP for parallel programming

using namespace std;

// Define the 'node' class, which represents each node in the tree
class node {
public:
    node *left;  // Pointer to the left child node
    node *right; // Pointer to the right child node
    int data;    // Data stored in the node
};

// Define the DFS class, which will handle the depth-first search (DFS)
class DFS {
public:
    node* insert(node*, int);    // Function to insert a node into the binary search tree
    void DFS_Function(node*);    // Function to perform DFS traversal
};

// Function to insert a new node into the binary search tree
node* DFS::insert(node* root, int data) 
{
    // If the tree is empty, create a new node with the given data and return it
    if (root == NULL) {
        root = new node;      // Create a new node
        root->data = data;    // Assign data to the node
        root->left = root->right = NULL; // Set left and right child to NULL
        return root;
    }

    // If data is less than root's data, insert in the left subtree
    if (data < root->data)
        root->left = insert(root->left, data);  // Recursively insert in the left subtree
    else
        root->right = insert(root->right, data); // If data is greater or equal, insert in the right subtree

    return root; // Return the updated root of the tree
}

// Function to perform Depth-First Search (DFS) traversal on the tree
void DFS::DFS_Function(node* head)
{
    if (head == NULL) return; // If the tree is empty, return

    stack<node*> s;  // Create a stack to keep track of the nodes during DFS
    s.push(head);     // Push the root node into the stack

    // OpenMP parallel block to perform parallel processing
    while (!s.empty()) 
    {
        node* currNode;

        // OpenMP parallel block
        #pragma omp parallel 
        {
            #pragma omp single
            {
                // The 'single' directive ensures that only one thread pops a node from the stack
                currNode = s.top();   // Get the top node from the stack
                s.pop();              // Pop the top node from the stack
                cout << "\t" << currNode->data; // Print the current node's data

                // OpenMP task to push the right child node onto the stack in parallel
                #pragma omp task
                {
                    if (currNode->right) {   // If there is a right child
                        s.push(currNode->right);  // Push it onto the stack
                    }
                }

                // OpenMP task to push the left child node onto the stack in parallel
                #pragma omp task
                {
                    if (currNode->left) {    // If there is a left child
                        s.push(currNode->left);  // Push it onto the stack
                    }
                }
            }
        }
    }
}

// Main function to run the DFS
int main()
{
    DFS tree;         // Create an object of DFS class
    node* root = NULL; // Initialize the root of the tree as NULL
    int num, n;

    cout << "How many Nodes: ";  // Ask the user for the number of nodes
    cin >> n;  // Read the number of nodes

    // Loop to insert nodes into the tree
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the code " << (i + 1) << ": "; // Prompt the user for node data
        cin >> num;  // Read the data for the node

        root = tree.insert(root, num);  // Insert the node into the tree
    }

    // Measure the time it takes to perform DFS traversal
    double start = omp_get_wtime();  // Start timer
    tree.DFS_Function(root);         // Call the DFS function on the root node
    double end = omp_get_wtime();    // End timer

    cout << "\nExecution Time: " << (end - start) << " seconds\n";  // Output the time taken for DFS traversal

    return 0;  // Return 0 indicating successful execution
}




//Sure! Here's a simple explanation of the code:

### Overview:
This program performs a **Depth-First Search (DFS)** on a **binary search tree (BST)** and does so using **parallel computing** (OpenMP) to speed up certain tasks. It also measures how long the DFS takes to complete.

### Main Concepts:

1. **Node**:
   - A **node** is a building block of the tree. It has:
     - **Data**: A value that the node holds.
     - **Left child**: Points to the left subtree.
     - **Right child**: Points to the right subtree.

2. **Binary Search Tree (BST)**:
   - In a BST, every node follows this rule:
     - **Left child**: Contains a value **less than** its parent node.
     - **Right child**: Contains a value **greater than** its parent node.

3. **DFS (Depth-First Search)**:
   - DFS is a way to explore all the nodes in the tree. It starts at the root and goes as far as possible down one branch before backtracking and exploring other branches.

### Code Breakdown:

1. **Node Class**:
   - Represents a node in the tree, with three parts:
     - **data**: The value stored in the node.
     - **left**: Points to the left child node.
     - **right**: Points to the right child node.

2. **DFS Class**:
   - Contains two important functions:
     - **insert()**: Adds a new node to the tree based on its value. It ensures that the left child is smaller and the right child is larger.
     - **DFS_Function()**: Performs the DFS traversal on the tree. It uses a stack to keep track of nodes to visit. The stack is used because DFS explores one branch fully before going to the next branch.
       - **OpenMP parallelism**: This part is used to speed up the DFS traversal by making multiple tasks run in parallel, like checking the left and right children at the same time.

3. **Main Function**:
   - Asks the user for the number of nodes they want to add to the tree.
   - Inserts those nodes into the tree using the `insert()` function.
   - After the tree is created, it performs DFS traversal using `DFS_Function()` and measures how long it takes to finish the traversal.
   - It then prints out the execution time of the DFS traversal.

### Key Parts:

1. **Inserting Nodes**:
   - The program inserts nodes into the tree one by one. Each node’s value determines whether it goes to the left or right of the current node in the tree.

2. **Parallel DFS Traversal**:
   - Normally, DFS would visit each node one by one in a serial manner (one step after another). But here, we use **OpenMP** to make parts of the traversal parallel, meaning that it can visit both left and right children of a node at the same time.
   - **OpenMP** helps the program use multiple processors or CPU cores to do work faster.

3. **Execution Time**:
   - The program measures how long it takes to run the DFS traversal. This is useful to see how well the parallel processing helps speed up the process.

### Simple Flow of the Program:

1. You enter how many nodes you want.
2. For each node, you input a number, and the program inserts it into the binary search tree.
3. The program then starts a DFS from the root of the tree, visiting nodes in a depth-first manner (going as deep as possible into each branch before moving to another branch).
4. It uses parallel tasks to speed up the process and shows how much time the DFS took.

### Example:

- If you input the numbers `5, 3, 7, 2, 4, 6, 8`, the tree would look like this:

```
       5
      / \
     3   7
    / \  / \
   2  4 6   8
```

- Then, the program would start at the root (`5`), go down to the leftmost branch (`2`), and then move back up, exploring the right side after finishing the left side. This would be the **DFS traversal order**.

- The parallel part of the program allows some parts of this process (like checking left and right children of nodes) to happen simultaneously, making the program run faster on multi-core processors.

### In Short:
The program builds a binary search tree based on user input, performs a depth-first traversal to explore all nodes, and uses parallel processing (OpenMP) to make the DFS faster. It also measures how long the traversal takes.