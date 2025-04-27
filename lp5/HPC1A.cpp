#include <iostream>    // For input/output operations
#include <queue>       // For using the queue data structure
#include <vector>      // For dynamic array to store current level nodes
#include <omp.h>       // For OpenMP (parallel processing)

using namespace std;

// Node class for binary tree
class node {
public:
    int data;          // Value stored in the node
    node* left;        // Pointer to left child
    node* right;       // Pointer to right child
    
    // Constructor to create a new node
    node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to insert a value into the BST
node* insert(node* root, int data) {
    if (root == nullptr) {
        return new node(data);    // If tree is empty, create a new node
    }
    if (data < root->data)
        root->left = insert(root->left, data);   // Insert into left subtree
    else
        root->right = insert(root->right, data); // Insert into right subtree

    return root;    // Return the unchanged root node
}

// Function to perform Breadth-First Search (BFS) traversal in parallel
void BFS_Function(node* head) {
    if (head == nullptr) return;  // If tree is empty, exit

    queue<node*> q;     // Queue to manage nodes at each level
    q.push(head);       // Start by pushing root into the queue

    while (!q.empty()) {
        int levelSize = q.size();   // Number of nodes at current level

        vector<node*> currentLevel; // Temporary array to store nodes of current level

        // Extract all nodes of the current level into a vector
        for (int i = 0; i < levelSize; ++i) {
            node* currNode = q.front();
            q.pop();
            currentLevel.push_back(currNode);
        }

        // Parallel print all nodes in the current level
        #pragma omp parallel for
        for (int i = 0; i < currentLevel.size(); ++i) {
            cout << "\t" << currentLevel[i]->data;
        }

        // Sequentially enqueue children of all nodes
        for (int i = 0; i < currentLevel.size(); ++i) {
            if (currentLevel[i]->left)
                q.push(currentLevel[i]->left);    // Push left child if exists
            if (currentLevel[i]->right)
                q.push(currentLevel[i]->right);   // Push right child if exists
        }
    }
}

// Main function
int main() {
    node* root = nullptr;    // Initialize empty root
    int num;                 // Variable to hold user input for node value
    int n;                   // Number of nodes to insert

    cout << "How many nodes? ";  // Ask user for number of nodes
    cin >> n;

    // Loop to take input and insert into BST
    for (int i = 0; i < n; i++) {
        cout << "Enter node value " << i+1 << ": ";
        cin >> num;
        root = insert(root, num);  // Insert each number into the tree
    }

    double start = omp_get_wtime(); // Start the timer
    BFS_Function(root);             // Perform BFS traversal
    double end = omp_get_wtime();    // End the timer

    cout << "\nExecution Time: " << (end - start) << " seconds\n"; // Print time taken

    return 0; // End program
}










//Of course! Let’s explain it in **super simple language** — like I’m teaching you personally. 🧠✨

---

# 🌳 What This Program Does

- It builds a **Binary Search Tree (BST)** from numbers you enter.
- Then it **travels level-by-level** (BFS — Breadth-First Search) through the tree.
- It **prints all the values** nicely.
- It also **measures how fast** the BFS happens using **OpenMP** (parallel computing).

---

# 🧩 Step-by-Step Simple Explanation

---

## 1. **Start with basic things**

- We include `iostream`, `queue`, `vector`, and `omp.h` libraries.
- `queue` helps us go **level-by-level**.
- `vector` is used to store nodes at each level temporarily.
- `omp.h` lets the CPU **work faster** by doing many things at once.

---

## 2. **Node: Building Block of the Tree**

We have a **node class**:

```cpp
class node {
public:
    int data;
    node* left;
    node* right;
};
```

Each node has:
- a **data** value (number),
- a **left child** (smaller value),
- a **right child** (bigger value).

---

## 3. **Insert: Adding Values to the Tree**

```cpp
node* insert(node* root, int data)
```

- If the tree is **empty**, we create a new node.
- If the number is **smaller**, go to the **left side**.
- If the number is **bigger**, go to the **right side**.
- This is called making a **Binary Search Tree (BST)**.

Example:
- Insert 10 → 10 is root.
- Insert 5 → smaller → left of 10.
- Insert 15 → bigger → right of 10.

---

## 4. **BFS_Function: Travelling the Tree**

```cpp
void BFS_Function(node* head)
```

This function **visits nodes level-by-level**:

- Use a **queue**:
  - Start by putting the root node into it.
- While the queue is not empty:
  - Pull out all nodes at the **current level**.
  - Print their values **(using OpenMP to make it faster)**.
  - Then push their **children** (left and right) into the queue for the next level.

So it goes:
```
Root → Children → Grandchildren → etc.
```

---
✅ **Important:**  
- **Queue** is used to keep track of *"what to visit next"*.
- **OpenMP** is only used for *printing* nodes faster (not for pushing/popping queue — that’s risky).

---

## 5. **Main Function: Running Everything**

```cpp
int main()
```

- Ask the user: "How many nodes do you want to add?"
- For each node:
  - Ask for a number.
  - Insert it into the tree using `insert()`.
- Then:
  - Start a timer (`start`).
  - Run the `BFS_Function()` to print nodes.
  - Stop the timer (`end`).
- Finally:
  - Print how much time it took.

---

# 📋 Small Example

User input:

```
How many nodes? 3
Enter node value 1: 10
Enter node value 2: 5
Enter node value 3: 20
```

Tree looks like:

```
    10
   /   \
  5    20
```

Printed output (level by level):

```
    10    5    20
Execution Time: 0.0001 seconds
```

---

# 🏁 In short:

- Build a tree 🌳
- Visit level-by-level ➡️➡️
- Print values ✍️
- Measure time 🕒

---
Would you like me to also show a **hand-drawn diagram** of how nodes move through the queue during BFS? 📈  
It’ll be very easy to understand in 1 picture! 🎨  
Want it?  🚀
