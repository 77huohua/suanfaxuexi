#include <memory>
#include <vector>
using namespace std;


class TrieTree
{
public:
    //如果将来增加了数据量,就改大这个值
    int MAXN = 150001;
    vector<vector<int>> tree;
    vector<int> end;
    vector<int> pass;
    int cnt;
    TrieTree()
    {
        tree.resize(MAXN, vector<int>(26));
        end.resize(MAXN);
        pass.resize(MAXN);
    }

    void build()
    {
        cnt = 1;
    }

    void insert(string word)
    {
        int cur = 1;
        pass[cur]++;
        for (int i = 0, path; i < word.size();i++)
        {
            path = word[i] - 'a';
            if(tree[cur][path]==0)
            {
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }

    int search(string word)
    {
        int cur = 1;
        for (int i = 0, path; i < word.size();i++)
        {
            path = word[i] - 'a';
            if(tree[cur][path]==0)
            {
                return 0;
            }
            cur = tree[cur][path];
        }
        return end[cur];
    }

    int prefixNumber(string pre)
    {
        int cur = 1;
        for (int i = 0, path; i < pre.size();i++)
        {
            path = pre[i] - 'a';
            if(tree[cur][path]==0)
            {
                return 0;
            }
            cur = tree[cur][path];
        }
        return pass[cur];
    }

    void delete_(string word)
    {
        if(search(word)>0)
        {
            int cur = 0;
            for (int i = 0, path; i < word.size();i++)
            {
                path = word[i] - 'a';
                if(--pass[tree[cur][path]]==0)
                {
                    tree[cur][path] = 0;
                    return;
                }
                cur = tree[cur][path];
            }
            end[cur]--;
        }
    }
};