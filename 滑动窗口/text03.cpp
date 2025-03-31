// 最小覆盖子串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串
// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

#include <string>
#include <vector>

class Solution
{
public:
    std::string minWindow(std::string str, std::string tar)
    {
        // 将输入字符串转换为字符数组
        std::vector<char> s(str.begin(), str.end());
        std::vector<char> t(tar.begin(), tar.end());

        // 每种字符的欠债情况
        // cnts[i] = 负数，代表字符i有负债
        // cnts[i] = 正数，代表字符i有盈余
        std::vector<int> cnts(256, 0);
        for (char cha : t)
        {
            cnts[cha]--;
        }

        // 最小覆盖子串的长度
        int len = INT_MAX;
        // 从哪个位置开头，发现的最小覆盖子串
        int start = 0;
        // 总债务
        int debt = t.size();

        // 初始化左指针和右指针
        for (int l = 0, r = 0; r < s.size(); r++)
        {
            // 窗口右边界向右扩展，给出字符
            if (cnts[s[r]]++ < 0)
            {
                debt--;
            }

            // 如果债务为零，说明当前窗口已经覆盖了目标字符串
            if (debt == 0)
            {
                // 窗口左边界向右收缩，拿回字符
                while (cnts[s[l]] > 0)
                {
                    cnts[s[l++]]--;
                }

                // 更新最小覆盖子串的长度和起始位置
                if (r - l + 1 < len)
                {
                    len = r - l + 1;
                    start = l;
                }
            }
        }

        // 如果没有找到覆盖子串，返回空字符串；否则返回最小覆盖子串
        return len == INT_MAX ? "" : str.substr(start, len);
    }
};