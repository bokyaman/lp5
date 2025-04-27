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
