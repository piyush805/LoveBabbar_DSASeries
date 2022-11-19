#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// ================  Toplogical Sort using BFS | Kahn's Algorithm =================
/*
    Traversal, each node neighbour indegree reduce by 1, and when become 0 then pushed into answer
*/
// Function to create adj list of edges pairs given in 2D vector
void prepareAdjList(unordered_map<int, list<int>> &adjList, vector<vector<int>> &edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adjList[u].push_back(v); // directed graph only one way
    }
}

vector<int> topologicalSort_Kahn(vector<vector<int>> &edges, int v, int e)
{
    unordered_map<int, list<int>> adj;
    // create adjlist
    prepareAdjList(adj, edges);

    // create indegree vector
    vector<int> indegree(v);
    for (auto i : adj) // entry in adj
    {
        for (auto j : i.second) // for each neighbour of the neighbour list
        {
            indegree[j]++;
        }
    }

    // push those with indegree zero into q
    queue<int> q;
    for (int i = 0; i < v; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    // Front into ans
    vector<int> ans;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        ans.push_back(front);
        for (auto i : adj[front])
        {
            indegree[i]--;        // when traversal, reduce indegree of neighbours by 1
            if (indegree[i] == 0) // when any node indegree reaches zero, then its pushed into queue
            {
                q.push(i);
            }
        }
    }
    return ans;
}

int main()
{
    int v = 5;
    int e = 5;
    vector<int> t1{1, 2};
    vector<int> t2{1, 3};
    vector<int> t3{2, 5};
    vector<int> t4{3, 5};
    vector<int> t5{5, 4};
    vector<vector<int>> adj;
    adj.push_back(t1);
    adj.push_back(t2);
    adj.push_back(t3);
    adj.push_back(t4);
    adj.push_back(t5);

    vector<int> ans = topologicalSort_Kahn(adj, v, e);
    /*
    adj:
        1 -> 2, 3
        2 -> 5
        3 -> 5
        5 -> 4
    indegree vector
        1 -> 0
        2 -> 1
        3 -> 1
        4 -> 1
        5 -> 2
    Traversal, each node neighbour indegree reduce by 1, and when become 0 then pushed into answer
    */
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}