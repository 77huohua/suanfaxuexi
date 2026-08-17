#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    using ll = long long;
    int kthDigit(long long k)
    {
        if (k <= 9)
        {
            return (int)k;
        }
        int len = 1;
        k -= 9;
        while (len++)
        {
            ll start = 1;
            for (int i = 0; i < len - 2; i++)
            {
                start *= 10;
            }
            ll count = 9 * start;
            ll block_length = 10LL * len;
            ll num_length = block_length * count;
            if (k <= num_length)
            {
                ll block_idx = (k - 1) / block_length;
                ll offset = (k - 1) % block_length;
                int num_idx = offset / len;
                int digit_idx = offset % len;
                ll block_num = start + block_idx;
                ll base_val = block_num * 10LL;
                ll val = 0;
                if (block_num % 2 == 0)
                {
                    val = base_val + num_idx;
                }
                else
                {
                    val = base_val + 9 - num_idx;
                }
                return to_string(val)[digit_idx] - '0';
            }
            k -= num_length;
        }
        return 114514;
    }
};