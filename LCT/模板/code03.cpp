// 部落冲突，C++版
// 一共n个点，给定n-1条边，所有点组成一棵树，一共m条操作，类型如下
// 操作 C x y : x和y在树中相邻，之前未开战，现在开战，x和y的直接边变成不可通行
//              每条C操作代表一次战争事件，战争事件从1开始编号，每次编号自增
// 操作 U x   : 第x号战争事件结束，对应的直接边变为可通行，保证战争不会重复结束
// 操作 Q x y : 查询点x和点y之间是否连通，打印 Yes 或 No
// 1 <= n、m <= 3 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3950

#include <algorithm>
#include <iostream>
#include <string>
#include <climits>
using namespace std;
using ll = long long;

const int MAXN = 10010;
int n, m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];

bool isroot(int x)
{
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x)
{
    return ls[fa[x]] == x ? 0 : 1;
}

void reverse(int x)
{
    if (x != 0)
    {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

void down(int x)
{
    if (rev[x])
    {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
}

void rotate(int x)
{
    int f = fa[x], g = fa[f];
    if (lr(x) == 0)
    {
        ls[f] = rs[x];
        if (ls[f] != 0)
        {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    }
    else
    {
        rs[f] = ls[x];
        if (rs[f] != 0)
        {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f))
    {
        if (lr(f) == 0)
        {
            ls[g] = x;
        }
        else
        {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
}

void splay(int x)
{
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = fa[y])
    {
        sta[++siz] = fa[y];
    }
    while (siz != 0)
    {
        down(sta[siz--]);
    }
    while (siz != 0)
    {
        down(sta[siz--]);
    }
    while (!isroot(x))
    {
        int f = fa[x];
        if (!isroot(f))
        {
            if (lr(x) == lr(f))
            {
                rotate(f);
            }
            else
            {
                rotate(x);
            }
        }
        rotate(x);
    }
}

void access(int x)
{
    for (int y = 0; x != 0; y = x, x = fa[x])
    {
        splay(x);
        rs[x] = y;
    }
}

void makeroot(int x)
{
    access(x);
    splay(x);
    reverse(x);
}

int findroot(int x)
{
    access(x);
    splay(x);
    down(x);
    while (ls[x] != 0)
    {
        x = ls[x];
        down(x);
    }
    splay(x);
    return x;
}

void link(int x, int y)
{
    makeroot(x);
    if (findroot(y) != x)
    {
        fa[x] = y;
    }
}

void cut(int x, int y)
{
    makeroot(x);
    if (findroot(y) == x && fa[y] == x && ls[y] == 0 && rs[x] == y)
    {
        fa[y] = rs[x] = 0;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++)
    {
        string op;
        cin >> op >> x >> y;
        if (op == "Connect")
        {
            link(x, y);
        }
        else if (op == "Destroy")
        {
            cut(x, y);
        }
        else
        {
            if (findroot(x) == findroot(y))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
}