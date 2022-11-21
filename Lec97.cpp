
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// =====-===========  Minimum Spanning Tree | Kruskal's Algo ======================
/*
    Initially take all nodes to be individual components
    Parent array initialise as self,rank array all single so init with zero
    - traverse each edge
        - find both component parent
            - if not same
                - union two components [
                    find parent,
                    attach lower rank component to higher rank parent
                    update rank if two ranks equal ]
                - update weight of this edge

    - resulting weight is the final weight of MST

*/

// initialise, parent with node self, rank with zero,
void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Function to find top node of any components
int findParent(vector<int> &parent, int node)
{
    if (parent[node] == node) // top node when node become parent of itself
    {
        return node;
    }
    return findParent(parent, parent[node]);         // recusrive calls until top
    parent[node] = findParent(parent, parent[node]); // Path Compression
    // To avoid having to go from leap to top each time, simply attach last node to top parent node, for direct access to parent
}

// Function to create union of two components, by attaching parent of lesser rank to parent of greater rank
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v])
    {
        parent[u] = v; // change parent of smaller rank
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u; // change parent of smaller rank
    }
    else // ranks equal; then any
    {
        parent[v] = u; // attach to u
        rank[u]++;     // increase 'u' rank by 1
    }
}

bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2]; //{u,v,w}- compare w
}
int minimumSpanningTree(vector<vector<int>> &edges, int n)
{
    sort(edges.begin(), edges.end()); // TC: O(m log m)

    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent, rank, n); // intialise parent, rank vectors

    int minWeight = 0;
    for (int i = 0; i < edges.size(); i++) // traverse each component
    {
        // find both node parent
        int u = findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        int wt = edges[i][2];

        if (u != v) // if parent not same then union
        {
            unionSet(u, v, parent, rank);
            minWeight += wt; // when making part of MST then add weight each time
        }
    }
    // MST created, and min weight found on the way
    return minWeight;
}

int main()
{
    cout << "Enter data:" << endl;
    int v, e;
    cin >> v >> e;
    vector<vector<int>> vec;
    for (int i = 0; i < e; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        vector<int> temp;
        temp.push_back(x);
        temp.push_back(y);
        temp.push_back(z);
        vec.push_back(temp);
    }
    /*  4 4
        0 1 3
        0 3 5
        1 2 1
        2 3 8

        o/p: 9
    */
    int results = minimumSpanningTree(vec, v);

    cout << "MST: " << results << endl;

    return 0;
}