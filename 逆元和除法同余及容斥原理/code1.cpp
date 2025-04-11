// 连续数字逆元的线性递推
// 给定n、p，求1∼n中所有整数在模p意义下的乘法逆元
// 1 <= n <= 3 * 10^6
// n < p < 20000528
// 输入保证p为质数

#include <iostream>
#include <vector>
using namespace std;

int n, p;
vector<int> inv(3000010);

int main()
{
    cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        inv[i] = (int)(p - (long long)inv[p % i] * (p / i) % p);
    }
    for (int i = 1; i <= n; i++)
    {
        cout << inv[i] << endl;
    }
}