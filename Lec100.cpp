
#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// ======= Strongly Connected Components | Kosaraju's Algorithm ============
/*
    1. Sort all nodes on basis on their finshing time. i.e. topological sort
        DFS on graph and push into stack on return of a node's dfs call

    2. Graph: transpose: all edges direction reversed: i.e. each neighbour to node map

    3. DFS on topological sort: and keep scc count with each time unvisited nodes remains for dfs call

TC: adj O(n+e),         SC: Adj O(n) linear
    dfs O(N+E)              Stack O(n)
    transpose O(N+E)        Transpose O(n)
    revDFS O(n+e)


*/
// DFS function to include node into stack on return its dfs call, topological sort
void dfs(int node, unordered_map<int, bool> &vis, stack<int> &st, unordered_map<int, list<int>> &adj)
{
    vis[node] = true;
    for (auto neighbour : adj[node])
    {
        if (!vis[neighbour]) // for unvisited neighbours of this node
        {
            dfs(neighbour, vis, st, adj);
        }
    }
    st.push(node); // push into stack on return call
}

// Same as dfs but does not push into stack
void revDfs(int node, unordered_map<int, bool> &vis, unordered_map<int, list<int>> &adj)
{
    vis[node] = true;
    for (auto neighbour : adj[node]) // for unvisited neighbours of this node
    {
        if (!vis[neighbour])
        {
            revDfs(neighbour, vis, adj);
        }
    }
}

int stronglyConnectedComponents(int v, vector<vector<int>> &edges)
{
    unordered_map<int, list<int>> adj;

    // create adj list from edges
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    // Step I: dfs calls to get topological sort in stack st
    stack<int> st;
    unordered_map<int, bool> vis;
    for (int i = 0; i < v; i++)
    {
        if (!vis[i])
        {
            dfs(i, vis, st, adj);
        }
    }

    // Step: II: Transpose the graph: transpose adj matrix
    unordered_map<int, list<int>> transpose;
    for (int i = 0; i < v; i++)
    {
        vis[i] = 0; // make visited array false again, because have to run revDfs on unvisited ones
        for (auto neighbour : adj[i])
        {
            transpose[neighbour].push_back(i); // earlier i has neighbour list, now each neghbour node  in map will have i as their neighbour in list
        }
    }

    // Step : III: RevDfs the new graph wrt to Stack top topological sort
    int count = 0;
    while (!st.empty())
    {
        int top = st.top();
        st.pop();
        if (!vis[top])
        {
            count++; // if all nodes visited in one go then there would be a single component
            // so coming back into loop with unvisited nodes still meaning its a new components which has not been reached
            revDfs(top, vis, transpose); // topological sort wise dfs calls
        }
    }
    return count;
}
int main()
{
    cout << "Enter data:" << endl;
    int v, e;
    cin >> v >> e;
    vector<vector<int>> vec;
    for (int i = 0; i < e; i++)
    {
        int x, y;
        vector<int> temp;
        cin >> x >> y;
        temp.push_back(x);
        temp.push_back(y);
        vec.push_back(temp);
    }
    /*

        5 6
        0 1
        1 2
        1 4
        2 3
        3 2
        4 0
        o/p: 2
    */
    cout << "SCC: " << stronglyConnectedComponents(v, vec) << endl;
    return 0;
}