#include <map>
#include <string>
using namespace std;

class TrieNode
{
public:
    int pass;
    int end;
    map<int, TrieNode *> nexts;
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
        TrieNode *node = &root;
        node->pass++;
        for (int i = 0, path; i < word.size(); i++)
        {
            path = word[i];
            if (node->nexts.find(path) == node->nexts.end())
            {
                node->nexts.insert(make_pair(path, new TrieNode));
            }
            node = node->nexts[path];
            node->pass++;
        }
    }

    void erase(string word)
    {
        if (countWordsEqualTo(word) > 0)
        {
            TrieNode *node = &root;
            TrieNode *next;
            node->pass--;
            for (int i = 0, path; i < word.size(); i++)
            {
                path = word[i];
                next = node->nexts[path];
                if (--next->pass == 0)
                {
                    node->nexts.erase(path);
                    return;
                }
                node = next;
            }
            node->end--;
        }
    }

    int countWordsEqualTo(string word)
    {
        TrieNode node = root;
        for (int i = 0, path; i < word.size();i++)
        {
            path = word[i];
            if(node.nexts.find(path)==node.nexts.end())
            {
                return 0;
            }
            node = *node.nexts[path];
        }
        return node.end;
    }

    int countWordsStartingWith(string pre)
    {
        TrieNode node = root;
        for (int i = 0, path; i < pre.size();i++)
        {
            path = pre[i];
            if(node.nexts.find(path)==node.nexts.end())
            {
                return 0;
            }
            node = *node.nexts[path];
        }
        return node.pass;
    }
};