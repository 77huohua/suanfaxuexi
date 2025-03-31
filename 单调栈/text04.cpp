// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积

#include <vector>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &height)
    {
        int n = height.size();
        vector<int> stack; // 使用 vector 模拟栈
        int ans = 0;       // 最大面积
        int cur, left;     // 当前元素和左边界的索引

        for (int i = 0; i < n; i++)
        {
            // 遍历每个柱状条
            while (!stack.empty() && height[stack.back()] >= height[i])
            {
                // 当栈不为空且栈顶元素的高度大于等于当前柱状条的高度时
                cur = stack.back();                           // 取出栈顶元素
                stack.pop_back();                             // 弹出栈顶元素
                left = stack.empty() ? -1 : stack.back();     // 左边界是栈顶元素的索引，如果栈为空则为 -1
                ans = max(ans, height[cur] * (i - left - 1)); // 计算当前柱状条能形成的矩形面积
            }
            stack.push_back(i); // 将当前柱状条索引压入栈
        }

        // 处理栈中剩余的柱状条
        while (!stack.empty())
        {
            cur = stack.back();                           // 取出栈顶元素
            stack.pop_back();                             // 弹出栈顶元素
            left = stack.empty() ? -1 : stack.back();     // 左边界是栈顶元素的索引，如果栈为空则为 -1
            ans = max(ans, height[cur] * (n - left - 1)); // 计算当前柱状条能形成的矩形面积
        }

        return ans; // 返回最大面积
    }
};