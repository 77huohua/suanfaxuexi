// 二维差分模版
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1002; // 最大矩阵尺寸
vector<vector<int>> diff(MAXN, vector<int>(MAXN));
int n, q; // 矩阵大小和查询次数

// 添加矩阵区域的增量更新
void add(int a, int b, int c, int d, int k)
{
    diff[a][b] += k;
    diff[c + 1][b] -= k;
    diff[a][d + 1] -= k;
    diff[c + 1][d + 1] += k;
}

// 构建最终的矩阵
void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // 差分数组的前缀和计算
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }
}

// 清空差分数组
void clear()
{
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            diff[i][j] = 0;
        }
    }
}

int main()
{
    int a, b, c, d;
    while (cin >> n >> q)
    {
        // 初始化差分数组
        clear();
        for (int i = 0; i < q; i++)
        {
            cin >> a >> b >> c >> d;
            add(a, b, c, d, 1); // 对矩形区域进行增量更新
        }
        build(); // 构建最终的矩阵

        // 输出结果
        for (int i = 1; i <= n; i++)
        {
            cout << diff[i][1];
            for (int j = 2; j <= n; j++)
            {
                cout << ' ' << diff[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}