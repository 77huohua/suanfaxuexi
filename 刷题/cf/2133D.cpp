#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;
using ll = long long;

int n;
const int MAXN = 200010;
ll h[MAXN];
ll dp[MAXN];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> h[i];
        }
        dp[1] = h[1];
        for (int i = 2; i <= n; i++)
        {
            dp[i] = min(dp[i - 1] + h[i] - 1, dp[i - 2] + h[i - 1] + max(0LL, h[i] - i + 1));
        }
        cout << dp[n] << endl;
    }
}