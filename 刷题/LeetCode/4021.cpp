#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minOperations(string s)
    {
        int ans = 0x7fffffff;
        for (int k = 0; k <= s.size() - 1; k++)
        {
            int tmp_ans = k;
            for (int i = 0; i < s.size() / 2; i++)
            {
                int idx1 = (i + k) % s.size(), idx2 = (s.size() - 1 - i + k) % s.size();
                int diff = (s[idx1] - s[idx2] + 26) % 26;
                tmp_ans += min(diff, 26 - diff);
            }
            ans = min(ans, tmp_ans);
        }
        return ans;
    }
};