#include <iostream>

#include <algorithm>

#include <map>

#include <set>

#include <vector>

#include <climits>

#include <cmath>

#include <queue>

using namespace std;

using ll = long long;

int n, k;

map<int, ll> gold;

ll num_silver;

priority_queue<pair<ll, int>> change;

struct Node

{

    int o, x;
};

Node arr[200010];

bool killMoster(int hp, int idx)
{

    ll need = hp / k;

    while (need && !gold.empty())

    {

        auto i = prev(gold.end());

        ll tack = min(need, i->second);

        i->second -= tack;

        need -= tack;

        hp -= tack * k;

        if (i->second == 0)

            gold.erase(i);
    }

    // 1金币花完了

    if (gold.empty())
    {

        if (num_silver >= hp)
        {

            num_silver -= hp;

            return true;
        }

        else

        {

            return false;
        }
    }

    // 2有剩

    change.push({hp, idx});

    if (num_silver >= hp)
    {

        num_silver -= hp;
    }

    else

    {

        while (!change.empty() && gold.begin()->first >= change.top().second)

        {

            change.pop();
        }

        if (!change.empty())
        {

            auto top = change.top();

            change.pop();

            ll r_big = top.first;

            int t_big = top.second;

            auto it = gold.lower_bound(t_big);

            --it;

            it->second--;

            if (it->second == 0)

                gold.erase(it);

            num_silver += r_big;

            num_silver -= hp;
        }

        else

        {

            auto it = prev(gold.end());

            it->second--;

            if (it->second == 0)

                gold.erase(it);

            num_silver -= hp;
        }
    }

    return true;
}

int main()
{

    int t;

    cin >> t;

    while (t--)

    {

        priority_queue<pair<ll, int>> empty;

        change.swap(empty);

        num_silver = 0;

        gold = {};

        cin >> n >> k;

        for (int i = 1; i <= n; i++)
        {

            cin >> arr[i].o >> arr[i].x;
        }

        bool check = true;

        for (int i = 1, o, x; i <= n; i++)
        {

            o = arr[i].o;
            x = arr[i].x;

            if (o == 1)
            {

                gold[i] += x;
            }

            else if (o == 2)
            {

                num_silver += x;
            }

            else

            {

                if (!killMoster(x, i))
                {

                    check = false;

                    break;
                }
            }
        }

        if (check)
        {

            ll num_gold = 0;

            for (auto &p : gold)

                num_gold += p.second;

            cout << num_gold * k + num_silver << endl;
        }

        else

        {

            cout << -1 << endl;
        }
    }
}
