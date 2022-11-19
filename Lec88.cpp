#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Cycle Detection in Undirected Graph =================
/*
    Need and extra data structure to store parent of each visited node.
    BFS Approach:
        Traverseing via adjacency list, using queue and push each unvisited elemenet and marks its parents as well.
        IF find a next node as visited, but its parent is not the current node, that means, it has a different parent node as well,
        thus there are two paths to reach that node meaning the cycle is present.


    DFS Approach:
    -   Traverse via adj list, and recursion for neighbour after neighbour, where parent becomes equal to current node in each recursion call.
    -   When we find a unvisited one then call further
    -   Else if neighbour is visited, and not a parent of current node, thus, again, there are two ways to reach the current node, so cycle is present, so sent result of true false in the recursive call stacks,
    -   if not these conditions then cycle is not present and false false false will be sent in the recursive call stack
*/
void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

bool isCycleBFS(int src, unordered_map<int, bool> &visited, unordered_map < int, list<int>> &adj)
{
    unordered_map<int, int> parent; // parent DS is created for each component because follwoing while loop works only on simgle component nodes
    parent[src] = -1;               // start node parent -1
    visited[src] = 1;

    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int front = q.front();
        q.pop();

        for (auto neighbour :adj[front])
        {
            if (visited[neighbour] == true && neighbour != parent[front])
            {
                // if neighbour is a visited node and it is not parent of this current node
                // i.e. this current node can be reached with that neighbour which has already been visited and some other parent,
                // so two paths to reach this node, thus the cycle is present
                return true;
            }
            else if (!visited[neighbour])
            {
                // push unvisited neighbours into queue
                q.push(neighbour);
                visited[neighbour] = true;
                parent[neighbour] = front; // all its neighbour reached via current node thus this is their parent
            }
        }
    }
    return false;
}

bool isCycleDFS(int node, int parent, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj)
{
    visited[node] = true;
    for (auto neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            // neighbour is the new node and, current node is the parent, in the args for recusrive call
            bool cycleDetected = isCycleDFS(neighbour, node, visited, adj);
            if (cycleDetected) // passes on true in recursive return call stack
            {
                return true;
            }
        }
        else if (neighbour != parent) // visited[neighbour] == true, because above 'if' became false
        {
            // visited neighbour but it is not parent(that is not where we came from, to this node, so there is other pathway to coming here, that means cycle is present )
            return true;
            // if this neigbour == parent then it is the node from where we came to the current node, so so far linear, so no cycle
        }
    } // if both contd prevented then cycle is not present until end and falses return in call stack
    return false;
}

string cycleDetection(vector<vector<int>> &edges, int n, int m)
{
    unordered_map<int, list<int>> adj;
    unordered_map<int, bool> visited;
    prepareAdjList(adj, edges);
    for (int i = 0; i < n; i++) // disconnected components
    {
        if (!visited[i])
        {
            bool ans = isCycleBFS(i, visited, adj);
            // bool ans = isCycleDFS(i,-1, visited, adj);
            if (ans == 1)
                return "Yes";
        }
    }
    return "No";
}
int main()
{
}