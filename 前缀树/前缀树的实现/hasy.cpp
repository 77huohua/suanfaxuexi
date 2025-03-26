#include <map>
#include <string>
using namespace std;

class TrieNode
{
    public:
        int pass;
        int end;
        map<int, int> nexts;
        TrieNode()
        {
            pass = 0;
            end = 0;
        }
};

class Trie
{
    private:
        TrieNode root;
    public:
        Trie()
        {
            TrieNode *temp;
            temp = new TrieNode;
        }

        void insert(string word)
        {
            TrieNode* node = &root;
            node->
        }
};