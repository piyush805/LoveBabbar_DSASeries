
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// =====-===========  Minimum Spanning Tree | Prim's Algo ======================
/*
    -   DS to track min weights for each node, store parent from which edge there is min weight, trck whether node in MST yet or not
    -   Find minimum in weight DS to start which, parent = -1,
    -   For each next node
        -   find min in mini vector which is unvisited,
        -   mark mst true
        -   Get all its adj, if weights from this ndoe are lesser then min[] and they are not in mst yet, then update their min[] value and parent[] to curr node

    -   After this, parent array is arranged a/c to min weights among all nodes

    -   Initial node already in place, start from next and attach, which all have parent [] = this node i.e. essentially store all weight edges in vector and return ans

TC : Adj, intiialise vectors, find min for each node, = > O(n^2)

Optimise using priority queue, there min goes at top, and update min will all also go at top and can be accessed using O(1) instead of O(n)
So overal TC O(n log n)
*/


vector<pair<pair<int, int>, int>> calculatePrimeBST(int n, int m, vector<pair<pair<int, int>, int>> g)
{
    //{{u, v}, w}
    unordered_map<int, list<pair<int, int>>> adj;
    // create adj list
    for (int i = 0; i < g.size(); i++)
    {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    vector<int> key(n + 1);    // store min distances
    vector<bool> mst(n + 1);   // done stored in mst, when all become true then stop algo
    vector<int> parent(n + 1); // store the parent while traversing, update with shorter distance
    // intitialise the 3 data structure
    for (int i = 0; i <= n; i++)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        mst[i] = false;
    }
    // start from source
    int src = 1;
    key[src] = 0;     // let source node be 1
    parent[src] = -1; // parent of source market as -1

    for (int i = 0; i < n; i++) // for all nodes
    {
        // STEP I: Find minimum value in the min vector, store in u
        int mini = INT_MAX; // we have to track mini
        int u;              // we have find u
        for (int v = 1; v <= n; v++)
        {
            // if it is unvisited and key value is lesser
            if (mst[v] == false && key[v] < mini)
            {
                // then update
                u = v;         // next to visit
                mini = key[v]; // update its mini
            }
        }

        // STEP II:  u found, mark it in mst as true
        mst[u] = true; // found u, with least mini value

        // STEP III: find all its adjacent nodes and marke their parents, update min value if smaller available ffrom current node
        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if (mst[v] == false && w < key[v]) // if not in mst and weight < key value then upate key value and parent
            {
                key[v] = w;
                parent[v] = u;
            }
        }
    }
    // Now using parent array attack node pairs
    vector<pair<pair<int, int>, int>> result;
    for (int i = 2; i <= n; i++) // 2 because, 0 mapping is not there, and 1 not becase parent -1, so 1st node as it is and attach nodes 2 onwards
    {
        result.push_back({{parent[i], i}, key[i]});
    }
    return result;
}

int main()
{
    cout << "Enter data:" << endl;
    int v, e;
    cin >> v >> e;
    vector<pair<pair<int, int>, int>> vec;
    for (int i = 0; i < e; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        pair<int, int> p = make_pair(x, y);
        pair<pair<int, int>, int> p2 = make_pair(p, z);
        vec.push_back(p2);
    }
    /*
        5 14
        1 2 2
        1 4 6
        2 1 2
        2 3 3
        2 4 8
        2 5 5
        3 2 3
        3 5 7
        4 1 6
        4 2 8
        4 5 9
        5 2 5
        5 3 7
        5 4 9

        o/p:    1 2 2
                2 3 3
                1 4 6
                2 5 5
    */
    vector<pair<pair<int, int>, int>> results = calculatePrimeBST(v, e, vec);
    cout << "MST: " << endl;
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i].first.first << " " << results[i].first.second << " " << results[i].second << endl;
    }
    return 0;
}