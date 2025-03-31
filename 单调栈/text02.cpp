// 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。

#include <vector>
using namespace std;

const int MAXN = 100001; // 定义栈的最大容量

int stack[MAXN]; // 定义一个栈，用于存储数组的索引
int r;           // 栈顶指针，初始值为 0 表示栈为空

vector<int> dailyTemperatures(vector<int> &nums)
{
    int n = nums.size();   // 获取输入数组的长度
    vector<int> ans(n, 0); // 初始化结果数组，所有元素初始为 0
    r = 0;                 // 重置栈顶指针

    for (int i = 0; i < n; i++)
    { // 遍历输入数组
        // 当栈不为空且当前元素大于栈顶元素对应的温度时
        while (r > 0 && nums[stack[r - 1]] < nums[i])
        {
            int cur = stack[--r]; // 弹出栈顶元素
            ans[cur] = i - cur;   // 计算当前索引与栈顶索引的差值，并存入结果数组
        }
        stack[r++] = i; // 将当前索引入栈
    }

    return ans; // 返回结果数组
}