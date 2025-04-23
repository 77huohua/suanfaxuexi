// 回文子串数量
// 返回字符串s的回文子串数量

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
string ss;
vector<int> p;

class Solution
{
public:
    void manacher(string s)
    {
        manacherss(s);
        for (int i = 0, c = 0, r = 0, len; i < n; i++)
        {
            len = r > i ? min(p[c * 2 - i], r - i) : 1;
            while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len])
            {
                len++;
            }
            if (i + len > r)
            {
                c = i;
                r = i + len;
            }
            p[i] = len;
        }
    }

    int countSubstrings(string s)
    {
        ss.resize(1010);
        p.resize(1010);
        manacher(s);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += p[i] / 2;
        }
        return ans;
    }

    void manacherss(string s)
    {
        n = s.size() * 2 + 1;
        for (int i = 0, j = 0; i < n; i++)
        {
            ss[i] = (i & 1) == 0 ? '#' : s[j++];
        }
    }
};