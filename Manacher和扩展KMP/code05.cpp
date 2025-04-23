// 不重叠回文子串的最多数目
// 给定一个字符串str和一个正数k
// 你可以随意把str切分成多个子串
// 目的是找到某一种划分方案，有尽可能多的回文子串
// 并且每个回文子串都要求长度>=k、且彼此没有重合的部分
// 返回最多能划分出几个这样的回文子串

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:

    // 时间复杂度O(n)
    int maxPalindromes(string s, int k)
    {
        ss.resize(MAXN << 1);
        p.resize(MAXN << 1);
        string tmp = s;
        manacherss(s);
        int ans = 0, next = 0;
        while ((next = find(next, k)) != -1)
        {
            ans++;
        }
        return ans;
    }

    void manacherss(string &a)
    {
        n = a.size() * 2 + 1;
        for (int i = 0, j = 0; i < n; i++)
        {
            ss[i] = (i & 1) == 0 ? '#' : a[j++];
        }
    }

    // 扩展串ss从l位置开始往右寻找回文，且ss[l]一定是'#'
    // 一旦有某个中心的回文半径>k，马上返回最右下标
    // 表示找到了距离l最近且长度>=k的回文串
    // 返回的这个最右下标一定要命中'#'
    // 如果没有命中返回(最右下标+1)，让其一定命中'#'
    // 如果不存在距离l最近且长度>=k的回文串，返回-1
    int find(int l, int k)
    {
        for (int i = l, c = l, r = l, len; i < n; i++)
        {
            len = r > i ? min(p[2 * c - i], r - i) : 1;
            while (i + len < n && i - len >= l && ss[i + len] == ss[i - len])
            {
                if (++len > k)
                    return i + k + (ss[i + k] != '#' ? 1 : 0);
            }
            if (i + len > r)
            {
                r = i + len;
                c = i;
            }
            p[i] = len;
        }
        return -1;
    }

    int n;
    string ss;
    const int MAXN = 2001;
    vector<int> p;
};