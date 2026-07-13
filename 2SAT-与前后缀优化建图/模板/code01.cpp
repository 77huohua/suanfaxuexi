// 2-SAT模版题，C++版
// 一共n个变量，变量的编号1~n，每个变量的取值不是0就是1
// 给定m条限制，每条限制的格式 x1 v1 x2 v2，含义如下
// 编号为x1的变量取值为v1 或者 编号为x2的变量取值为v2
// 决定每个变量的值，来满足所有限制，如果无法做到，打印"IMPOSSIBLE"
// 如果可以做到，先打印"POSSIBLE"，然后打印每个变量的值，任何一种方案都可以
// 1 <= n、m <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P4782

#include <bits/stdc++.h>
    using namespace std;

const int MAXN = 2000010;
const int MAXM = 2000010;

//链式前向星
//点i代表i=1,点i+n代表i=0
int head[MAXN];
int to[MAXM];
int nxt[MAXM];
int cntg;

//tarjan算法
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
    dfn[u] = low[u] = ++cntd;//分配dfn序和初始化low
    sta[++top] = u;//u入栈
    for (int e = head[u]; e; e = nxt[e])//遍历u的所有孩子
    {
        int v = to[e];
        if (dfn[v] == 0)//如果该孩子未被分配dfn序
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);//父亲可以提供该孩子到达孩子能到达的low
        }
        else
        {
            if (belong[v] == 0)//孩子已经被分配dfn序
            {
                low[u] = min(low[u], dfn[v]);//父亲可以到达孩子
            }
        }
    }
    if (dfn[u] == low[u])//父亲无法到达dfn小于该点的地方，扎袋子
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
    for (int i = 1, x1, v1, x2, v2; i <= m; i++)
    {
        //如果x1=0或者x2=0
        cin >> x1 >> v1 >> x2 >> v2;
        if (v1 == 0 && v2 == 0)
        {
            addEdge(x1, x2 + n);//则当x1=1时，推出x2=0
            addEdge(x2, x1 + n);//当x2=2时，推出x1=0
        }
        else if (v1 == 0 && v2 == 1)//要求x1=0或者x2=1
        {
            addEdge(x1, x2);//当x1=1有x2=1
            addEdge(x2 + n, x1 + n); // 当x2=0,有x1=1;
        }
        else if (v1 == 1 && v2 == 0)//要求x1=1或者x2=0
        {
            addEdge(x1 + n, x2 + n);//当x1=0,有x2=0
            addEdge(x2, x1);//当x2=1,有x1=1
        }
        else//要求x1=1或者x2=1
        {
            addEdge(x1 + n, x2);//当x1=0有x2=1
            addEdge(x2 + n, x1);//当x2=0有x1=1
        }
    }
    //tarjan
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
        if (belong[i] == belong[i + n])//当i=0和i=1在同一个强连通分类，说明两个可以相互推出来，无解
        {
            check = false;
            break;
        }
    }
    if (check)
    {
        cout << "POSSIBLE" << endl;
        for (int i = 1; i <= n; i++)
        {
            if (belong[i] < belong[i + n])//belong的编号拓扑序大的天然小，打印拓扑序靠后的结果
            {
                cout << "1 ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }
}
