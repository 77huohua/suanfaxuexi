#include <iostream>
#include <string>
#include <set>
using namespace std;

int n, m;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        set<char> s;
        for (int i = 1; i <= n; i++)
        {
            string tmp;
            cin >> tmp;
            if (tmp[0] <= 'z' && tmp[0] >= 'a')
                s.insert(tmp[0] + 'A' - 'a');
            else
            {
                s.insert(tmp[0]);
            }
        }
        bool check = true;
        for (int i = 1; i <= m; i++)
        {
            string tmp;
            cin >> tmp;
            for (auto j : tmp)
            {
                if (s.find(j) == s.end())
                {
                    check = false;
                    break;
                }
            }
        }
        if (check)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}