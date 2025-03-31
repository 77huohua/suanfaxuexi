// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模

#include <vector>
using namespace std;

const int MOD = 1000000007; // 定义模数
const int MAXN = 30001;     // 定义栈的最大容量

int stack[MAXN]; // 定义一个栈，用于存储数组的索引
int r;           // 栈顶指针，初始值为 0 表示栈为空

long long sumSubarrayMins(vector<int> &arr)
{
    long long ans = 0; // 初始化结果
    r = 0;             // 重置栈顶指针

    // 遍历输入数组
    for (int i = 0; i < arr.size(); i++)
    {
        // 当栈不为空且当前元素小于等于栈顶元素对应的值时
        while (r > 0 && arr[stack[r - 1]] >= arr[i])
        {
            int cur = stack[--r];                  // 弹出栈顶元素
            int left = r == 0 ? -1 : stack[r - 1]; // 获取左侧边界
            // 计算以当前元素为最小值的子数组数量，并累加到结果中
            ans = (ans + (long long)(cur - left) * (i - cur) * arr[cur]) % MOD;
        }
        stack[r++] = i; // 将当前索引入栈
    }

    // 处理栈中剩余的元素
    while (r > 0)
    {
        int cur = stack[--r];                  // 弹出栈顶元素
        int left = r == 0 ? -1 : stack[r - 1]; // 获取左侧边界
        // 计算以当前元素为最小值的子数组数量，并累加到结果中
        ans = (ans + (long long)(cur - left) * (arr.size() - cur) * arr[cur]) % MOD;
    }

    return (int)ans; // 返回结果
}