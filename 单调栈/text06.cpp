// 最大宽度坡
// 给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]
// 这样的坡的宽度为 j - i，找出 A 中的坡的最大宽度，如果不存在，返回 0
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    static const int MAXN = 50001; // 定义栈的最大容量
    vector<int> stack;             // 用 vector 模拟栈
    int r;                         // 栈顶指针

    int maxWidthRamp(vector<int> &arr)
    {
        // 初始化栈，初始时栈中只有索引 0
        stack.clear();
        stack.push_back(0);
        r = 1; // 栈顶指针初始为 1，表示栈中有 1 个元素
        int n = arr.size();

        // 构建单调递减栈
        for (int i = 1; i < n; i++)
        {
            if (arr[stack[r - 1]] > arr[i])
            {
                stack.push_back(i); // 如果当前元素比栈顶元素小，则压入栈
                r++;
            }
        }

        int ans = 0; // 最大宽度坡的初始值为 0
        // 从数组末尾开始向左遍历
        for (int j = n - 1; j >= 0; j--)
        {
            // 如果栈不为空且栈顶元素对应的值小于等于当前值
            while (r > 0 && arr[stack[r - 1]] <= arr[j])
            {
                // 更新最大宽度坡
                ans = max(ans, j - stack[r - 1]);
                r--; // 栈顶指针减 1
            }
        }

        return ans; // 返回最大宽度坡
    }
};