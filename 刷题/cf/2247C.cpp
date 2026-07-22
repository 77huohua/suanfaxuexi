#include <iostream>
#include <string>
using namespace std;

const int MAXN = 200010;

int n;
int a[MAXN], b[MAXN];

bool same()
{
    for (int i = 1; i <= n; i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool AAllIsZero()
{
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 1)
        {
            return false;
        }
    }
    return true;
}

bool BAllIsOne()
{
    for (int i = 1; i <= n; i++)
    {
        if (b[i] == 0)
        {
            return false;
        }
    }
    return true;
}

bool noAns()
{
    if (AAllIsZero() || BAllIsOne())
        return true;
    return false;
}

bool AnsIsOneOrTow()
{
    // true是1，false是2
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 1 && b[i] == 0)
        {
            sum++;
        }
    }
    if (sum % 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> b[i];
        }
        if (same())
        {
            cout << 0 << endl;
            continue;
        }
        if (noAns())
        {
            cout << -1 << endl;
            continue;
        }
        if (AnsIsOneOrTow())
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}