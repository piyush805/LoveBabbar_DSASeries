#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

// ============= Creating and Printing nodes and neighbours ==============

vector<vector<int>> printAdj(int m, int n, vector<vector<int>> &edges)
{
    vector<int> ans[n]; // ans will store all neighbour nodes corresponding to ith nodes in ith vector 
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][0];
        // store adjacent
        ans[u].push_back(v);
        ans[v].push_back(u); // both ways because undirected
    }
    vector<vector<int>> adj;
    // ith node then its neightbour
    for (int i = 0; i < n; i++)
    {
        adj[i].push_back(i);                    // output demand to print the node and then neighbour
        for (int j = 0; j < ans[i].size(); i++) // entering neighbours
        {
            adj[i].push_back(ans[i][j]);
        }
    }
    return adj;
}

int main()
{
    graph g;
    int n, m;
    cout << "No. of nodes:" << endl;
    cin >> n;
    cout << "No. of edges" << endl;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        // creating an unidrected graph
        g.addEdge(u, v, 0);
    }
    cout << endl;
    g.printAdjList();
}