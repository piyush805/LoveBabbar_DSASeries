
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// =====-==================  Dijkstra's Algorithm ============================

/*  -   Store BFS in set/heap, because elements are to be taken on after other in greedy manner, i.e. based on current shortest dist, which set/heap arrange automatically
    -   for each neighbout of node, 
            if new distnce from this node is shorter then current dist from this node
        -       if this <dist, node> entry alrady in set 
                    then delete it
        -       update dist[] vector for that neighbour 
        -       make entry of this neighbour into set, because this (even if visited) may help find shorter dist for other nodes
 
*/
// Function to print out weighted adj list
void printAdj(unordered_map<int, list<pair<int, int>>> adj)
{
    cout << "Adj list" << endl;
    for (auto i : adj)
    {
        cout << i.first << "->";
        for (auto j : i.second)
        {
            cout << "(" << j.first << ", " << j.second << ")";
        }
        cout << endl;
    }
}
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source)
{
    unordered_map<int, list<pair<int, int>>> adj;
    // weight adj list
    for (int i = 0; i < edges; i++)
    {
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    printAdj(adj);
    // intialise dist vector with infinite for all
    vector<int> dist(vertices);
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
    }
    // source dist with itself
    dist[source] = 0;

    set<pair<int, int>> st; // DS to store which node coming next: either set/priority queue
    // Storing next node data as <distance, node value>
    // In set, elements are arranged in asc, thus elements will be arranged in sorted order of their distance, thus next element will be picked based on whose current value of dist is mini.
    // In priority queue, shortest element would go to top, hence O(1) to fetch element from top,

    // initialise for source
    st.insert(make_pair(0, source));

    while (!st.empty())
    {
        auto top = *(st.begin());     // top <dist, Node>
        int nodeDistance = top.first; // get dist of this node
        int topNode = top.second;     // node value

        st.erase(st.begin()); // remove it from set

        // for all neigbours of this topNode from adj list
        for (auto neighbour : adj[topNode])
        {
            if (nodeDistance + neighbour.second < dist[neighbour.first]) // if new distance < current dist
            {
                // check if entry of this node is available
                auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));
                if (record != st.end()) // if entry available then delete that entry
                {
                    st.erase(record);
                }
                // update/create new dist with new smaller distance
                dist[neighbour.first] = nodeDistance + neighbour.second;
                // make entry for this neighbour new distance in set again for further traversal
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }
    // when st empty, vector contains shortest of the smaller distances
    return dist;
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
    /*
        5 7
        0 1 7
        0 2 1
        0 3 2
        1 2 3
        1 3 5
        1 4 1
        3 4 7
        o/p: 0 4 1 2 5

        9 14
        0 1 4
        0 7 8
        1 2 8
        1 7 11
        2 3 7
        2 5 4
        2 8 2
        3 4 9
        3 5 14
        4 5 10
        5 6 2
        6 7 1
        6 8 6
        7  8 7

        o/p: 0 4 12 19 21 11 9 8 1 4
    */
    int s = 0;
    vector<int> ans = dijkstra(vec, v, e, s);
    cout << "Shortest distance from " << s << " to all nodes " << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}