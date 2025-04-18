// 不停删除之后剩下的字符串
// 给定一个字符串s1，如果其中含有s2字符串，就删除最左出现的那个
// 删除之后s1剩下的字符重新拼接在一起，再删除最左出现的那个
// 如此周而复始，返回最终剩下的字符串`

#include <vector>
#include <string>
#include <iostream>
using namespace std;

string s1, s2;
vector<int> next_m(1000010);
vector<int> stack1(1000010);
vector<int> stack2(1000010);
int size_m;

void nextArray(int m)
{
    next_m[0] = -1;
    if (m == 1)
    {
        return;
    }
    next_m[1] = 0;
    int i = 2, cn = 0;
    while (i < m)
    {
        if (s2[i - 1] == s2[cn])
            next_m[i++] = ++cn;
        else if (cn > 0)
            cn = next_m[cn];
        else
            next_m[i++] = 0;
    }
    return;
}

void compute()
{
    int n = s1.size(), m = s2.size(), x = 0, y = 0;
    nextArray(m);
    while (x < n)
    {
        if (s1[x] == s2[y])
        {
            stack1[size_m] = x;
            stack2[size_m] = y;
            size_m++;
            x++;
            y++;
        }
        else if (y == 0)
        {
            stack1[size_m] = x;
            stack2[size_m] = -1;
            size_m++;
            x++;
        }
        else
        {
            y = next_m[y];
        }
        if (y == m)
        {
            size_m -= m;
            y = size_m > 0 ? (stack2[size_m - 1] + 1) : 0;
        }
    }
}

int main()
{
    cin >> s1 >> s2;
    compute();
    for (int i = 0; i < size_m; i++)
        cout << s1[stack1[i]];
}