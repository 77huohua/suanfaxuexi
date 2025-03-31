// 无重复字符的最长子串
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstring(string str)
{
    // 将字符串转换为字符数组
    vector<char> s(str.begin(), str.end());
    int n = s.size();

    // 每个字符上次出现的位置，初始值设为 -1（表示未出现过）
    int last[256];
    fill_n(last, 256, -1);

    // 最长无重复字符子串的长度
    int ans = 0;

    // 使用滑动窗口算法，l 和 r 分别表示窗口的左右边界
    for (int l = 0, r = 0; r < n; r++)
    {
        // 如果当前字符之前出现过，则将左边界移动到上次出现位置的下一个位置
        l = max(l, last[s[r]] + 1);

        // 更新最长无重复子串的长度
        ans = max(ans, r - l + 1);

        // 更新当前字符的上次出现位置
        last[s[r]] = r;
    }

    return ans;
}