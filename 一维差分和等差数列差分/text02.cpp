// 一开始1~n范围上的数字都是0，一共有m个操作，每次操作为(l,r,s,e,d)
// 表示在l~r范围上依次加上首项为s、末项为e、公差为d的数列
// m个操作做完之后，统计1~n范围上所有数字的最大值和异或和

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10000005; // 定义数组的最大大小
long long arr[MAXN];       // 定义一个全局数组来存储数据
int n, m;

void set(int l, int r, int s, int e, int d);
void build();

// 主函数
int main()
{
    // 读取输入
    cin >> n >> m;

    // 初始化数组
    for (int i = 0; i < MAXN; i++)
    {
        arr[i] = 0;
    }

    // 处理每个操作
    for (int i = 0; i < m; i++)
    {
        int l, r, s, e;
        cin >> l >> r >> s >> e;
        int d = (e - s) / (r - l); // 计算斜率
        set(l, r, s, e, d);        // 调用set函数
    }

    // 构造最终数组
    build();

    // 计算最大值和异或值
    long long max_val = 0, xor_val = 0;
    for (int i = 1; i <= n; i++)
    {
        max_val = max(max_val, arr[i]); // 更新最大值
        xor_val ^= arr[i];              // 更新异或值
    }

    // 输出结果
    cout << xor_val << " " << max_val << endl;
    return 0;
}

// set函数:对数组进行增量操作
void set(int l, int r, int s, int e, int d)
{
    arr[l] += s;         // 在位置L增加s
    arr[l + 1] += d - s; // 在位置L+1增加d-s
    arr[r + 1] -= d + e; // 在位置r+1减少d+e
    arr[r + 2] += e;     // 在位置r+2增加e
}

// build函数:构建最终数组
void build()
{
    // 第一次前缀和
    for (int i = 1; i <= n; i++)
    {
        arr[i] += arr[i - 1];
    }
    // 第二次前缀和
    for (int i = 1; i <= n; i++)
    {
        arr[i] += arr[i - 1];
    }
}