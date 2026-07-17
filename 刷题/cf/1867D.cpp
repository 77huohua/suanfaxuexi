#include <iostream>
#include <set>
using namespace std;

int n, k;
const int MAXN = 100010;
int b[MAXN];

int head[MAXN];
int to[MAXN];
int nxt[MAXN];
int cntg;

int color[MAXN];
int dep[MAXN];
bool check;

void addEdge(int u, int v)
{
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void clear()
{
    for (int i = 1; i <= n; i++)
    {
        dep[i] = head[i] = color[i] = 0;
    }
    cntg = 0;
}

void dfs(int u, int deep)
{
    color[u] = 1;
    dep[u] = deep;
    for (int e = head[u]; e; e = nxt[e])
    {
        int v = to[e];
        if (color[v] == 0)
        {
            dfs(v, deep + 1);
        }
        else if (color[v] == 1)
        {
            int ring_len = deep - dep[v] + 1;
            if (ring_len != k)
                check = false;
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> b[i];
        }

        if (k == 1)
        {
            check = true;
            for (int i = 1; i <= n; i++)
            {
                if (i != b[i])
                {
                    check = false;
                    break;
                }
            }
            cout << (check ? "YES" : "NO") << endl;
            clear();
            continue;
        }

        for (int i = 1; i <= n; i++)
        {
            addEdge(i, b[i]);
        }

        check = true;
        for (int i = 1; i <= n && check; i++)
        {
            if (color[i] == 0)
            {
                dfs(i, 0);
            }
        }
        cout << (check ? "YES" : "NO") << endl;
        clear();
    }
}