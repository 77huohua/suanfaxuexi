// 最大矩形
// 给定一个仅包含 0 和 1 、大小为 rows * cols 的二维二进制矩阵
// 找出只包含 1 的最大矩形，并返回其面积

#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &grid)
    {
        int n = grid.size();
        if (n == 0)
            return 0;
        int m = grid[0].size();
        vector<int> height(m, 0); // 高度数组
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            // 更新高度数组
            for (int j = 0; j < m; j++)
            {
                height[j] = (grid[i][j] == '0') ? 0 : height[j] + 1;
            }
            // 计算当前行的最大矩形面积
            ans = max(ans, largestRectangleArea(height));
        }

        return ans;
    }

private:
    int largestRectangleArea(vector<int> &height)
    {
        int m = height.size();
        vector<int> stack; // 使用 vector 模拟栈
        int ans = 0;
        int cur, left;

        for (int i = 0; i < m; i++)
        {
            // 遍历每个柱状条
            while (!stack.empty() && height[stack.back()] >= height[i])
            {
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
            ans = max(ans, height[cur] * (m - left - 1)); // 计算当前柱状条能形成的矩形面积
        }

        return ans;
    }
};