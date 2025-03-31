// K个不同整数的子数组
// 给定一个正整数数组 nums和一个整数 k，返回 nums 中 「好子数组」 的数目。
// 如果 nums 的某个子数组中不同整数的个数恰好为 k
// 则称 nums 的这个连续、不一定不同的子数组为 「好子数组 」。
// 例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。
// 子数组 是数组的 连续 部分。

#include <vector>
#include <algorithm> // 用于 std::fill

using namespace std;

class Solution
{
public:
    // 计算恰好有 K 种不同数字的子数组数量
    int subarraysWithKDistinct(vector<int> &arr, int k)
    {
        return numsOfMostKinds(arr, k) - numsOfMostKinds(arr, k - 1);
    }

private:
    static const int MAXN = 20001; // 定义一个足够大的数组大小
    int cnts[MAXN];                // 用于统计窗口内每个数字的出现次数

    // 计算最多有 K 种不同数字的子数组数量
    int numsOfMostKinds(vector<int> &arr, int k)
    {
        // 初始化计数数组
        fill(cnts, cnts + MAXN, 0);

        int ans = 0;     // 最终结果
        int collect = 0; // 当前窗口内不同数字的种类数
        int l = 0;       // 窗口的左边界

        // 滑动窗口的右边界
        for (int r = 0; r < arr.size(); r++)
        {
            // 如果当前数字是第一次进入窗口，增加种类数
            if (cnts[arr[r]] == 0)
            {
                collect++;
            }
            cnts[arr[r]]++;

            // 如果种类数超过 K，移动左边界直到种类数不超过 K
            while (collect > k)
            {
                cnts[arr[l]]--;
                if (cnts[arr[l]] == 0)
                {
                    collect--;
                }
                l++;
            }

            // 当前窗口内所有以 r 为右端点的子数组数量
            ans += r - l + 1;
        }

        return ans;
    }
};