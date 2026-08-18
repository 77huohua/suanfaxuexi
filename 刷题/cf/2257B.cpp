#include <iostream>
#include <string>
#include <set>
using namespace std;

int n1, n2, max1, max2;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n1 >> n2;
        cin >> max1;
        for (int i = 2, tmp; i <= n1; i++)
        {
            cin >> tmp;
        }
        cin >> max2;
        for (int i = 2, tmp; i <= n2; i++)
        {
            cin >> tmp;
        }
        if (n1 + max1 >= n2 + max2)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}