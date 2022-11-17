#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

//============= Graph | Implementation ===============

/*
Adj list can be either of the type
    -   vector<vector <int>> adj
    -   unordered_map<int, list<int>> adj
*/

class graph
{
public:
    unordered_map<int, list<int>> adj; // node, and all nodes it is connected to
    void addEdge(int u, int v, bool direction)
    {
        // create and edge from u to v
        adj[u].push_back(v);

        if (!direction)
        {
            adj[v].push_back(u);
        }
    }
    void printAdjList()
    {
        for (auto i : adj)
        {
            cout << i.first << " -> ";
            for (auto j : i.second) // print all possible i.second for each
            {
                cout << j << ", ";
            }
            cout << endl;
        }
    }
};
/*
n = 5, m = 6
i/p :   0 1
        2 3
        3 1
        1 2
        3 4
        0 4
o/p:
    4 -> 3, 0,
    3 -> 2, 1, 4,
    2 -> 3, 1,
    1 -> 0, 3, 2,
    0 -> 1, 4,

*/
int main()
{
    graph g;
    int n, m;
    cout << "No. of nodes:" << endl;
    cin >> n;
    cout << "No. of edges" << endl;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        // creating an unidrected graph
        g.addEdge(u, v, 0);
    }
    cout << endl;
    g.printAdjList();
}