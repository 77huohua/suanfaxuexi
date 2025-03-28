// 每个元音包含偶数次的最长子字符串
// 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度
// 每个元音字母，即 'a'，'e'，'i'，'o'，'u'
// 在子字符串中都恰好出现了偶数次。

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int move(char cha)
{
    //将字符映射到对应的索引,非元音字符返回-1
    switch (cha)
    {
        case 'a':
            return 0;
        case 'e':
            return 1;
        case 'i':
            return 2;
        case 'o':
            return 3;
        case 'u':
            return 4;
        default:
            return -1;
    }
}

int findTheLongestSubstring(string s)
{
    int n = s.length();
    //使用一个数组来记录状态的最早出现位置,初始值为-2表示未出现
    int map[32];
    fill(map, map + 32, -2);
    map[0] = -1;//初始状态(所有元音字符出现次数为偶数)的位置为-1

    int ans = 0;// 最长子字符串的长度
    int status = 0;//当前状态(元音字符的奇偶性)

    for (int i = 0; i < n;i++)
    {
        //更新状态
        int m = move(s[i]);
        if(m!=-1)
        {
            status ^= (1 << m);//翻转对应元音字符的奇偶性
        }

        //如果当前状态之前出现过,计算子字符串长度
        if(map[status]!=-2)
        {
            ans = max(ans, i - map[status]);
        }
        else
        {
            //如果当前状态未出现过,记录其位置
            map[status] = i;
        }
    }
    return ans;
}

int main()
{
    string s;
    cin >> s;//从标准输入流读取字符串
    cout << findTheLongestSubstring(s) << endl;//输出结果
    return 0;
}