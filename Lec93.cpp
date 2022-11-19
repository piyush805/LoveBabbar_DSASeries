#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ========  Shortest path in undirected graph ==========
/*
    create Parent array using BFS i.e from which node to reach where
    So we can extrapolate from destination node to start, using each node's parent
*/
// Function to create adj list of edges pairs given in 2D vector
void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<pair<int, int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v); // directed graph only one way
        adjList[v].push_back(u); // directed graph only one way
    }
}

vector<int> shortestPath(vector<pair<int, int>> edges, int n, int m, int s, int t)
{
    unordered_map<int, list<int>> adj;
    // adj list
    prepareAdjList(adj, edges);

    // data structure initiation
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    queue<int> q;
    q.push(s);

    visited[s] = 1;
    parent[s] = -1;

    // DFS
    while (!q.empty())
    {
        int front = q.front();
        // cout << "front: " << front << endl;
        q.pop();
        for (auto i : adj[front]) // for all neigbour list of front node
        {
            if (!visited[i]) // for any unvisited node
            {
                visited[i] = true; // each neighbour visited
                parent[i] = front; // for each neighbour this front is their parent
                
                q.push(i);
            }
        }
    }
   
    // parents map ready
    vector<int> ans;
    int currNode = t; // end
    ans.push_back(t);
    // backtrack from destination to source
    while (currNode != s) // until reach source node
    {
        
        currNode = parent[currNode]; // backtrack by parent of currNode

        ans.push_back(currNode); // this node is one step back
    }
    // reverse backtracking
    reverse(ans.begin(), ans.end()); // path is stored from destination to source so reverse it
    return ans;                      // shortest path vector
    // if need to count then count while backtracking
}

int main()
{
    cout << "Nodes: ";
    int n;
    cin >> n;

    cout << "Edges: ";
    int m;
    cin >> m;
    int s, t;

    cout << "s: ";
    cin >> s;

    cout << "t: ";
    cin >> t;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        vector<int> oneEdge;
        cin >> x >> y;
        pair<int, int> p = make_pair(x, y);
        edges.push_back(p);
    }
    /*
        N = 8, E = 9
        S = 1  T = 8
        8 9
        1 8
        1 2
        1 3
        1 4
        2 5
        5 8
        3 8
        4 6
        6 7
        7 8

       o/p: 1 3 8
    */
    vector<int> ans = shortestPath(edges, n, m, s, t);
    cout<<"Shortest path: "
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}