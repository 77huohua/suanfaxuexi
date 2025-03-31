// 替换子串得到平衡字符串
// 有一个只含有 'Q', 'W', 'E', 'R' 四种字符，且长度为 n 的字符串。
// 假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。
// 给你一个这样的字符串 s，请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。
// 你可以用和「待替换子串」长度相同的 任何 其他字符串来完成替换。
// 请返回待替换子串的最小可能长度。
// 如果原字符串自身就是一个平衡字符串，则返回 0。

#include <string>
#include <vector>
#include <climits>
using namespace std;

int balancedString(string str)
{
    int n = str.length();
    vector<int> s(n);       // 将字符映射为整数值
    vector<int> cnts(4, 0); // 统计每种字符的数量

    // 将字符串中的每个字符映射为对应的整数值
    for (int i = 0; i < n; i++)
    {
        char c = str[i];
        s[i] = (c == 'W') ? 1 : (c == 'E') ? 2
                            : (c == 'R')   ? 3
                                           : 0;
        cnts[s[i]]++;
    }

    // 计算每种字符的“债务”（即需要调整的数量）
    int debt = 0;
    for (int i = 0; i < 4; i++)
    {
        if (cnts[i] < n / 4)
        {
            cnts[i] = 0; // 如果数量不足，不需要调整
        }
        else
        {
            cnts[i] = cnts[i] - n / 4; // 计算超出的数量
            debt += cnts[i];           // 累计债务
        }
    }

    // 如果债务为零，说明已经平衡，直接返回0
    if (debt == 0)
    {
        return 0;
    }

    int ans = INT_MAX; // 初始化最短长度为最大值
    for (int l = 0, r = 0; r < n; r++)
    {
        // 当前字符进入窗口，更新计数和债务
        if (--cnts[s[r]] >= 0)
        {
            debt--;
        }

        // 当债务为零时，说明窗口内的字符调整可以满足平衡条件
        while (debt == 0)
        {
            // 尝试缩小窗口，找到最小的窗口长度
            ans = min(ans, r - l + 1);
            // 移动左指针，更新计数和债务
            if (++cnts[s[l++]] > 0)
            {
                debt++;
            }
        }
    }

    return ans; // 返回最短窗口长度
}