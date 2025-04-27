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
