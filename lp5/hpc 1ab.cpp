#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <omp.h>
using namespace std;

// --------------------------- Tree Node for BFS ---------------------------
class node {
public:
    node *left;
    node *right;
    int data;
};

// --------------------------- BFS Class ---------------------------
class BFS {
public:
    node* insert(node* root, int data);
    void BFS_Function(node* head);
};

node* BFS::insert(node* root, int data) {
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

void BFS::BFS_Function(node* head) {
    if (head == NULL) return;

    queue<node*> q;
    q.push(head);
    int qsize;

    while (!q.empty()) {
        qsize = q.size();
        
        #pragma omp parallel for
        for (int i = 0; i < qsize; i++) {
            node* currNode;
            
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }

            #pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

// --------------------------- DFS Variables ---------------------------
const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

// --------------------------- DFS Function ---------------------------
void dfs(int start_node) {
    stack<int> s;
    s.push(start_node);

    while (!s.empty()) {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node]) {
            visited[curr_node] = true;
            cout << curr_node << " ";

            #pragma omp parallel for
            for (int i = 0; i < graph[curr_node].size(); i++) {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node]) {
                    #pragma omp critical
                    s.push(adj_node);
                }
            }
        }
    }
}

// --------------------------- Main Function ---------------------------
int main() {
    int choice;
    cout << "Choose Option:\n1. Parallel BFS (Tree)\n2. Parallel DFS (Graph)\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        BFS b;
        node* root = NULL;
        int n, num;
        cout << "Enter number of nodes: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter value for node " << i + 1 << ": ";
            cin >> num;
            root = b.insert(root, num);
        }

        double start = omp_get_wtime();
        b.BFS_Function(root);
        double end = omp_get_wtime();

        cout << "\nExecution Time: " << (end - start) << " seconds\n";
    }
    else if (choice == 2) {
        int n, m, start_node;
        cout << "Enter number of nodes, edges and starting node: ";
        cin >> n >> m >> start_node;

        cout << "Enter edge pairs:\n";
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        #pragma omp parallel for
        for (int i = 0; i < n; i++)
            visited[i] = false;

        double start = omp_get_wtime();
        dfs(start_node);
        double end = omp_get_wtime();

        cout << "\nExecution Time: " << (end - start) << " seconds\n";
    }
    else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
