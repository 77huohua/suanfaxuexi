// Manacher算法模版
// 求字符串s中最长回文子串的长度

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


int n;
const int MAXN = 11000010;
string ss;
vector<int> p(MAXN << 1);

void manacherss(string a)
{
    n = a.size() * 2 + 1;
    for(int i = 0, j = 0; i < n; i++)
    {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int main()
{
    ss.resize(MAXN << 1);
}

int manacher(string str)
{
    manacherss(str);
    int max_m = 0;
    for(int i = 0, c = 0, r = 0, len; i < n;i++)
    {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i+len<n&&i-len>=0&&ss[i+len]==ss[i-len])
        {
            len++;
        }
        if(i+len>r)
        {
            r = i + len;
            c = i;
        }
        max_m = max(max_m, len);
        p[i] = len;
    }
    return max_m - 1;
}



