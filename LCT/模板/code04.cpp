// 群岛，C++版
// 一共n个点，每个点有点权，初始时没有边，一共m条操作，类型如下
// 操作 bridge x y    : 如果x和y已经连通，打印no，表示不需要连边
//                      如果x和y不连通，打印yes，然后增加无向边
// 操作 penguins x y  : x的点权变成y
// 操作 excursion x y : 如果x和y不连通，打印impossible
//                      如果x和y连通，打印路径的点权累加和
// 1 <= n <= 3 * 10^4
// 1 <= m <= 3 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4312

#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 30010;
int n, m;
int arr[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];

int sum[MAXN];

void up(int x)
{
    sum[x] = sum[ls[x]] + sum[rs[x]] + arr[x];
}

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
    up(f);
    up(x);
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
        up(x);
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

void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
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
        up(x);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        sum[i] = arr[i];
    }
    cin >> m;
    string op;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> op >> x >> y;
        if (op == "bridge")
        {
            if (findroot(x) == findroot(y))
            {
                cout << "no" << endl;
            }
            else
            {
                cout << "yes" << endl;
                link(x, y);
            }
        }
        else if (op == "penguins")
        {
            splay(x);
            arr[x] = y;
            up(x);
        }
        else
        {
            if (findroot(x) != findroot(y))
            {
                cout << "impossible" << endl;
            }
            else
            {
                split(x, y);
                cout << sum[y] << endl;
            }
        }
    }
}