#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <cstring>
#include <bit>
using namespace std;
using ll = long long;

int n;
int N;

int main()
{
    cin >> n;
    int N = 1 << n;
    string s(N, '0');
    ll sum = 0;

    for (int a = 1; a < N; a++)
    {
        for (int b = 0; b < 2; b++)
        {
            for (unsigned int x = 0; x < N; x++)
            {
                int ip = popcount(a & x) & 1; // cpp20才有 老版本gcc用__builtin_popcount
                s[x] = (ip == b) ? '0' : '1';
            }
            cout << "? " << s << endl;
            ll d;
            cin >> d;
            sum += d;
        }
    }
    ll denom = (1LL << (n + 1)) - (1LL << (n - 1)) - 1;
    cout << "! " << sum / denom << endl;
    return 0;
}