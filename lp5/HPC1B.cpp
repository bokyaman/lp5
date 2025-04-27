#include <iostream>      // For standard input and output
#include <vector>        // For dynamic array (adjacency list)
#include <stack>         // For stack used in DFS
#include <omp.h>         // For OpenMP parallelization

using namespace std;

const int MAX = 100000;       // Maximum number of nodes
vector<int> graph[MAX];       // Adjacency list for the graph
bool visited[MAX];            // Array to track visited nodes

// Depth First Search (DFS) function
void dfs(int node) 
{
    stack<int> s;          // Create a stack for DFS
    s.push(node);          // Push the starting node into stack

    while (!s.empty()) 
    {
        int curr_node = s.top(); // Get the top element
        s.pop();                 // Remove the top element

        if (!visited[curr_node])  // If not visited
        {
            visited[curr_node] = true;    // Mark it as visited
            
            if (visited[curr_node])       // Redundant check (can be removed)
            {
                cout << curr_node << " ";  // Print the visited node
            }

            // Explore all adjacent nodes in parallel
            #pragma omp parallel for
            for (int i = 0; i < graph[curr_node].size(); i++) 
            {
                int adj_node = graph[curr_node][i];  // Get adjacent node
                if (!visited[adj_node]) 
                {
                    s.push(adj_node);     // Push unvisited adjacent node into stack
                }
            }
        }
    }
}

int main() 
{
    int n, m, start_node;   // n = number of nodes, m = number of edges, start_node = DFS starting point

    cout << "Enter No of Node, Edges, and start node: ";
    cin >> n >> m >> start_node;

    cout << "Enter Pair of edges: ";
    for (int i = 0; i < m; i++) 
    {
        int u, v;           // Edge between node u and v
        cin >> u >> v;
        
        // As graph is undirected, add edge in both directions
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize all nodes as unvisited in parallel
    #pragma omp parallel for
    for (int i = 0; i < n; i++) 
    {
        visited[i] = false;
    }

    // Record start time
    double start = omp_get_wtime();
    
    // Perform DFS traversal
    dfs(start_node);

    // Record end time
    double end = omp_get_wtime();

    cout << "\nExecution Time: " << (end - start) << " seconds\n";

    return 0;
}






//This program implements a graph traversal using **Depth-First Search (DFS)**, and it also uses **OpenMP** to speed up certain parts of the program by running them in parallel. Here's a simple breakdown of how it works:

### What the Code Does:

1. **Graph Representation**: The graph is represented using an adjacency list. This is a list where each node has a list of neighboring nodes (nodes directly connected by an edge).

2. **DFS Traversal**: The program performs a DFS to explore the graph, starting from a given node. It uses a stack to keep track of the nodes to visit next.

3. **Parallelization**: OpenMP is used to run some parts of the program in parallel, which can speed up the execution when there are many nodes and edges.

### Step-by-Step Explanation:

1. **Libraries**:
   - `iostream`: For standard input and output.
   - `vector`: Used to create dynamic arrays for storing the adjacency list.
   - `stack`: Used to implement the DFS algorithm (LIFO).
   - `omp.h`: Provides OpenMP functions for parallelization.

2. **Global Variables**:
   - `graph[MAX]`: An adjacency list where each `graph[i]` holds the neighbors (edges) of node `i`.
   - `visited[MAX]`: An array that tracks whether a node has been visited during DFS.

3. **DFS Function**:
   - A **stack** is used to keep track of nodes to visit.
   - The **while loop** continues until there are no more nodes left to visit. The loop processes one node at a time:
     - It pops a node from the stack.
     - If the node hasn't been visited, it marks it as visited and prints it.
     - Then, it pushes all of its unvisited neighbors (adjacent nodes) onto the stack.
   - **Parallelism**: The neighbors of a node are processed in parallel using OpenMP. This means that the program tries to process multiple neighbors at the same time, which can speed up the traversal in certain cases.

4. **Main Function**:
   - The program asks the user for:
     - `n`: The number of nodes.
     - `m`: The number of edges.
     - `start_node`: The node from which DFS should begin.
   - The user then enters the edges, which are added to the adjacency list. Since the graph is **undirected**, each edge is added in both directions.
   - Before starting DFS, it initializes the `visited` array in parallel.
   - The program starts a timer, performs the DFS traversal starting from `start_node`, and prints the nodes in the order they are visited.
   - Finally, it calculates and prints the execution time.

### Key Points:

1. **DFS Algorithm**:
   - DFS explores as far as possible along each branch before backtracking. It uses a stack to keep track of the nodes to visit.
   - The algorithm starts at a given node and visits all its neighbors recursively. Here, a stack is used instead of recursion for the DFS.

2. **Parallelization**:
   - OpenMP is used to run some parts of the program in parallel. Specifically, it allows processing the neighbors of a node in parallel, which can speed up the algorithm for large graphs.

3. **Execution Time**:
   - The program records the time taken to run the DFS algorithm and prints it at the end. This helps to understand the performance of the algorithm.

### Example:

- Suppose the graph has 5 nodes and 4 edges:
  - Nodes: 0, 1, 2, 3, 4
  - Edges: (0, 1), (1, 2), (2, 3), (3, 4)
  
  If the DFS starts at node 0, the program will print the nodes in the order they are visited (e.g., 0 1 2 3 4). The DFS will visit each node starting from node 0 and explore its neighbors recursively, using the stack to backtrack when it reaches a node with no unvisited neighbors.

### Possible Issues:
- The parallelism in OpenMP might not always improve performance, especially for small graphs. Parallelization overhead can sometimes outweigh the benefits for simpler cases.

### Summary:
This program implements DFS to traverse a graph, prints the visited nodes, and measures the execution time. It uses OpenMP for parallel processing to speed up the DFS traversal when possible. The graph is represented as an adjacency list, and the algorithm uses a stack to simulate the recursive nature of DFS.