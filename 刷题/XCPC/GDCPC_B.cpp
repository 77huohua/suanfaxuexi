#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// 三元组 (a,b,c) 的极差 max - min

static inline ll spreadOf(ll a, ll b, ll c)
{

    return max(a, max(b, c)) - min(a, min(b, c));
}

// 固定乘数 a，求 min over b of spread(a, b, x - a*b)

static inline ll bestForA(ll x, ll a)
{

    // b 的上界：保证 c = x - a*b >= 0（c 必须是非负整数）

    ll B = x / a;

    ll D = LLONG_MAX;

    // 尝试候选 b：越界 [a, B] 则跳过（越界意味着不满足 a<=b 或 c>=0）

    auto cand = [&](ll b)
    {
        if (b < a || b > B)
            return;

        D = min(D, spreadOf(a, b, x - a * b));
    };

    // 候选集合：两个交点的上下取整 + 区间两端点

    ll t = x / (a + 1); // 连续极小点之一：b == c，即 (a+1)*b = x

    ll s = x >= a ? (x - a) / a : -1; // 连续极小点之二：c == a，即 a*(b+1) = x

    cand(t);
    cand(t + 1); // floor / ceil

    cand(s);
    cand(s + 1);

    cand(a);
    cand(B); // 端点兜底

    return D;
}

// 单组询问：返回最小极差

static ll solve(ll x)
{

    if (x == 0)
        return 0; // (0,0,0)

    // q = floor(sqrt(x))；sqrtl 有精度风险，用两次微调修正到精确值

    ll q = (ll)sqrtl((long double)x);

    while (q * q > x)
        --q;

    while ((q + 1) * (q + 1) <= x)
        ++q;

    ll D = LLONG_MAX; // 当前已知最优答案

    for (ll a = q; a >= 1; --a)
    {

        // 下界剪枝：ceil(x/(a+1)) - a 用整数运算写为 (x+a)/(a+1) - a

        // 若该下界已 >= 当前答案 D，则更小的 a 只会给出更大的下界，直接停止

        if ((x + a) / (a + 1) - a >= D)
            break;

        D = min(D, bestForA(x, a));
    }

    return D;
}

int main()
{

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int T;

    if (!(cin >> T))
        return 0;

    while (T--)
    {

        ll x;

        cin >> x;

        cout << solve(x) << '\n';
    }

    return 0;
}