// 至少有K个重复字符的最长子串
// 给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串
// 要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度
// 如果不存在这样的子字符串，则返回 0。
#include <string>
#include <vector>
#include <algorithm> // 用于 std::fill 和 std::max

using namespace std;

class Solution
{
public:
    // 找到字符串中最长的子串，该子串中恰好包含 require 种不同字符，
    // 并且每种字符的出现次数都至少为 k 次
    int longestSubstring(string str, int k)
    {
        int n = str.size();
        vector<int> cnts(256, 0); // 用于统计字符出现次数
        int ans = 0;              // 最终结果

        // 尝试所有可能的 require 值（1 到 26）
        for (int require = 1; require <= 26; require++)
        {
            fill(cnts.begin(), cnts.end(), 0); // 初始化计数数组
            int collect = 0;                   // 当前窗口内不同字符的种类数
            int satisfy = 0;                   // 当前窗口内满足出现次数 >=k 的字符种类数
            int l = 0;                         // 窗口左边界

            // 滑动窗口的右边界
            for (int r = 0; r < n; r++)
            {
                cnts[str[r]]++; // 当前字符计数加 1

                // 如果当前字符是第一次进入窗口，增加种类数
                if (cnts[str[r]] == 1)
                {
                    collect++;
                }

                // 如果当前字符的计数刚好达到 k，增加满足条件的种类数
                if (cnts[str[r]] == k)
                {
                    satisfy++;
                }

                // 如果窗口内的字符种类数超过 require，移动左边界
                while (collect > require)
                {
                    // 如果左边界字符的计数是 1，减少种类数
                    if (cnts[str[l]] == 1)
                    {
                        collect--;
                    }

                    // 如果左边界字符的计数刚好是 k，减少满足条件的种类数
                    if (cnts[str[l]] == k)
                    {
                        satisfy--;
                    }

                    // 左边界字符计数减 1，并移动左边界
                    cnts[str[l]]--;
                    l++;
                }

                // 如果窗口内所有字符都满足出现次数 >=k，更新最大长度
                if (satisfy == require)
                {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};