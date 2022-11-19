#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Graph DFS Traversal =================
// TC = O(1), SC = O(1)
// For sorted answer, instead of adj List use sets because they sort themselves
// Only different is that from 'push_back' there will be 'insert'
void prepareAjList(unordered_map<int, list<int>> &adjList, vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

void dfs(int node, unordered_map<int, bool> &visited,
         unordered_map<int, list<int>> &adj,
         vector<int> &component)
{
    component.push_back(node); // that node print
    visited[node] = 1;         // mark visited
    for (auto i : adj[node])   // for each node in adj list
    {
        if (!visited[i]) // if not visited, call recursive for it
        {
            dfs(i, visited, adj, component);
        }
    }
}

// For sorted answer, instead of adj List use sets because they sort themselves
// Only different is that from 'push_back' there will be 'insert'
void printAdjList(unordered_map<int, list<int>> &adjList,
                  vector<pair<int, int>> &edges)
{
    for (auto i : adjList)
    {
        cout << i.first << "->";
        for (auto j : i.second)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> DFS(int V, int E, vector<vector<int>> &edges)
{

    vector<vector<int>> ans;
    unordered_map<int, list<int>> adjList;
    unordered_map<int, bool> visited;
    prepareAjList(adjList, edges);
    for (int i = 0; i < V; i++) // for possible disconnected components
    {
        if (!visited[i])
        {
            vector<int> component;               // for connected one this will run only once
            dfs(i, visited, adjList, component); // because in recusrive call all will become visited
            ans.push_back(component);
        }
    }
    return ans;
}

int main()
{
    
}
