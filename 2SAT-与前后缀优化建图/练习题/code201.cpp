#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int eid, nid, color;
};

bool NodeCmp(Node a, Node b)
{
    if (a.nid != b.nid)
    {
        return a.nid < b.nid;
    }
    return a.color < b.color;
}

const int MAXM = 50010;
const int MAXT = 500010;
const int MAXE = 1000010;
int n, m, k, maxt, cntt;

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int cntg;

int group[MAXM];
int gsiz;

int dfn[MAXT];
int low[MAXT];
int cntd;

int sta[MAXT];
int top;

int belong[MAXT];
int sccCnt;

int destroytime[MAXM];
Node arr[MAXM << 1];

int ansTime;
int ansSize;
int ansArr[MAXM];

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

int other(int i)
{
    return i <= m ? i + m : i - m;
}

void groupLink()
{
    if (gsiz > 1)
    {
        cntt++;
        addEdge(cntt, other(group[1]));
        for (int i = 2; i <= gsiz; i++)
        {
            cntt++;
            addEdge(cntt, other(group[i]));
            addEdge(cntt, cntt - 1);
            addEdge(group[i], cntt - 1);
        }

        cntt++;
        addEdge(cntt, other(group[gsiz]));
        for (int i = gsiz - 1; i >= 1; i--)
        {
            cntt++;
            addEdge(cntt, other(group[i]));
            addEdge(cntt, cntt - 1);
            addEdge(group[i], cntt - 1);
        }
    }
}

void buildGroup(int limit)
{
    cntt = m << 1;
    for (int i = 1; i <= m; i++)
    {
        if (destroytime[i] > limit)
        {
            addEdge(i, i + m);
        }
    }

    for (int l = 1, r = 1; l <= k; l = ++r)
    {
        int curx = arr[l].nid;
        while (r + 1 <= k && arr[r + 1].nid == curx)
        {
            r++;
        }
        gsiz = 0;
        for (int i = l; i <= r; i++)
        {
            group[++gsiz] = arr[i].eid;
        }
        groupLink();
    }

    for (int l = 1, r = 1; l <= k; l = ++r)
    {
        int curx = arr[l].nid;
        int curc = arr[l].color;
        while (r + 1 <= k && arr[r + 1].nid == curx && arr[r + 1].color == curc)
        {
            r++;
        }
        gsiz = 0;
        for (int i = l; i <= r; i++)
        {
            group[++gsiz] = other(arr[i].eid);
        }
        groupLink();
    }
}

void clear()
{
    for (int i = 1; i <= cntt; i++)
    {
        head[i] = dfn[i] = belong[i] = 0;
    }
    cntt = cntg = sccCnt = cntd = top = 0;
}

bool getAns(int limit)
{
    buildGroup(limit);

    for (int i = 1; i <= (m << 1); i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }

    bool check = true;

    for (int i = 1; i <= m; i++)
    {
        if (belong[i] == belong[i + m])
        {
            check = false;
            break;
        }
    }

    if (check)
    {
        ansTime = ansSize = 0;
        for (int i = 1; i <= m; i++)
        {
            if (belong[i] < belong[i + m])
            {
                ansTime = max(ansTime, destroytime[i]);
                ansArr[++ansSize] = i;
            }
        }
    }
    clear();
    return check;
}

bool compute()
{
    sort(arr + 1, arr + k + 1, NodeCmp);
    int l = 1, r = maxt, mid;
    bool hasAns = false;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (getAns(mid))
        {
            hasAns = true;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return hasAns;
}

int main()
{
    cin >> n >> m;
    maxt = 0;
    for (int i = 1, x, y, c, t; i <= m; i++)
    {
        cin >> x >> y >> c >> t;
        arr[++k] = {i, x, c};
        arr[++k] = {i, y, c};
        maxt = max(maxt, t);
        destroytime[i] = t;
    }
    bool check = compute();
    if (check)
    {
        cout << "Yes" << endl;
        cout << ansTime << ' ' << ansSize << endl;
        for (int i = 1; i <= ansSize; i++)
        {
            cout << ansArr[i] << ' ';
        }
        cout << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
