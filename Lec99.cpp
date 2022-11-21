
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

// =====-=========== Articulation Points in Graphs ======================
/*
4 DS:
    dis[] to store discovery time
    low[] lowest discovery time possible, if by some other routes
    map <int, bool> visited, true false
    parent[] to store parent

-   create adj
-   find Bridges function,
    -    to create and initialise these data structures along with timer which increment on visiting next node
    -   for all unvisited nodes in adj
        -    call dfs
                mark visited true
                discover and lowest disovery timer as current timer
                increment timer
                for all neighbour for this node in adjlist
                    if neighbour = parent
                        ignore
                    if unvisited
                        recursive call dfs
                        on return
                        update low[node], maybe there is shorter way pssible through child
                        Check for AP @node:
                        if (child lowest possible disc time > currNode disc time)
                            then this node is the only way to get to that child and removing it will create new component on other side so this is AP
                            AP[node] = true;
                    else (a visited neighbour)
                        check for back edge, i.e. maybe a shorter time possible though that neighbour to this node
                        update low[node]
-    return results containing what all nodes are AP

*/

void dfs(int node, int parent,
         vector<int> &disc,
         vector<int> &low,
         unordered_map<int, bool> &vis,
         unordered_map<int, list<int>> &adj,
         vector<int> &ap,
         int &timer)
{
    vis[node] = true;
    disc[node] = low[node] = timer++;
    int child = 0;                   // track child for checking parent as AP
    for (auto neighbour : adj[node]) // for all neighbours of a node in adj
    {
        if (neighbour == parent)
        {
            continue;
        }
        // call dfs for unvisited neighbour
        if (!vis[neighbour])
        {
            dfs(neighbour, node, disc, low, vis, adj, ap, timer);
            // on dfs return update low[node]
            low[node] = min(low[node], low[neighbour]);
            // Check for AP: same logic as  bridge
            // lowest discovery time of nieghbour is greater meaning it can only be reached through this node, so cutting node will create a new component
            if (low[neighbour] >= disc[node] && parent != -1)
            {
                ap[node] = 1;
            }
            child++;
        }
        else // update low of node for visited neighbours
        {
            low[node] = min(low[node], disc[neighbour]);
        }
    }
    // if more than one child for source node, then removing it will create component
    if (parent == -1 && child > 1)
    {
        ap[node] = 1;
    }
}

vector<int> findAP(vector<pair<int, int>> &edges, int n, int e)
{
    unordered_map<int, list<int>> adj;
    // create adj list
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // intialize data structures
    int timer = 0;
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    unordered_map<int, bool> vis;
    vector<int> ap(n, false);
    // call dfs for all unvisited nodes in
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfs(i, -1, disc, low, vis, adj, ap, timer);
        }
    }
    // ap contains info which node true for articulation points
    return ap;
}
int main()
{
    cout << "Enter data:" << endl;
    int v, e;
    cin >> v >> e;
    vector<pair<int, int>> vec;
    for (int i = 0; i < e; i++)
    {
        int x, y;
        cin >> x >> y;
        vec.push_back(make_pair(x, y));
    }
    /*
        5 6
        1 0
        0 4
        1 4
        2 3
        2 4
        3 4
        o/p: 4
    */
    vector<int> ap = findAP(vec, v, e);

    cout << "Articulation Points: ";
    for (int i = 0; i < v; i++)
    {
        if (ap[i] == 1)
        {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}