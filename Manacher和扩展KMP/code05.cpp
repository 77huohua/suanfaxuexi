#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
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