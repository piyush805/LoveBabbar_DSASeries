#include <iostream>
#include <vector>
using namespace std;
// ================== Trie || Longest Common Prefix =================

class TrieNode
{
public:
    char data;
    TrieNode *children[26]; // next alphabet can be any of the 26
    int childCount;
    bool isTerminal;

    TrieNode(char ch)
    {
        data = ch;
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        childCount = 0;
        isTerminal = false;
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie(char ch)
    {
        root = new TrieNode(ch);
    }
    // Function to insert a world into Trie, copy from implementing a dictionary
    void insertUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            // when the word insertion over, set the last char as terminal
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'a'; // assumption word will all be in CAPS

        TrieNode *child;
        if (root->children[index] != NULL) // this character present
        {
            child = root->children[index]; // this character is the child
        }
        else
        {
            child = new TrieNode(word[0]); // create this new charachter for 1st char of given substr
            root->children[index] = child; // root children point point to this child node formed
            root->childCount++;
        }
        // recursion for attaching to child, and rest  of substr except that 1st char that was used in this call
        insertUtil(child, word.substr(1));
    }

    void insertWord(string word)
    {
        insertUtil(root, word);
    }

    // Function to find take first word of arr and find prefix by comparing inside Trie
    // This first word is a prefix until the character from which many words diverge, i.e. its childcount should be 1
    void lcp(string str, string &ans)
    {
        for (int i = 0; i < str.length(); i++)
        {
            char ch = str[i];          // for each char of this first word
            if (root->childCount == 1) // if it has a single child (that is not many words diverge from this point)
            {
                ans.push_back(ch); // this parent ch is a prefix letter
                int index = ch - 'a';
                root = root->children[index]; // move forward root
            }
            else // many words diverge from this point onward
            {
                break;
            }

            if (root->isTerminal) // or if this first word is over(entire arr[0] is prefix)
                break;
        }
    }
};
/*
Insert all strings into a trie
//using insert Utils, whenever we insert a char, we do childCount++
//Then calls for function lcp, which finds the common prefix */
string longestCommonPrefix_Trie(vector<string> &arr, int n)
{
    Trie *t = new Trie('\0');
    for (int i = 0; i < n; i++)
    {
        t->insertWord(arr[i]); // insert all words into trie
    }
    string first = arr[0]; // take first word for finding prefix
    string ans = "";
    t->lcp(first, ans);
    return ans;
}

string longestCommonPrefix_brute(vector<string> arr, int n)
{
    string ans = "";
    for (int i = 0; i < arr[0].length(); i++) // 1st string length()
    {
        char ch = arr[0][i]; // curr char
        bool match = true;
        for (int j = 1; j < n; j++) // starting from the first string
        {
            if (arr[j].size() < i || ch != arr[j][i]) // if next string is not that long or if char not match
            {
                match = false; // then stop
                break;
            }
        }
        if (match == false)
            break;
        else                   // if(childCount != 1)
            ans.push_back(ch); // if match remained true for other string the push that char into ans
    }
    return ans;
}

int main()
{

    vector<string> arr{"coding", "codezer", "codingninja", "coders"};
    int n = 4;
    // vector<string> arr{"nil", "ninja", "night"};
    // int n = 3;
    /*      n
            |
            i
          / | \
        l   n  g
            |  |
            j  h
            |  |
            a  t
    Root has 1 child i.e. n, so n into ans, root moved to n
    n has 1 child i.e. i, so i into ans, root moved to i
    i has 3 childCount =>break
    */
    cout << "Longest common prefix: " << longestCommonPrefix_Trie(arr, n) << endl;
    return 0;
}