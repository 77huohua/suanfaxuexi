// 累加和大于等于target的最短子数组长度
// 给定一个含有 n 个正整数的数组和一个正整数 target
// 找到累加和 >= target 的长度最小的子数组并返回其长度
// 如果不存在符合条件的子数组返回0

#include <vector>
#include <climits>
using namespace std;
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int ans = INT_MAX; // 初始化最短子数组长度为最大整数值
        int l = 0;         // 左指针，表示当前窗口的左边界
        int sum = 0;       // 当前窗口的和

        // 右指针遍历数组
        for (int r = 0; r < nums.size(); r++)
        {
            sum += nums[r]; // 将当前元素加入窗口和

            // 当窗口和大于等于 target 时，尝试收缩左边界
            // 以找到更短的子数组
            while (sum - nums[l] >= target)
            {
                sum -= nums[l]; // 移除左边界元素
                l++;            // 左边界向右移动
            }

            // 如果当前窗口和大于等于 target，更新最短长度
            if (sum >= target)
            {
                ans = min(ans, r - l + 1); // 更新最短长度
            }
        }

        // 如果 ans 仍为 INT_MAX，说明没有找到符合条件的子数组，返回 0
        return ans == INT_MAX ? 0 : ans;
    }
};