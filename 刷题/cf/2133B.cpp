#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 200010;
int n;
ll sum, g[MAXN];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> g[i];
        }
        sort(g + 1, g + n + 1, greater<int>());
        sum = 0;
        for (int i = 1; i <= n; i += 2)
        {
            sum += g[i];
        }
        cout << sum << endl;
    }
}