#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
using ll = long long;

const int MAXN = 200010;

int a[MAXN];
int b[MAXN];
int n;
ll ans;

struct Node
{
    ll max = 0, nhv = 0;
    int maxi = 0, nhvi = 0;
} N1, N2;

ll f1(int s1, int s2, int x)
{
    return 1LL * (s1 * a[x] - s2 * b[x] - abs(a[x] - b[x]));
}

ll f2(int s1, int s2, int x)
{
    return 1LL * (s2 * a[x] - s1 * b[x] - abs(a[x] - b[x]));
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ans = 0;

        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }

        for (int i = 1; i <= n; i++)
        {
            cin >> b[i];
        }

        for (int i = 1; i <= n; i++)
        {
            ans += abs(a[i] - b[i]);
        }

        ll maxDetal = 0;

        for (int s1 : {-1, 1})
        {
            for (int s2 : {-1, 1})
            {
                N1.max = N1.nhv = N2.max = N2.nhv = LONG_MIN;
                N1.maxi = N1.nhvi = N2.maxi = N2.nhvi = -1;

                for (int i = 1; i <= n; i++)
                {

                    if (f1(s1, s2, i) > N1.max)
                    {
                        N1.nhv = N1.max;
                        N1.nhvi = N1.maxi;
                        N1.max = f1(s1, s2, i);
                        N1.maxi = i;
                    }
                    else if (f1(s1, s2, i) > N1.nhv)
                    {
                        N1.nhv = f1(s1, s2, i);
                        N1.nhvi = i;
                    }

                    if (f2(s1, s2, i) > N2.max)
                    {
                        N2.nhv = N2.max;
                        N2.nhvi = N2.maxi;
                        N2.max = f2(s1, s2, i);
                        N2.maxi = i;
                    }
                    else if (f2(s1, s2, i) > N2.nhv)
                    {
                        N2.nhv = f2(s1, s2, i);
                        N2.nhvi = i;
                    }
                }

                ll detal = 0;
                if (N1.maxi != N2.maxi)
                {
                    detal = N1.max + N2.max;
                }
                else
                {
                    detal = max(N1.max + N2.nhv, N1.nhv + N2.max);
                }
                maxDetal = max(maxDetal, detal);
            }
        }
        cout << ans + maxDetal << endl;
    }
}