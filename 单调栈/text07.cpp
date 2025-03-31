// 去除重复字母保证剩余字符串的字典序最小
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次
// 需保证 返回结果的字典序最小
// 要求不能打乱其他字符的相对位置

#include <string>
#include <cstring>
using namespace std;

class Solution
{
public:
    static const int MAXN = 26; // 最大字符数（a-z）

    // 每种字符的词频
    int cnts[MAXN];

    // 每种字符是否已经进入栈中
    bool enter[MAXN];

    // 单调栈
    char stack[MAXN];

    int r; // 栈顶指针

    string removeDuplicateLetters(string str)
    {
        r = 0;
        memset(cnts, 0, sizeof(cnts));       // 初始化词频数组为 0
        memset(enter, false, sizeof(enter)); // 初始化进入栈标记为 false

        // 统计每个字符的词频
        for (char cha : str)
        {
            cnts[cha - 'a']++;
        }

        // 遍历字符串中的每个字符
        for (char cur : str)
        {
            // 如果当前字符没有进入栈
            if (!enter[cur - 'a'])
            {
                // 如果栈不为空，且栈顶字符大于当前字符，且栈顶字符在后面还会出现
                while (r > 0 && stack[r - 1] > cur && cnts[stack[r - 1] - 'a'] > 0)
                {
                    // 将栈顶字符标记为未进入栈
                    enter[stack[r - 1] - 'a'] = false;
                    // 弹出栈顶字符
                    r--;
                }
                // 将当前字符压入栈
                stack[r++] = cur;
                // 标记当前字符已经进入栈
                enter[cur - 'a'] = true;
            }
            // 当前字符的词频减 1
            cnts[cur - 'a']--;
        }

        // 将栈中的字符转换为字符串并返回
        return string(stack, r);
    }
};