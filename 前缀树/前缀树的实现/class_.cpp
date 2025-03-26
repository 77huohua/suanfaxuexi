#include <memory>
using namespace std;
#include <string>

class TrieNode
{
    public:
        int pass;
        int end;
        shared_ptr<shared_ptr<TrieNode>[]> nexts;
        TrieNode()
        {
            pass = 0;
            end = 0;
            nexts = make_shared<shared_ptr<TrieNode>[]>(26);
        }
};

class Trie
{
    private:
        shared_ptr<TrieNode> root;
    public:
        Trie()
        {
            root = make_shared<TrieNode>();
        }
        void insert(string word)
        {
            shared_ptr<TrieNode> node = root;
            node->pass++;
            for (int i = 0, path; i < word.size();i++)
            {//从左往右遍历字符
                path = word[i] - 'a';//由字符,对于成走向哪条路
                if(node->nexts[path]==nullptr)
                {
                    node->nexts[path] = make_shared<TrieNode>();
                }
                node = node->nexts[path];
                node->pass++;
            }
            node->end++;
        }

        //查询前缀树里,word单词出现了几次
        int countWordsEqualTo(string word)
        {
            shared_ptr<TrieNode> node = root;
            for (int i = 0, path; i < word.size();i++)
            {
                path = word[i] - 'a';
                if(node->nexts[path]==nullptr)
                {
                    return 0;
                }
                node = node->nexts[path];
            }
            return node->end;
        }

        //查询前缀树里,有多少单词以pre做前缀
        int countWordsStartigWith(string pre)
        {
            shared_ptr<TrieNode> node = root;
            for (int i = 0, path; i < pre.size();i++)
            {
                path = pre[i] - 'a';
                if(node->nexts[path]==nullptr)
                {
                    return 0;
                }
                node = node->nexts[path];
            }
            return node->pass;
        }

        //如果之前word插入过前缀树,那么此时删掉一次
        //如果之前word没有插入过前缀树,那么什么也不做
        void erase(string word)
        {
            if(countWordsEqualTo(word)>0)
            {
                shared_ptr<TrieNode> node = root;
                node->pass--;
                for (int i = 0, path; i < word.size();i++)
                {
                    path = word[i] - 'a';
                    if(--node->nexts[path]->pass==0)
                    {
                        node->nexts[path] = nullptr;
                        return;
                    }
                    node = node->nexts[path];
                }
                node->end--;
            }
        }
};