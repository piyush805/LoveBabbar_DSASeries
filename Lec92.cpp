#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ========  Cycle Detection in directed graph using BFS | Kahn's Algorithm ==========
/*
    Topo sort can only be present in DAG: Directed acyclic
    If we find TS in graph where cycle is present then it will not be valid
    If TS of graph is invalid then cycle is present


*/
// Function to create adj list of edges pairs given in 2D vector
void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;

        adjList[u].push_back(v); // directed graph only one way
    }
}

bool cycleDetectionUsingTopologicalSort(vector<vector<int>> &edges, int n)
{
    unordered_map<int, list<int>> adj;
    // create adjlist
    prepareAdjList(adj, edges);

    // create indegree vector
    vector<int> indegree(n);
    for (auto i : adj) // entry in adj
    {
        for (auto j : i.second) // for each neighbour of the neighbour list
        {
            indegree[j]++;
        }
    }

    // push those with indegree zero into q
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    // Front into ans
    vector<int> ans;
    int count = 0;
    while (!q.empty())
    {
        int front = q.front();

        q.pop();

        count++;

        for (auto i : adj[front]) // for each neighbour in list of this node's neighbour
        {
            cout << "i: " << i << endl;
            indegree[i]--;        // when traversal, reduce indegree of neighbours by 1
            if (indegree[i] == 0) // when any node indegree reaches zero, then its pushed into queue
            {
                q.push(i);
            }
        }
    }

    if (count == n)
    {
        return false;
    }
    return true;
}

int main()
{
    cout << "Nodes: ";
    int n;
    cin >> n;

    cout << "Edges: ";
    int e;
    cin >> e;

    vector<vector<int>> adj;
    for (int i = 0; i < e; i++)
    {
        int x, y;
        vector<int> oneEdge;
        cin >> x >> y;
        oneEdge.push_back(x);
        oneEdge.push_back(y);
        adj.push_back(oneEdge);
    }
    /*
        N= 8, E= 9
        1 2
        2 3
        2 4
        3 7
        3 8
        4 5
        5 6
        6 4
        8 7
        Cycle present

        N = 5, E = 5
        1 2
        1 3
        2 5
        3 5
        5 4
        Cycle absent
    */
    bool ans = cycleDetectionUsingTopologicalSort(adj, n);

    cout << "Cycle present? " << ans << endl;

    return 0;
}