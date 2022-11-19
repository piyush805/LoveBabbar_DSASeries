#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Cycle Detection in Undirected Graph =================

/*
    Cycle present only when edges directed in cyclic manner
    Contd for cycle: When DFS call for node is running(so it is also marked visited), and it is encuntered again from a diff path which is, and that node is not parent of current node then cycle is present

*/

void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<pair<int, int>> &edges)
{
    for (int i = 0; i < edges; i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
        // adjList[v].push_back(u); because this is directed graph so one way only
    }
}

bool checkCycleDFS(int node, unordered_map<int, bool> &visited,
                   unordered_map<int, bool> &visitedDFS,
                   unordered_map<int, list<int>> &adj)
{
    visited[node] = true;
    visitedDFS[node] = true;
    // when come across a node, mark it vsisited and its call going to run so mark is DFS true as well
    for (auto neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            bool cycleDetected = checkCycleDFS(neighbour, visited, visitedDFS, adj);
            if (cycleDetected) // sent true after true in call stack
            {
                return true;
            }
        }
        else if (visitedDFS[neighbour]) // when visited[node] && visitedDFS[node] both true then cycle is present
        {
            // i.e. a visited node is in recursive call stack, its call is running anf we encounter the same node again thus cycle is present
            return true;
        }
    }
    visitedDFS[node] = false; // when a call of node finishes mark is false
    return false;             // all contd skipped thus cycle is not present
}

int detectCycleInDirectedGraph(int n, vector<pair<int, int>> &edges)
{
    unordered_map<int, list<int>> adj;
    prepareAdjList(adj, edges);
    unordered_map<int, bool> visited, visitedDFS;
    for (int i = 1; i <= n; i++) // for loop, because in directed graph node in same component may not have nay neighbours at all so recusrive call stack simply returns back so it has to be directed to next node
    {
        if (!visited[i]) //
        {
            bool cycleFound = checkCycleDFS(i, visited, visitedDFS, adj);
            if (cycleFound)
            {
                return true; // stop is cycle found at any time
            }
        }
    }
    return true;
}

int main()
{
}