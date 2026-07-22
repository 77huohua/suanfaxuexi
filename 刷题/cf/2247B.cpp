#include <iostream>
using namespace std;

int n, k, m;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k >> m;
        if (k > m)
        {
            cout << "NO" << endl;
            continue;
        }
        else
        {
            cout << "YES" << endl;
            for (int i = 1; i <= n - 1; i++)
            {
                cout << 1 << ' ';
            }
            cout << m - k + 1 << endl;
        }
    }
}