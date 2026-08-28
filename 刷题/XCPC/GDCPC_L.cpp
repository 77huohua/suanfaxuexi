#include <bits/stdc++.h>

using namespace std;

static char ibuf[1 << 16];

static int ipos = 0, ilen = 0;

inline int gc()
{

    if (ipos == ilen)
    {

        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);

        ipos = 0;

        if (ilen <= 0)
            return -1;
    }

    return ibuf[ipos++];
}

inline int readInt()
{

    int c = gc();

    while (c != -1 && (c < '0' || c > '9'))
        c = gc();

    int x = 0;

    while (c >= '0' && c <= '9')
    {
        x = x * 10 + (c - '0');
        c = gc();
    }

    return x;
}

int a[500005];

int main()
{

    int T = readInt();

    string out;

    out.reserve(1 << 22);

    while (T--)
    {

        int n = readInt();

        for (int i = 0; i < n; i++)
            a[i] = readInt();

        sort(a, a + n); // 升序

        int cntOdd = 0; // 前 j 个中奇数的个数

        bool maya = true; // 后手摩耶必胜？

        for (int j = 1; j <= n; j++)
        {

            cntOdd += a[j - 1] & 1;

            if ((((n - j) & 1) == 0) && (cntOdd & 1))
            {
                maya = false;
                break;
            }
        }

        out += maya ? "Maya\n" : "Insight\n";
    }

    fwrite(out.data(), 1, out.size(), stdout);

    return 0;
}