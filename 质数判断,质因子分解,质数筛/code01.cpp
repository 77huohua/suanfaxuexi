// 按公因数计算最大组件大小
// 给定一个由不同正整数的组成的非空数组 nums
// 如果 nums[i] 和 nums[j] 有一个大于1的公因子，那么这两个数之间有一条无向边
// 返回 nums中最大连通组件的大小。

#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<int> father;
    vector<int> size;
    vector<int> fac;

    int get_max()
    {
        int ans = 1;
        for (int i = 0; i < size.size(); i++)
        {
            ans = max(ans, size[i]);
        }
        return ans;
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }
        return father[i];
    }

    void union_(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
        {
            father[fx] = fy;
            size[fy] += size[fx];
        }
    }

    void bulid()
    {
        father.resize(100010);
        for (int i = 0; i < 100010; i++)
            father[i] = i;
        size.resize(0);
        size.resize(100010, 1);
        fac.resize(0);
        fac.resize(100010, -1);
    }
    int largestComponentSize(vector<int> &nums)
    {
        bulid();
        for (int i = 0, x; i < nums.size(); i++)
        {
            x = nums[i];
            for (int j = 2; j * j <= x; j++)
            {
                if (x % j == 0)
                {
                    if (fac[j] == -1)
                    {
                        fac[j] = i;
                    }
                    else
                    {
                        union_(fac[j], i);
                    }
                    while (x % j == 0)
                    {
                        x /= j;
                    }
                }
            }
            if (x > 1)
            {
                if (fac[x] == -1)
                    fac[x] = i;
                else
                    union_(fac[x], i);
            }
        }
        return get_max();
    }
};