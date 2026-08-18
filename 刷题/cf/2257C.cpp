#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int n, m;
int a[100010];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 2, tmp; i <= n; i++)
        {
            cin >> tmp;
        }
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> a[i];
        }
        sort(a + 1, a + m + 1);
        cout << m - 1 << ' ';
        for (int i = 2; i <= m; i++)
        {
            cout << a[i] << ' ';
        }
        cout << endl;
    }
}