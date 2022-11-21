
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

// =====-===========  Bridges in a Graph ======================
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
                            Check for bridge b/w node and this child: 
                            if (child lowest possible disc time > currNode disc time) 
                            then this node is the only way to get to that child hence bridge is present
                                so store both nodes in results
                        else (a visited neighbour)
                            check for back edge, i.e. maybe a shorter time possible though that neighbour to this node
                            update low[node]
    -    return results containing all bridge edge nodes 
    -   
*/

void dfs(int node, int parent, int &timer,
         vector<int> &disc,
         vector<int> &low,
         vector<vector<int>> &result,
         unordered_map<int, list<int>> &adj,
         unordered_map<int, bool> &vis)
{
    vis[node] = true;                 // mark this visited
    disc[node] = low[node] = timer++; // mark timers and increment timer for next
    for (auto neighbour : adj[node])  // for all neighbour of this node
    {
        if (neighbour == parent) // ignore, move to other neighbour if parent, because otherwise it will be loop between this node and neighbour
        {
            continue;
        }
        if (!vis[neighbour]) // for unvisted call dfs
        {
            dfs(neighbour, node, timer, disc, low, result, adj, vis);
            low[node] = min(low[node], low[neighbour]);//updae lowest possible time through that neighbour is maybe 
            if (low[neighbour] > disc[node]) // Bridge b/w node and neighbour
            // lowest discovery time of nieghbour is greater meaning it can only be reached through this node, so cutting this edges will create a new component
            {
                vector<int> ans;
                ans.push_back(node);
                ans.push_back(neighbour);
                result.push_back(ans);
            }
        }
        else // Back Edge:, lowest time of child was updated and lowest time of this node also need to be checked and updated; maybe there is shorter low time we do not know
        {
            low[node] = min(low[node], disc[neighbour]);
        }
    }
}
vector<vector<int>> findBridges(vector<vector<int>> &edges, int v, int e)
{
    unordered_map<int, list<int>> adj;
    // create adj list out of edges
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // intialise all data structures
    int timer = 0;
    vector<int> disc(v);
    vector<int> low(v);
    int parent = -1;
    unordered_map<int, bool> vis;
    for (int i = 0; i < v; i++)
    {
        disc[i] = -1;
        low[i] = -1;
    }
    vector<vector<int> > result;
    for (int i = 0; i < v; i++)
    {
        if (!vis[i]) // for unvisited nodes, dfs traverse and on return
        //  -   check for bridge(low[child] > disc[node]) or
        //  -   backedge(update current lowest time if child time was updated)
        {
            dfs(i, parent, timer, disc, low, result, adj, vis);
        }
    }
    // result will contain the brige edge nodes
    return result;
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
        cin >> x >> y;
        vector<int> temp;
        temp.push_back(x);
        temp.push_back(y);
        vec.push_back(temp);
    }
    /*
        5 4
        0 1
        3 1
        1 2
        3 4

        o/p:    4
                0 1
                1 2    
                1 3
                3 4
    */
    vector<vector<int>> results = findBridges(vec, v, e);

    cout << "No of bridges: " << results.size() << endl;
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i][0] << " " << results[i][1] << endl;
    }

    return 0;
}