// 树直径最小化，C++版
// 图中有n个点、n条无向边，每条边有边权，图是一棵基环树
// 可以任意删掉环上的一条边，让图变成树，希望让树的直径最小
// 第一个测试链接，计算树的直径最小值
// 第二个测试链接，等价于计算树的直径最小值 / 2，结果保留一位小数
// 1 <= n <= 2 * 10^5
// 1 <= 边权 <= 10^9
// 测试链接 : https://codeforces.com/problemset/problem/835/F

#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;
using ll = long long;

const int MAXN = 200001;
int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];
int cntg;

int dfn[MAXN];
int cntd;

int fromNode[MAXN];
int fromWeight[MAXN];
bool cycle[MAXN];
int arr[MAXN];
int val[MAXN];
int cnta;

ll dist[MAXN];
ll diamter;

ll height[MAXN];

ll preMax[MAXN];
ll preDiameter[MAXN];

ll sufMax[MAXN];
ll sufDiameter[MAXN];

void addEdge(int u, int v, int w)
{
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

void dfs(int u)
{
    dfn[u] = ++cntd;
    for (int e = head[u]; e; e = nxt[e])
    {
        int v = to[e];
        if (dfn[v] == 0)
        {
            fromNode[v] = u;
            fromWeight[v] = weight[e];
            dfs(v);
        }
        else if (dfn[u] < dfn[v])
        {
            cycle[u] = true;
            arr[++cnta] = u;
            val[cnta] = weight[e];
            for (int i = v; i != u; i = fromNode[i])
            {
                cycle[i] = true;
                arr[++cnta] = i;
                val[cnta] = fromWeight[i];
            }
        }
    }
}

void dpOnTree(int u, int fa)
{
    for (int e = head[u]; e; e = nxt[e])
    {
        int v = to[e];
        int w = weight[e];
        if (v != fa && !cycle[v])
        {
            dpOnTree(v, u);
            diamter = max(diamter, dist[u] + dist[v] + w);
            dist[u] = max(dist[u], dist[v] + w);
        }
    }
}

ll dpOnCycle()
{
    ll best = 0;
    ll sum = 0;
    for (int i = 1; i <= cnta; i++)
    {
        preMax[i] = max(preMax[i - 1], height[i] + sum);
        preDiameter[i] = max(preDiameter[i - 1], sum + height[i] + best);
        best = max(best, height[i] - sum);
        sum += val[i];
    }
    sufMax[cnta] = height[cnta] + val[cnta];
    sufDiameter[cnta] = height[cnta];
    best = height[cnta] - val[cnta];
    sum = val[cnta] + val[cnta - 1];
    for (int i = cnta - 1; i >= 1; i--)
    {
        sufMax[i] = max(sufMax[i + 1], height[i] + sum);
        sufDiameter[i] = max(sufDiameter[i + 1], sum + height[i] + best);
        best = max(best, height[i] - sum);
        sum += val[i - 1];
    }
    ll ans = LLONG_MAX;
    for (int i = 1; i < cnta; i++)
    {
        ans = min(ans, max(preMax[i] + sufMax[i + 1], max(preDiameter[i], sufDiameter[i + 1])));
    }
    ans = min(ans, preDiameter[cnta]);
    return ans;
}

ll compute()
{
    dfs(1);
    ll ans1 = 0;
    for (int i = 1; i <= cnta; i++)
    {
        diamter = 0;
        dpOnTree(arr[i], 0);
        ans1 = max(ans1, diamter);
        height[i] = dist[arr[i]];
    }
    ll ans2 = dpOnCycle();
    return max(ans1, ans2);
}

int main()
{
    cin >> n;
    for (int i = 1, u, v, w; i <= n; i++)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    cout << compute();
}
