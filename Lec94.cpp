#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// =========  Shortest Path to reach any node in directed Acyclic Grophs DAG =============
//========Weighed edges using Toplogical sort
/*
    Topo sort can only be present in DAG: Directed acyclic
    If we find TS in graph where cycle is present then it will not be valid
    If TS of graph is invalid then cycle is present

    ToSo tells us which node lies before which node
    Thus this linear ordering can be used to reach source to destionation
*/
// Function to create adj list of edges pairs given in 2D vector

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adj;
    // adj list, weighted
    void addEdge(int u, int v, int weight)
    {
        pair<int, int> p = make_pair(v, weight);
        adj[u].push_back(p);
    }
    // print adj list
    void printAdj()
    {
        for (auto i : adj)
        {
            cout << i.first << "->";
            for (auto j : i.second)
            {
                cout << "(" << j.first << ", " << j.second << ")";
            }
            cout << endl;
        }
    }

    void dfs(int node, unordered_map<int, bool> &vis, stack<int> &topo)
    {
        vis[node] = true;
        for (auto neighbour : adj[node])
        {
            if (!vis[neighbour.first]) // visit all non visited neighbours of non neighbours
            {
                dfs(neighbour.first, vis, topo);
            }
        }
        topo.push(node); // on return push into stack, to find Topological Sort
    }

    void getShortestPath(int src, vector<int> &dist, stack<int> &topo)
    {
        dist[src] = 0; // distance of source from source itself
        while (!topo.empty())
        {
            int top = topo.top();     // using topological sort order to update dist array in that sequence
            topo.pop();               // this node
            if (dist[top] != INT_MAX) // if dist is not infinite
            {
                for (auto i : adj[top]) // for each of its neighbour
                {
                    if (dist[top] + i.second < dist[i.first]) // if new distace is shorted
                    {
                        // then update the distance in this array
                        dist[i.first] = dist[top] + i.second;
                    }
                }
            }
        }
    }
};


int main()
{
    Graph g;
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    g.printAdj(); // print adj
    int n = 6;
    unordered_map<int, bool> visited;
    stack<int> s;
    // DFS call for each univisited
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            g.dfs(i, visited, s);
        }
    }

    int src = 1; // given starting from zero
    vector<int> dist(n);
    for (int i = 0; i < n; i++) // dist vector for all is infinite initialy, each shorter distance will be updated
    {
        dist[i] = INT_MAX;
    }
    // update shortest path for each neighbour
    g.getShortestPath(src, dist, s);
    // print shortest distance array
    cout << "Answer is ";
    for (int i = 0; i < dist.size(); i++)
    {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}