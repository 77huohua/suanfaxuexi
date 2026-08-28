#include <iostream>

#include <algorithm>

#include <map>

#include <set>

#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 200010;

int n, m;

pair<int, int> v[MAXN];

int v1[MAXN];

int b[MAXN];

int b1[MAXN];

ll a;

set<int> skip;

map<int, ll> Pans;

void readDate()
{

    cin >> n >> a;

    for (int i = 1; i <= n; i++)
    {

        cin >> v[i].first;

        v[i].second = i;

        v1[i] = v[i].first;
    }

    cin >> m;

    for (int i = 1; i <= m; i++)
    {

        cin >> b[i];

        b1[i] = b[i];
    }
}

ll compute(ll A, ll B)
{

    int has = 0;

    ll ret = 0;

    for (int i = 1; i < n; i++)
    {

        if (v[i].first <= A)
        {

            ret -= v[i].first;

            has++;
        }

        if (has == 0 && v[i].first >= B)
        {

            skip.insert(v[i].second);
        }

        if (has > 0 && v[i].first >= B)
        {

            ret += v[i].first;

            has--;
        }
    }

    ret += (ll)has * v[n].first;

    return ret;
}

void coutAns(ll ans)
{

    sort(b + 1, b + m + 1);

    sort(v + 1, v + n + 1);

    int LastB = a + 1;

    for (int i = 1; i <= m; i++)
    {

        int B = b[i];

        auto l = lower_bound(v + 1, v + 1 + n, make_pair(LastB, 0)) - v;

        auto r = lower_bound(v + 1, v + 1 + n, make_pair(B, 0)) - v;

        for (int j = l; j < r; j++)
        {

            if (v[j].second == n)
                continue;

            if (skip.count(v[j].second))
            {

                skip.erase(v[j].second);
            }

            else

            {

                ans -= v1[v[j].second];

                auto it = skip.upper_bound(v[j].second);

                if (it != skip.end())

                {

                    ans += v1[*it];

                    skip.erase(it);
                }

                else

                {

                    ans += v1[n];
                }
            }
        }

        LastB = B;

        Pans[b[i]] = ans;
    }
}

int main()
{

    int t;

    cin >> t;

    while (t--)

    {

        Pans.clear();

        skip.clear();

        readDate();

        coutAns(compute(a, a + 1));

        for (int i = 1; i <= m; i++)
        {

            cout << Pans[b1[i]] << ' ';
        }

        cout << endl;
    }
}