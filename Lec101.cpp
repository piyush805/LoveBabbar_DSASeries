
#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// =================== Bellman Ford Algorithm ==========================
/*
For finding shortest path or Negative cycles in graph [-ve weight edges]

Dijkstra does not apply to -ve weight edges
    because there we follow greedy i.e. the immediate shortest for the next, and do not calcuate shortest path 2nd time, to compare if there can be one included -ve weight which might compensate for all +ve weights and make the shortest distance even shorter

When -ve edges present in cycle then each traversal provides with even shorter path.
Bellman Ford cannot be applied to -ve cycle as well but it can be used to detect -ve cycle

In undirected graph, it will need to be converted to directed

Algo:
    1.  Traverse edges (node - 1) times

*/
int bellford(int n, int m, int src, int dest, vector<vector<int>> &edges)
{
    vector<int> dist(n + 1, 1e9); // intialise with infinite
    dist[src] = 0;                // dist of source from itself
    for (int i = 1; i <= n; i++)  // apply formaul 1 to n
    {
        for (int j = 0; j < m; j++) // m edges
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[u] != 1e9 && (dist[u] + w < dist[v])) // if prev dist + edge  is shorter than next dist then update that distance as value of shorter distance
            {
                dist[v] = dist[u] + w;
            }
        }
    }
    bool flag = 0; // flag to check if dist will be updated in final

    for (int j = 0; j < m; j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (dist[u] != 1e9 && (dist[u] + w < dist[v]))
        {
            dist[v] = dist[u] + w;
            flag = 1;
        }
    }
    if (flag == 0) // if finally also dist not update then it is present dist
    {
        return dist[dest];
    }
    // else if updated then -ve cycle is present and shortest dist as such cannot be found as it weill be shorter in each trversal
    return -1;
}
int main()
{
    cout << "Enter data:" << endl;
    int n, m, src, dest;
    cin >> n >> m >> src >> dest;
    vector<vector<int>> vec;
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        vector<int> temp;
        cin >> x >> y >> z;
        temp.push_back(x);
        temp.push_back(y);
        temp.push_back(z);
        vec.push_back(temp);
    }
    /*
        4 4 1 4

        1 2 4
        1 3 3
        2 4 7
        3 4 -2
        o/p: shortest dist: 1
    */
    cout << "Shortest dist: " << bellford(n, m, src, dest, vec) << endl;
    return 0;
}