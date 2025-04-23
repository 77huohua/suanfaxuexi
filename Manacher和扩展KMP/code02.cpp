// 扩展KMP模版，又称Z算法或Z函数
// 给定两个字符串a、b，求出两个数组
// b与b每一个后缀串的最长公共前缀长度，z数组
// b与a每一个后缀串的最长公共前缀长度，e数组
// 计算出要求的两个数组后，输出这两个数组的权值即可
// 对于一个数组x，i位置的权值定义为 : (i * (x[i] + 1))
// 数组权值为所有位置权值的异或和

#include <vector>
#include <string>
using namespace std;

const int MAXN = 20000010;
vector<int> z(MAXN);
vector<int> e(MAXN);

//非常像Manacher算法
void zArray(string s,int n)
{
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n;i++)
    {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i+len<n&&s[i+len]==s[len])
        {
            len++;
        }
        if(i+len>r)
        {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

//非常像Mnacher算法
void eArray(string a,string b,int n,int m)
{
    for (int i = 0, c = 0, r = 0, len; i < n;i++)
    {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i+len<n&&len<m&&a[i+len]==b[len])
        {
            len++;
        }
        if(i+len>r)
        {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}