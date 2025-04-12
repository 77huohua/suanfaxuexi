// 多次查询购买方法
// 一共有4种硬币，面值分别为v0、v1、v2、v3，这个永远是确定的
// 每次去购物的细节由一个数组arr来表示，每次购物都是一次查询
// arr[0] = 携带v0面值的硬币数量
// arr[1] = 携带v1面值的硬币数量
// arr[2] = 携带v2面值的硬币数量
// arr[3] = 携带v3面值的硬币数量
// arr[4] = 本次购物一定要花多少钱
// 返回每次有多少种花钱的方法
// 1 <= v0、v1、v2、v3、arr[i] <= 10^5
// 查询数量 <= 1000

#include <iostream>
#include <vector>
using namespace std;

vector<long long> dp(100010);
vector<int> value(4);
vector<int> cnt(4);
int n, s;

void init()
{
    dp[0] = 1;
    for (int i = 0; i <= 3; i++)
    {
        for (int j = value[i]; j <= 100000; j++)
        {
            dp[j] += dp[j - value[i]];
        }
    }
}

long long query()
{
    long long illegal = 0;
    // status->0001到1111
    for (int status = 1; status <= 15; status++)
    {
        long long t = s;
        int sign = -1;
        for (int j = 0; j <= 3; j++)
        {
            if (((status >> j) & 1) == 1)
            {
                t -= value[j] * (cnt[j] + 1);
                sign = -sign;
            }
        }
        if (t >= 0)
        {
            illegal += dp[(int)t] * sign;
        }
    }
    return dp[s] - illegal;
}

int main()
{
    cin >> value[0] >> value[1] >> value[2] >> value[3] >> n;
    init();
    for (int i = 1; i <= n; i++)
    {
        cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3] >> s;
        cout << query() << endl;
    }
}
