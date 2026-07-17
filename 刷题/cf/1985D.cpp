#include <iostream>
using namespace std;

const int MAXN = 200010;

int a[MAXN];
int b[MAXN];
int sum[MAXN];
const int MAXNODE = MAXN * 22;

int ch[MAXNODE][2];
int cntt;

void init()
{
    ch[0][0] = ch[0][1] = -1;
    cntt = 0;
}

void insert(int x)
{
    int now = 0;
    for (int i = 19; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        if (ch[now][bit] == -1)
        {
            cntt++;
            ch[cntt][0] = ch[cntt][1] = -1;
            ch[now][bit] = cntt;
        }
        now = ch[now][bit];
    }
}

int queryMax(int val)
{
    int now = 0;
    int result = 0;
    for (int i = 19; i >= 0; i--)
    {
        int bit = (val >> i) & 1, want = bit ^ 1;
        if (ch[now][want] != -1)
        {
            result |= (1 << i);
            now = ch[now][want];
        }
        else
        {
            now = ch[now][bit];
        }
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        cin >> a[i];
    }

    sum[0] = 0;
    for (int i = 1; i < n; i++)
    {
        sum[i] = sum[i - 1] ^ a[i];
    }

    init();
    for (int i = 0; i < n; i++)
    {
        insert(sum[i]);
    }

    for (int b1 = 0; b1 < n; b1++)
    {
        if (queryMax(b1) < n)
        {
            b[1] = b1;
            for (int i = 1; i < n; i++)
            {
                b[i + 1] = b1 ^ sum[i];
            }
            for (int i = 1; i <= n; i++)
            {
                cout << b[i] << (i == n ? "" : " ");
            }
            cout << endl;
            return 0;
        }
    }

    return 0;
}