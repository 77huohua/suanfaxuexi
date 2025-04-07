// 乘法快速幂模版
// 求a的b次方，对p取模的结果

#include <iostream>
using namespace std;
long long a, b, p, ans = 1;
int main()
{
    cin >> a >> b >> p;
    long long a1 = a, b1 = b;
    while (b1 > 0)
    {
        if ((b1 & 1) == 1)
            ans = (ans * a1) % p;
        a1 = a1 * a1 % p;
        b1 >>= 1;
    }
    cout << a << '^' << b << " mod " << p << '=' << ans;
}