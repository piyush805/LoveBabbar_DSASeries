#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

//===================== HASH MAP ========================
/*
Implementation:
    -   Using linked list: when want insertion, deletion, searching in const time O(N)
    -   Using BST: insertion, deletion, search in O(log n) [in build ordered map behind the scene]
*/

/*
    Bucket Array
    Hash funciton
    -   Hashcode
    -   Compression function
    -   Collision Handling
        -   Open handling
        -   Closed addressing
    -   Linear Probing a subtype
    -   Quadratic Probing

*/
int maxFrequency(vector<char> arr)
{
    unordered_map<int, int> count;
    int maxFreq = 0;
    int maxAns = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        count[arr[i]]++;
        maxFreq = max(maxFreq, count[arr[i]]);
    }
    // get maxfreq
    // then find first character with that max frequency
    for (int i = 0; i < arr.size(); i++)
    {
        if (maxFreq == count[arr[i]])
        {
            maxAns = arr[i];
            break;
        }
    }
    return maxAns;
}

int main()
{
    unordered_map<string, int> m;

    // Insert  using pair
    //  method 1
    pair<string, int> p = make_pair("babbar", 3);
    m.insert(p);

    // method 2
    pair<string, int> p2("word", 2);
    m.insert(p2);

    // method 3
    m["word1"] = 1; // new entry
    m["word1"] = 2; // updation

    // Search
    cout << m["word"] << endl;
    cout << m.at("word") << endl;
    // cout << m.at("unknown") << endl; // unkown exception - key not found

    cout << m["unknown"] << endl;    // returns 0 because it makes a new entry
    cout << m.at("unknown") << endl; // returns 0 because now entry has been created

    return 0;
}