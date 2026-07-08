// 约束条件，C++版
// 你需要构造长度为n的数组arr，每个元素的值在1~k之间，数组是非递减的
// 接下来给定m个约束条件，构造方案要满足所有约束条件，约束的格式如下
// 约束 1 i x   : arr[i] != x
// 约束 2 i j x : arr[i] + arr[j] <= x
// 约束 3 i j x : arr[i] + arr[j] >= x
// 如果不存在构造方案打印-1，存在方案就打印arr，任何一种方案都可以
// n、m <= 2 * 10^4
// 2 <= k <= 10
// 测试链接 : https://www.luogu.com.cn/problem/CF1697F
// 测试链接 : https://codeforces.com/problemset/problem/1697/F

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
const int MAXM = 20000010;
const int MAXK = 25;
const int MAXT = MAXN * 20;

int id[MAXN][MAXK][2]; // id[a][x][1]意味a>=k,id[a][k][0]意味a<k
int cntt;

int head[MAXT];
int to[MAXM];
int nxt[MAXM];
int cntg;

int dfn[MAXT];
int low[MAXT];
int cntd;

int sta[MAXT];
int top;

int belong[MAXT];
int sccCnt;

int n, m, k;

void addEdge(int u, int v)
{
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void init()
{
    sccCnt = cntd = cntg = top = 0;
    for (int i = 1; i <= cntt; i++)
    {
        head[i] = dfn[i] = low[i] = sta[i] = belong[i] = 0;
    }
    cntt = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = 1; j <= k + 1; j++)
        {
            id[i][j][0] = ++cntt;
            id[i][j][1] = ++cntt;
        }
    }
    // 天然成立
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            addEdge(id[i][j][0], id[i][j + 1][0]);
            addEdge(id[i][j + 1][1], id[i][j][1]);
        }
    }
    // 数组非递减
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            addEdge(id[i + 1][j][0], id[i][j][0]);
            addEdge(id[i][j][1], id[i + 1][j][1]);
        }
    }
    // i属于1-k
    for (int i = 1; i <= n; i++)
    {
        addEdge(id[i][1][0], id[i][1][1]);
        addEdge(id[i][k + 1][1], id[i][k + 1][0]);
    }
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    for (int e = head[u]; e; e = nxt[e])
    {
        int v = to[e];
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else
        {
            if (belong[v] == 0)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u])
    {
        sccCnt++;
        int pop;
        do
        {
            pop = sta[top--];
            belong[pop] = sccCnt;
        } while (pop != u);
    }
}

void noequal(int a, int x)
{
    addEdge(id[a][x][1], id[a][x + 1][1]);
    addEdge(id[a][x + 1][0], id[a][x][0]);
}

void lessEqual(int i, int j, int x)
{
    for (int w = 1; w <= k; w++)
    {
        if (w >= x)
        {
            noequal(i, w);
        }
        else
        {
            if (x - w + 1 <= k)
            {
                addEdge(id[i][w][1], id[j][x - w + 1][0]);
                addEdge(id[j][x - w + 1][1], id[i][w][0]);
            }
        }
    }
}

void moreEqual(int i, int j, int x)
{
    for (int w = 1; w <= k; w++)
    {
        if (w <= x - k - 1)
        {
            noequal(i, w);
        }
        else
        {
            if (x - w > 1)
            {
                addEdge(id[i][w + 1][0], id[j][x - w][1]);
                addEdge(id[j][x - w][0], id[i][w + 1][1]);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> k;
        init();
        for (int i, j, x, op, o = 1; o <= m; o++)
        {
            cin >> op;
            if (op == 1)
            {
                cin >> i >> x;
                noequal(i, x);
            }
            else if (op == 2)
            {
                cin >> i >> j >> x;
                lessEqual(i, j, x);
                lessEqual(j, i, x);
            }
            else if (op == 3)
            {
                cin >> i >> j >> x;
                moreEqual(i, j, x);
                moreEqual(j, i, x);
            }
        }

        for (int i = 1; i <= cntt; i++)
        {
            if (dfn[i] == 0)
            {
                tarjan(i);
            }
        }

        bool check = true;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= k + 1; j++)
            {
                if (belong[id[i][j][0]] == belong[id[i][j][1]])
                {
                    check = false;
                    break;
                }
            }
        }

        if (check)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = k; j >= 1; j--)
                {
                    if (belong[id[i][j][1]] < belong[id[i][j][0]])
                    {
                        cout << j << ' ';
                        break;
                    }
                }
            }
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}