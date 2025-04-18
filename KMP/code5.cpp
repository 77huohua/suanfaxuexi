// 二叉树中的链表
// 给你一棵以root为根的二叉树、一个以head为头的链表
// 在二叉树中，有很多一直向下的路径
// 如果某个路径上的数值等于以head为头的整个链表
// 返回True，否则返回False

#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
};

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    int val;
};

class Solution
{
public:
    bool isSubPath(ListNode *head, TreeNode *root)
    {
        int m = 0;
        ListNode *tmp = head;
        while (tmp != nullptr)
        {
            m++;
            tmp = tmp->next;
        }
        vector<int> s2(m);
        m = 0;
        while (head != nullptr)
        {
            s2[m++] = head->val;
            head = head->next;
        }
        vector<int> next = nextArray(s2, m);
        return find(s2, next, root, 0);
    }

    vector<int> nextArray(vector<int> str, int m)
    {
        if (m == 1)
        {
            return vector<int>(1, -1);
            ;
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

    // 二叉树来到cur节点了
    // 链表比对的位置来到i位置
    // 利用链表的next数组加速匹配
    // 返回是否能把链表整体匹配出来
    bool find(vector<int> s2, vector<int> next, TreeNode *cur, int i)
    {
        if (i == s2.size())
        {
            return 1;
        }
        if (cur == nullptr)
        {
            return 0;
        }
        // 当前来到cur节点,一开始的i是父亲节点给的
        // 但是要修正,找到配成的位置
        // 均摊下来,时间复杂度O(1)
        while (i >= 0 && cur->val != s2[i])
        {
            i = next[i];
        }
        return find(s2, next, cur->left, i + 1) || find(s2, next, cur->right, i + 1);
    }
};