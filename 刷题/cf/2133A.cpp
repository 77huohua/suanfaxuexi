#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
int arr[MAXN];
int n;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 1, arr + n + 1);
        bool check = false;
        for (int i = 2; i <= n; i++)
        {
            if (arr[i - 1] == arr[i])
            {
                cout << "YES" << endl;
                check = true;
                break;
            }
        }
        if (!check)
            cout << "NO" << endl;
    }
}