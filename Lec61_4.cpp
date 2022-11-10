#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// =======First non repeating character in string stream ==========
// function to print the queue
void printQueue(queue<char> q)
{
    // printing content of queue
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}
string firstNonRepeatingCharacter(string A)
{
    unordered_map<char, int> count;
    queue<char> q;
    string ans = "";
    for (int i = 0; i < A.length(); i++)
    {
        char ch = A[i];
        count[ch]++;
        q.push(ch);
        while (!q.empty())
        {
            if (count[q.front()] > 1)
            {
                // No pop until count>1 because at front is the first non repeating char of stream so far moving from left to right in stream
                q.pop();
            }
            else
            {
                ans.push_back(q.front()); // else this is first non repeating for the stream in ith iteration
                break;
            }
        }
        if (q.empty())
        {
            ans.push_back('#');
        }
    }
    return ans;
}

int main()
{

    string ans = firstNonRepeatingCharacter("dahdasdknfahsdkasnfldk");
    cout << ans << endl;

    return 0;
}