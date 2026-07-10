// mlgb的，艹，不知道的以为劳资写数分呢

/*笔记

设f(x)=z,得x属于(2^z,2^(z+1)-1)
设g(x)=k,得x属于(z^x,z^(x+1)-1)

两层循环，暴力枚举z,g(x),求g(x)的前缀和

例: 设z=2.得x属于[4,7]
设g(x)=1,得x属于,[2,3] [2,3]交[4,7]是空集
设g(x)=2,得x属于,[4,7] [4,7]交[4,7]等于[4.7] 有g(4),g(5),g(6),g(7)=2
有S(7)=S(3)+4*2

*/

#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAXZ = 65;

// Sz[i]= x属于[2^i,2^(z+1)-1]范围上g(x)的和 Sz[2]=4*2
int Sz[MAXZ];

// i=0,1 Sz2=0,i>1,Sz2[i]=Sz[2]+Sz[3]+...+Sz[i]
int Sz2[MAXZ];

int max_z;

ll computeSz(int z)
{
    ll l = 1LL << z;
    ll r = (1LL << (z + 1)) - 1;
    ll ret = 0;
    ll zx = z;
    int gx = 1;
    while (zx <= r)
    {
        ll intervalL = zx;
        ll zx1 = zx;
        if (r / z <= zx)
        {
            zx1 = r + 1;
        }
        else
        {
            zx1 = zx * z; // z^(x+1)
        }
        ll intervalR = min(zx1 - 1, r);
        ll segL = max(l, intervalL);
        ll segR = min(r, intervalR);

        if (segL <= segR)
        {
            ll count = segR - segL + 1;
            ret = (ret + (gx % MOD) * (count % MOD)) % MOD;
        }

        if (r / z < zx)
        {
            break;
        }
        zx *= z;
        gx++;
    }
    return ret;
}

void init()
{
    Sz2[0] = Sz2[1] = 0;
    for (int z = 2; z < MAXZ; z++)
    {
        Sz[z] = computeSz(z);
        Sz2[z] = (Sz2[z - 1] + Sz[z]) % MOD;
    }
}

ll calc_suffix(ll n, int b)
{
    ll ret = 0;
    ll l = 1LL << b;
    ll bz = b;
    ll z = 1;
    while (bz <= n)
    {
        ll intervalL = bz;
        ll bz1;
        if (n / b < bz)
        {
            bz1 = n + 1;
        }
        else
        {
            bz1 = bz * b;
        }

        ll IntervalR = min(bz1 - 1, n);
        ll segL = max(intervalL, l);
        ll segR = min(IntervalR, n);

        if (segL <= segR)
        {
            ll count = segR - segL + 1;
            ret = (ret + (z % MOD) * (count % MOD)) % MOD;
        }

        if (n / b < bz)
        {
            break;
        }

        bz *= b;
        z++;
    }
    return ret;
}

ll S(ll n)
{
    if (n < 4)
        return 0;
    max_z = 0;
    while ((1LL << (max_z + 1)) <= n)
    {
        max_z++;
    }
    ll ret = Sz2[max_z - 1];
    ret = (ret + calc_suffix(n, max_z)) % MOD;
    return ret;
}

int main()
{
    int q;
    cin >> q;
    init();
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll ans = S(r) - S(l - 1) % MOD;
        cout << ((ans >= 0) ? ans : ans + MOD) << endl;
    }
}
