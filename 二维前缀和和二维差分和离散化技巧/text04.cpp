// 用邮票贴满网格图
// 给你一个 m * n 的二进制矩阵 grid
// 每个格子要么为 0 （空）要么为 1 （被占据）
// 给你邮票的尺寸为 stampHeight * stampWidth
// 我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：
// 覆盖所有空格子，不覆盖任何被占据的格子
// 可以放入任意数目的邮票，邮票可以相互有重叠部分
// 邮票不允许旋转，邮票必须完全在矩阵内
// 如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    private:
    //构建前缀和数组
    void build(vector<vector<int>>& m)
    {
        for (int i = 1; i < m.size();i++)
        {
            for (int j = 1; j < m[0].size();j++)
            {
                // 前缀和公式:m[i][j]+=上边+左边-左上角
                m[i][j] += m[i - 1][j] + m[i][j - 1] - m[i - 1][j - 1];
            }
        }
    }

    //计算区域和
    int sumRegion(vector<vector<int>>& sum,int a,int b,int c,int d)
    {
        //区域和公式:sum[c][d]-sum[c][b-1]-sum[a-1][d]+sum[a-1][b-1]
        return sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
    }

    //在差分矩阵中添加矩形区域的增量
    void add(vector<vector<int>>&diff,int a,int b,int c,int d)
    {
        diff[a][b] += 1;
        diff[c + 1][d + 1] += 1;
        diff[c + 1][b] -= 1;
        diff[a][d + 1] -= 1;
    }

    public:
    //判断是否可以按照指定的邮票大小进行覆盖
    bool possibleToStamp(vector<vector<int>>& grid,int h,int w)
    {
        int n = grid.size();
        if(n==0)
            return false;
        int m = grid[0].size();
        if(m==0)
            return false;
        //构建前缀和数组
        vector<vector<int>> sum(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++)
            {
                sum[i + 1][j + 1] = grid[i][j];
            }
        }
        build(sum);

        //构建差分矩阵
        vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));
        for (int a = 1, c = a + h - 1; c <= n;a++,c++)
        {
            for (int b = 1, d = b + w - 1; d <= m;b++,d++)
            {
                //计算当前区域的和
                if(sumRegion(sum,a,b,c,d)==0)
                {
                    add(diff, a, b, c, d);//在差分矩阵中添加增量
                }
            }
        }
        build(diff);//构建差分矩阵

        //检查所有格子是否都被覆盖
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++)
            {
                //如果原始矩阵是洞,但差分矩阵没有覆盖返回false
                if(grid[i][j]==0&&diff[i+1][j+1]==0)
                {
                    return false;
                }
            }
        }
        return true;
    }
};