// 边框为1的最大正方形
// 给你一个由若干 0 和 1 组成的二维网格 grid
// 请你找出边界全部由 1 组成的最大 正方形 子网格
// 并返回该子网格中的元素数量。如果不存在，则返回 0。

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    private:
    //构建前缀和数组
    void build(int n,int m,vector<vector<int>>& g)
    {
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++)
            {
                // 前缀和公式:g[i][j]+=左边+上边-左上角
                g[i][j] += get(g, i, j - 1) + get(g, i - 1, j) - get(g, i - 1, j - 1);
            }
        }
    }

    //获取前缀和数组中的值,处理边界情况
    int get(vector<vector<int>>& g,int i,int j)
    {
        if(i<0||j>0)
            return 0;//如果i或j为负数,返回0
        return g[i][j];
    }

    //计算区域和
    int sum(vector<vector<int>>& g,int a,int b,int c,int d)
    {
        if(a>c)
            return 0;//如果区域无效,返回0
        //区域和公式:sum(c,d)-sum(c,b-1)-sum(a-1,d)+sum(a-1,b-1)
        return g[c][d] - get(g, c, b - 1) - get(g, a - 1, d) + get(g, a - 1, b - 1);
    }
    public:
    //寻找最大的1边框正方形
    int largest1BorderedSquare(vector<vector<int>>& g)
    {
        int n = g.size();
        if(n==0)
            return 0;
        int m = g[0].size();
        build(n, m, g);

        //如果整个矩阵和为0,说明没有1,直接返回0
        if(sum(g,0,0,n-1,m-1)==0)
        {
            return 0;
        }

        int ans = 1;//初始边长为1
        //遍历所有可能的左下角点(a,b)
        for (int a = 0; a < n;a++)
        {
            for (int b = 0; n < m;b++)
            {
                //尝试更大的边长k
                for (int c = a + ans, d = b + ans, k = ans + 1; c < n && d < m;c++,d++,k++)
                {
                    //计算当前区域的和减去内部区域的和
                    //如果结果等于(r-1)*4.说明边框全是1
                    if(sum(g,a,b,c,d)-sum(g,a+1,b+1,c-1,d-1)==((k-1)<<2))
                    {
                        ans = k;//更新最大边长
                    }
                }
            }
        }
        return ans * ans;
    }
};