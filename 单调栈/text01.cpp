// 单调栈求每个位置左右两侧，离当前位置最近、且值严格小于的位置
// 给定一个可能含有重复值的数组 arr
// 找到每一个 i 位置左边和右边离 i 位置最近且值比 arr[i] 小的位置
// 返回所有位置相应的信息。
// 输入描述：
// 第一行输入一个数字 n，表示数组 arr 的长度。
// 以下一行输入 n 个数字，表示数组的值
// 输出描述：
// 输出n行，每行两个数字 L 和 R，如果不存在，则值为 -1，下标从 0 开始。

#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1000001; // 定义数组的最大长度

int arr[MAXN];       // 存储输入的数组
int monoStack[MAXN]; // 用于实现单调栈
int ans[MAXN][2];    // 存储每个元素的左右最近较小值
int n, r;            // n是数组长度，r是栈顶指针

void compute();

int main()
{
    // 读取输入
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        compute(); // 计算每个元素的左右最近较小值
        // 输出结果
        for (int i = 0; i < n; i++)
        {
            cout << ans[i][0] << " " << ans[i][1] << endl;
        }
    }
    return 0;
}

// 计算每个元素的左右最近较小值
void compute()
{
    r = 0;   // 初始化栈顶指针
    int cur; // 临时变量，用于存储当前处理的元素索引

    // 遍历阶段：维护一个单调递增栈
    for (int i = 0; i < n; i++)
    {
        // 当栈不为空且栈顶元素对应的值大于等于当前元素时，弹出栈顶
        while (r > 0 && arr[monoStack[r - 1]] >= arr[i])
        {
            cur = monoStack[--r]; // 弹出栈顶元素
            // 记录当前元素的左右最近较小值
            ans[cur][0] = (r > 0) ? monoStack[r - 1] : -1; // 左边最近较小值
            ans[cur][1] = i;                               // 右边最近较小值
        }
        monoStack[r++] = i; // 将当前元素压入栈
    }

    // 清算阶段：处理栈中剩余的元素
    while (r > 0)
    {
        cur = monoStack[--r];                          // 弹出栈顶元素
        ans[cur][0] = (r > 0) ? monoStack[r - 1] : -1; // 左边最近较小值
        ans[cur][1] = -1;                              // 右边没有更小值
    }

    // 修正阶段：修正右侧答案，确保右侧答案是严格更小的值
    // 从右往左遍历，修正右侧边界
    for (int i = n - 2; i >= 0; i--)
    {
        if (ans[i][1] != -1 && arr[ans[i][1]] == arr[i])
        {
            // 如果右侧边界值等于当前值，则将其指向右侧边界的右侧边界
            ans[i][1] = ans[ans[i][1]][1];
        }
    }
}