// 同谋者，C++版
// 一共n个人，编号1~n，分配每个人进入交流队或者保密队中的一个
// 交流队要求内部任意两人都认识，保密队要求内部任意两人都不认识
// 给定每人的认识列表，如果x的认识列表里有y，那么y的认识列表里有x
// 分配还要求交流队和保密队都不能为空，计算n个人分成两组的方法数
// 如果不存在任何方法，打印0
// 2 <= n <= 5000
// 所有认识列表的总人数 <= n * (n - 1)
// 测试链接 : https://www.luogu.com.cn/problem/P3513
// 测试链接 : https://loj.ac/p/2155

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
const int MAXE = (MAXN * MAXN) << 1;
const int MAXT = MAXN << 1;

int head[MAXT]; // i+n,保密队 i交流队
int nxt[MAXE];
int to[MAXE];
int cntg;

int dfn[MAXT];
int low[MAXT];
int cntd;

int sta[MAXT];
int top;

int belong[MAXT];
int sccCnt;

bool know[MAXN][MAXN];

int n, m;

int team1[MAXN]; // 交流队
int team2[MAXN]; // 保密队
int cntt1;
int cntt2;

// 如果i在交流队
// other[i] >= 1，表示i认识保密队中的人的编号
// other[i] == 0，表示i不认识保密队中的所有人
// other[i] == -1，表示i认识保密队中的人数，不止一个
//
// 如果i在保密队
// other[i] >= 1，表示i不认识交流队中的人的编号
// other[i] == 0，表示i认识交流队中的所有人
// other[i] == -1，表示i不认识交流队中的人数，不止一个
int other[MAXN];

void addEdge(int u, int v)
{
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
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
    if (low[u] == dfn[u])
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

int compute()
{
    for (int i = 1; i <= n; i++)
    {
        if (belong[i] == belong[i + n])
        {
            return 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (belong[i] < belong[i + n])
        {
            team1[++cntt1] = i;
        }
        else
        {
            team2[++cntt2] = i;
        }
    }

    int ans = cntt1 > 0 && cntt2 > 0 ? 1 : 0;

    for (int i = 1; i <= cntt1; i++)
    {
        for (int j = 1; j <= cntt2; j++)
        {
            if (know[team1[i]][team2[j]])
            {
                other[team1[i]] = (other[team1[i]] == 0) ? team2[j] : -1;
            }
            else
            {
                other[team2[j]] = (other[team2[j]] == 0) ? team1[i] : -1;
            }
        }
    }

    if (cntt1 > 1)
    {
        for (int i = 1; i <= cntt1; i++)
        {
            if (other[team1[i]] == 0)
            {
                ans++;
            }
        }
    }

    if (cntt2 > 1)
    {
        for (int i = 1; i <= cntt2; i++)
        {
            if (other[team2[i]] == 0)
            {
                ans++;
            }
        }
    }

    for (int i = 1; i <= cntt1; i++)
    {
        for (int j = 1; j <= cntt2; j++)
        {
            if (know[team1[i]][team2[j]])
            {
                if (other[team1[i]] == team2[j] && other[team2[j]] == 0)
                {
                    ans++;
                }
            }
            else
            {
                if (other[team1[i]] == 0 && other[team2[j]] == team1[i])
                {
                    ans++;
                }
            }
        }
    }

    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> m;
        for (int j = 1, k; j <= m; j++)
        {
            cin >> k;
            know[i][k] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (know[i][j])
            {
                addEdge(i + n, j);
                addEdge(j + n, i);
            }
            else
            {
                addEdge(i, j + n);
                addEdge(j, i + n);
            }
        }
    }

    for (int i = 1; i <= n << 1; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }

    cout << compute() << endl;
}