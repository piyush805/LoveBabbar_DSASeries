#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Graph BFS Traversal =================

// Function to preapre adjacency list first so that can go from a node to neighbours
void prepareAjList(unordered_map<int, list<int>> &adjList, vector<pair<int, int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}
// For sorted answer, instead of adj List use sets because they sort themselves
// Only different is that from 'push_back' there will be 'insert'
void printAdjList(unordered_map<int, list<int>> &adjList, vector<pair<int, int>> &edges)
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
vector<int> bfs(unordered_map<int, list<int>> &adjList,
                unordered_map<int, bool> &visited,
                vector<int> &ans, int node)
{
    queue<int> q; // push into queue node by node
    q.push(node);
    visited[node] = 1; // mark it as visited
    while (!q.empty())
    {
        int frontNode = q.front(); // get a node and push it into answer
        q.pop();
        ans.push_back(frontNode);
        // from the adj list push all its unvisited neightbours into queue
        for (auto i : adjList[frontNode])
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
    return ans;
}

// Function to call function to create ADJ and call bfs for eahc node
vector<int> BFS(int vertex, vector<pair<int, int>> edges)
{
    unordered_map<int, list<int>> adjList;
    vector<int> ans;
    unordered_map<int, bool> visited;
    //prepare adjlist
    prepareAjList(adjList, edges);
    // bcause possibly for disconnected components, else simply call from 0
    for (int i = 0; i < vertex; i++)
    {
        if (!visited[i])
        {
            bfs(adjList, visited, ans, i);
        }
    }
    return ans;
}
/*



*/
int main()
{
}