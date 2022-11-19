#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Toplogical Sort using DFS =================
/*

    Direction Acyclic Graph(DAG)
    TopoSort is a linear ordering of vertices such that every directed edge from vertex'u' to vertex'v', vertex 'u'  comes before 'v' in the ordering. Topological Sorting for a graph is not posible if graph is not DAG. 
    
    Approach: 
    -   Traverse by DFS, and in return call, when DFS call of node returns, push that node into Stack,
    -   When entire adj traversed, the popping out elements of stack, it is in order of TopoSort

*/
// Function to create adj list of edges pairs given in 2D vector
void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adjList[u].push_back(v);
        // adjList[v].push_back(u); because this is directed graph so one way only
    }
}

// Function to run DFS and on return store node into stack
void topoSort(int node, vector<bool> &visited, stack<int> &s, unordered_map<int, list<int>> &adj)
{
    visited[node] = 1;
    for (auto neighbour : adj[node]) // for each neighbour of this node
    {
        if (!visited[neighbour])
        {
            topoSort(neighbour, visited, s, adj); // recursive call if not visited, each neihgbour becomes 'node' for next call
        }
    }
    s.push(node); // when call returns from recusrive calls upwards then push into stack
}
void printAdjList(unordered_map<int, list<int>> &adjList)
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
// Function to call DFS function and get Sort from the stack returned
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)
{
    unordered_map<int, list<int>> adj;
    prepareAdjList(adj, edges);
    // unordered_map<int,bool>visited; this is giving TLE in the question
    vector<bool> visited(v,0);
    stack<int> s;

    for (int i = 0; i < v; i++)
    {
        if (!visited[i]) // for all nodes in nodes, if unvisited
        {
            
            topoSort(i, visited, s, adj);
        }
    }
    vector<int> ans;
    while (!s.empty()) // values pushed in the return recursion, popped out in order of correct topological sort, and that is the answer
    {
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}

int main()
{
    int v = 3;
    int e = 2;
    vector<int> t1{3, 2};
    vector<int> t2{0, 1};
    vector<int> t3{0, 2};
    vector<vector<int>> adj;
    adj.push_back(t1);
    adj.push_back(t2);
    adj.push_back(t3);
    vector<int> ans = topologicalSort(adj, v, e);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}