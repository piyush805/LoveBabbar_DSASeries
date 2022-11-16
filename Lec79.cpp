#include <iostream>
using namespace std;
// ===================== TRIE & its implementation ==================

// Implement a dictionary:
/*
    -   insert, search, remove - Hashmap can do it in O(1)[average case]
    -


*/

class TrieNode
{
public:
    char data;
    TrieNode *children[26]; // next alphabet can be any of the 26
    bool isTerminal;
    TrieNode(char ch)
    {
        data = ch;
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        isTerminal = false;
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode('\0');
    }

    void insertUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            // when the word insertion over, set the last char as terminal
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'A'; // assumption word will all be in CAPS
        TrieNode *child;
        if (root->children[index] != NULL) // this character present
        {
            child = root->children[index]; // this character is the child
        }
        else
        {
            child = new TrieNode(word[0]); // create this new charachter for 1st char of given substr
            root->children[index] = child; // root children point point to this child node formed
        }
        // recursion for attaching to child, and rest  of substr except that 1st char that was used in this call
        insertUtil(child, word.substr(1));
    }

    void insertWord(string word)
    {
        insertUtil(root, word);
    }

    bool searchUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            return root->isTerminal;
        }
        int index = word[0] - 'A';
        TrieNode *child;
        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        else
        {
            return false;
        }
        return searchUtil(child, word.substr(1));
    }

    bool search(string word)
    {
        return searchUtil(root, word);
    }

    // Remove: find the word->go its terminal and make its false
    void removeUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            // word length 0 ==> reached terminal
            root->isTerminal = false;
            return;
        }
        int index = word[0] - 'A';
        TrieNode *child;
        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        else
        {
            cout << "Cannot remove. Word Not present." << endl;
            return;
        }
        removeUtil(child, word.substr(1));
    }
    void remove(string word)
    {
        removeUtil(root, word);
    }
};

int main()
{
    Trie *t = new Trie();
    t->insertWord("ABCD");
    cout << t->search("ABC") << endl;  // 0
    cout << t->search("ABCD") << endl; // 1 word length 0 and isTerminal = 1
    t->remove("ABCD");
    cout << t->search("ABCD") << endl; // 0 because terminal false
    cout << t->search("ABC") << endl;  // 0 because terminal false still
    t->remove("ABE");//E not present 
    return 0;
}