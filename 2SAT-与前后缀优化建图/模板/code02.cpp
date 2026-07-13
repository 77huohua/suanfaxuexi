// 和平委员会，C++版
// 一共n个团体，每个团体有两个代表，所以有2n个代表
// 第i号团体两个代表的编号为2i−1和2i，然后给定m个讨厌关系
// 格式 x y : 编号x和编号y这两个代表，相互讨厌，不可共事
// 现在要选出n个人组成委员会，每个团体的两个代表，有且仅有1人入选
// 同时要求选出的委员会中，没有相互讨厌的代表，如果做不到，打印"NIE"
// 如果能做到，按升序打印组成委员会的n个人的编号，任何一种方案都可以
// 1 <= n <= 8 * 10^3
// 0 <= m <= 2 * 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P5782

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16010;
const int MAXM = 40010;

//链式前向星
int head[MAXN];
int to[MAXM];
int nxt[MAXM];
int cntg;

//tarjan
int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int belong[MAXN];
int sccCnt;

int n, m;

//链式前向星建图
void addEdge(int u, int v)
{
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}
//tarjan
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
            low[u] = min(low[v], low[u]);
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

int main()
{
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++)
    {
        cin >> x >> y;//x和y不和
        addEdge(x, y % 2 == 1 ? y + 1 : y - 1);//如果推举x，有必须推举y的队友
        addEdge(y, x % 2 == 1 ? x + 1 : x - 1);//如果推举y,有必须推荐x的队友
    }
    
    for (int i = 1; i <= n << 1; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }

    bool check = true;
    for (int i = 1; i <= n; i++)
    {
        if (belong[2 * i] == belong[2 * i - 1])
        {
            check = false;
            break;
        }
    }
    if (check)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << ((belong[2 * i] < belong[2 * i - 1]) ? 2 * i : 2 * i - 1) << endl;
        }
    }
    else
    {
        cout << "NIE" << endl;
    }
}