// 另一棵树的子树
// 给你两棵二叉树root和subRoot
// 检验root中是否包含和subRoot具有相同结构和节点值的子树
// 如果存在，返回true
// 否则，返回false

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void serial(TreeNode *root, vector<string> &path)
    {
        if (root == nullptr)
        {
            path.push_back("null");
        }
        else
        {
            path.push_back(to_string(root->val));
            serial(root->left, path);
            serial(root->right, path);
        }
    }

    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (root != nullptr && subRoot != nullptr)
        {
            vector<string> s1;
            vector<string> s2;
            serial(root, s1);
            serial(subRoot, s2);
            return kmp(s1, s2) != -1;
        }
        return subRoot == nullptr;
    }

    vector<int> nextArray(vector<string> &str)
    {
        int m = str.size();
        if (m == 1)
        {
            return vector<int>(1, -1);
        }
        vector<int> next(m);
        next[0] = -1;
        next[1] = 0;
        int i = 2, cn = 0;
        while (i < m)
        {
            if (str[i - 1] == str[cn])
            {
                next[i++] = ++cn;
            }
            else if (cn > 0)
            {
                cn = next[cn];
            }
            else
            {
                next[i++] = 0;
            }
        }
        return next;
    }

    int kmp(vector<string> s1, vector<string> s2)
    {
        // s1中当前比对的位置是x
        // s2中当前比对的位置是y
        int n = s1.size(), m = s2.size(), x = 0, y = 0;
        vector<int> next = nextArray(s2);
        while (x < n && y < m)
        {
            if (s1[x] == s2[y])
            {
                x++;
                y++;
            }
            else if (y == 0)
            {
                x++;
            }
            else
            {
                y = next[y];
            }
        }
        return y == m ? x - y : -1;
    }
};