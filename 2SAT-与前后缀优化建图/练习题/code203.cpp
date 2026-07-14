// 编码，C++版
// 一共有n个字符串，都由字符 '0'、'1'、'?' 组成
// 每个字符串最多含有一个'?'，如果不含有，说明该字符串已经确定了
// 如果字符串含有'?'，那么这个'?'必须变成'0'或'1'中的一个
// 请把所有字符串都确定下来，要求任意一个字符串不是其它字符串的前缀
// 存在方案打印"YES"，然后打印每个确定后的字符串，不存在方案打印"NO"
// 1 <= n、字符总数 <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P6965

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 500001;
const int MAXP = 1000002;
const int MAXT = 5000001;
const int MAXE = 10000001;
int n, cntt;

string arr[MAXN << 1];

int headg[MAXT];
int nxtg[MAXE];
int tog[MAXE];
int cntg;

int tree[MAXP][2];
int up[MAXP];
int down[MAXP];
int fa[MAXP];
int cntp;

int headx[MAXP];
int nxtx[MAXP];
int tox[MAXP];
int cntx;

int group[MAXN];
int gsiz;

int dfn[MAXT];
int low[MAXT];
int cntd;

int sta[MAXT];
int top;

int belong[MAXT];
int sccCnt;

void addEdge(int u, int v)
{
    nxtg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    for (int e = headg[u]; e; e = nxtg[e])
    {
        int v = tog[e];
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

int other(int x)
{
    return x <= n ? x + n : x - n;
}

void addGroup(int u, int x)
{
    nxtx[++cntx] = headx[u];
    tox[cntx] = x;
    headx[u] = cntx;
}

void insert(int x)
{
    string str = arr[x];
    int cur = 1;
    for (int si = 0; si < str.size(); si++)
    {
        int path = str[si] == '0' ? 0 : 1;
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++cntp;
            fa[cntp] = cur;
            up[cntp] = ++cntt;
            down[cntp] = ++cntt;
            addEdge(up[cntp], up[cur]);
            addEdge(down[cur], down[cntp]);
        }
        cur = tree[cur][path];
    }
    addEdge(x, up[fa[cur]]);
    addEdge(up[cur], other(x));
    addEdge(x, down[cur]);
    addEdge(down[fa[cur]], other(x));
    addGroup(cur, x);
}

void groupLink()
{
    if (gsiz > 1)
    {
        cntt++;
        addEdge(cntt, other(group[1]));
        for (int i = 2; i <= gsiz; i++)
        {
            addEdge(++cntt, other(group[i]));
            addEdge(cntt, cntt - 1);
            addEdge(group[i], cntt - 1);
        }

        addEdge(++cntt, other(group[gsiz]));
        for (int i = gsiz - 1; i >= 1; i--)
        {
            addEdge(++cntt, other(group[i]));
            addEdge(cntt, cntt - 1);
            addEdge(group[i], cntt - 1);
        }
    }
}

void buildGroup()
{
    cntt = n << 1;
    cntp = 1;
    up[1] = ++cntt;
    down[1] = ++cntt;
    for (int i = 1; i <= (n << 1); i++)
    {
        insert(i);
    }
    for (int u = 1; u <= cntp; u++)
    {
        gsiz = 0;
        for (int e = headx[u]; e; e = nxtx[e])
        {
            group[++gsiz] = tox[e];
        }
        groupLink();
    }
}

void addString(int i, string s)
{
    int mark = -1;
    for (int si = 0; si < s.size(); si++)
    {
        if (s[si] == '?')
        {
            mark = si;
            break;
        }
    }
    if (mark == -1)
    {
        if (s[0] == '0')
        {
            addEdge(i + n, i);
        }
        else
        {
            addEdge(i, i + n);
        }
        mark = 0;
    }
    s[mark] = '0';
    arr[i] = s;
    s[mark] = '1';
    arr[i + n] = s;
}

int main()
{
    cin >> n;
    string s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        addString(i, s);
    }
    buildGroup();
    for (int i = 1; i <= (n << 1); i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }
    bool check = true;
    for (int i = 1; i <= n; i++)
    {
        if (belong[i] == belong[i + n])
        {
            check = false;
            break;
        }
    }
    if (check)
    {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++)
        {
            if (belong[i] < belong[i + n])
            {
                cout << arr[i] << endl;
            }
            else
            {
                cout << arr[i + n] << endl;
            }
        }
    }
    else
    {
        cout << "NO" << endl;
    }
}