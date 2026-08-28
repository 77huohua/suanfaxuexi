#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> freq(n + 2, 0);

    ll maxb = 0;

    for (int i = 0; i < n; i++)
    {

        ll x;
        cin >> x;

        maxb = max(maxb, x);

        if (x <= n)
            freq[x]++; // >n 的值永远不构成约束
    }

    ll m = maxb + 1; // 唯一值得尝试的模数

    ll m0 = 0;

    while (m0 <= n && freq[m0] > 0)
        m0++;

    ll h = LLONG_MAX;

    for (ll r = 0; r <= min(maxb, (ll)n); r++)

        h = min(h, r + m * freq[r]);

    cout << min((ll)n, max(m0, h)) + 1 << endl;
}