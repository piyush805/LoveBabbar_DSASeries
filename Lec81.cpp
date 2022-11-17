#include <iostream>
#include <vector>
using namespace std;
// ================== Trie || Implement a Phone Directory =================

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
    Trie()
    {
        root = new TrieNode('\0');
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

    void printSuggestions(TrieNode *curr, vector<string> &temp, string prefix)
    {
        if (curr->isTerminal) // reached last char, recursive base case
        {
            temp.push_back(prefix); // temp for function to keep going even after terminal node of this, to backtrack and look for other words
        }
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            TrieNode *next = curr->children[ch - 'a'];
            if (next != NULL) // does  curr has a children
            {
                prefix.push_back(ch);
                printSuggestions(next, temp, prefix); // for that ch, print all possible words
                prefix.pop_back();                    // backtrack at end of one word to look if at some point there is some other child so go into that branch until all visited
            }
            // all words for each letter into temp 2D vector, it all goes into ans, when done upto 'z'
        }
    }

    vector<vector<string>> getSuggestions(string str)
    {
        TrieNode *prev = root; // prev pointer set initialily at root, goes forward until end of the letter
        vector<vector<string>> output;
        string prefix = "";                    // each next char of each suggestion gets added here
        for (int i = 0; i < str.length(); i++) // for each letter of the input string
        {
            char lastCh = str[i];
            prefix.push_back(lastCh); // this letter ofcourse

            // curr pointer points to a node, which is index current letter
            TrieNode *curr = prev->children[lastCh - 'a'];
            if (curr == NULL) // if prev does not point to such letter then this letter does not exist in the lists, no need to search further in the list
                break;

            vector<string> temp;
            // for each letter get all possible suggestion in contact list in 2D vector temp
            printSuggestions(curr, temp, prefix);

            output.push_back(temp); // push this temp into output
            temp.clear();           // clear temp for getting all suggestion for next entered letter,
            prev = curr;            // with prev pointing the prev letter (taking us to that branch again, so dont have to traverse from the root everytime)
        }
        return output;
    }
};

int main()
{
    vector<string> contactList{"cod", "coding", "codding", "code", "coly"};
    Trie *t = new Trie();
    // Create a try and insert all contact words into Trie
    for (int i = 0; i < contactList.size(); i++)
    {
        string str = contactList[i];
        t->insertWord(str);
    }

    string input = "cod";
    vector<vector<string>> output = t->getSuggestions(input);
    /*
        -   first input char gets pushed into prefix
        -   entire prefix gets pushed into a vector<string>temp, on reaching terminal
        -   for all suggestion for a character, temp vector gets pushed into 2D vector before checking for next character

        -   for each character of input
        -       if this letter is not next in any list
                    break
                else temp vector string,
                    get words for  'a' to 'z' recusrively what all prsent in Trie ahead of this TrieNode
                    when a word ends, insert it into vector temp
                store this temp into output
                clear the temp
            return output

    */
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 0; j < output[i].size(); j++)
        {
            cout << output[i][j] << endl;
        }
        cout << endl;
    }
    
    return 0;
}
