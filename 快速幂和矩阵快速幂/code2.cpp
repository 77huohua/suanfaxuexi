// 求斐波那契数列第n项

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int fib(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        if (n == 1)
        {
            return 0;
        }
        vector<vector<int>> start = {{1, 0}};
        vector<vector<int>> base = {{1, 1}, {1, 0}};
        vector<vector<int>> temp = power(base, n - 1);
        vector<vector<int>> ans = multiply(start, temp);
        return ans[0][0];
    }

    vector<vector<int>> multiply(vector<vector<int>> &a, vector<vector<int>> &b) // 矩阵相乘
    {
        int n = a.size();
        int m = b[0].size();
        int k = a[0].size();
        vector<vector<int>> ans(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int c = 0; c < k; c++)
                {
                    ans[i][j] += a[i][c] * b[c][j];
                }
            }
        }
        return ans;
    }

    // 矩阵快速幂
    vector<vector<int>> power(vector<vector<int>> &m, int p)
    {
        int n = m.size();
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            ans[i][i] = 1;
        }
        for (; p != 0; p >>= 1)
        {
            if ((p & 1) != 0)
            {
                ans = multiply(ans, m);
            }
            m = multiply(m, m);
        }
        return ans;
    }
};