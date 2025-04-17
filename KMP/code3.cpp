// 最短循环节的长度
// 给你一个字符串s，它一定是由某个循环节不断自我连接形成的
// 题目保证至少重复2次，但是最后一个循环节不一定完整
// 现在想知道s的最短循环节是多长

#include <vector>
#include <string>
#include <iostream>

std::vector<int> next(1000010);
int n;
std::string s;

void nextArray()
{
    if (n == 1)
    {
        next.push_back(-1);
        return;
    }
    next[0] = -1;
    next[1] = 0;
    int i = 2, cn = 0;
    while (i <= n)
    {
        if (s[i - 1] == s[cn])
        {
            next[i++] = ++cn;
        }
        else if (cn > 0)
        {
            cn = next[cn];
        }
        else
        {
            next[i++] = 0;
        }
    }
    return;
}

int compute()
{
    nextArray();
    return n - next[n];
}

int main()
{
    std::cin >> n >> s;
    std::cout << compute();
}