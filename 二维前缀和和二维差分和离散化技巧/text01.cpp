// 利用二维前缀和信息迅速得到二维区域和

#include <iostream>
#include <vector>
using namespace std;

class NumMatrix{
    private:
        vector<vector<int>> sum;//用于存储前缀和的二维数组
    public:
    //构造函数,初始化前缀和数组
    NumMatrix(vector<vector<int>>&matrix)
    {
        int n = matrix.size();
        if(n==0)
            return;
        int m = matrix[0].size();
        sum.resize(n + 1, vector<int>(m + 1, 0));//初始化前缀和数组,多出一行一列用于边界处理

        //复制到sum数组中
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; i <= m;j++)
            {
                sum[i][j] = matrix[i - 1][j - 1];//将输入矩阵的元素复制到sum数组中
            }
        }

        //计算前缀和
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; j <= n;j++)
            {
                //前缀和公式:sum[i][j]=matrix[i-1][j-1]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
    }

    //计算区域和的方法
    int sumRegion(int a,int b,int c,int d)
    {
        //参数调整,因为sum数组是从1开始索引的
        a++;
        b++;
        c++;
        d++;
        // 区域和公式:sum[c][d]-sum[c][b-1]-sum[a-1][d]+sum[a-1][b-1];
        return sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
    }
};