// cdq优化建图二维偏序，C++版
// 一共n个点，每个点给定两个点权，a[i]、b[i]，初始时没有边
// 一共m条操作，格式 x w，每个满足如下要求的点，都向x连权值为w的边
// 两种点权 <= x对应的点权，这样的点就算满足要求，注意x自己也是达标的
// 建好图之后可以测试图的任何算法，比如dijkstra算法求最短路
// 如下代码在C++环境运行，可以通过对数器验证
// C++版本和java版本逻辑完全一样

#include <bits/stdc++.h>

using namespace std;

struct Data {
    int i, a, b;
};

bool DataCmp(Data x, Data y) {
    if (x.a != y.a) {
        return x.a < y.a;
    }
    return x.b < y.b;
}

const int MAXN = 101;
const int MAXM = 1001;
const int MAXV = 10001;
const int MAXT = 100001;
const int MAXE = 100001;
int n, m, cntt;
int a[MAXN];
int b[MAXN];

Data arr[MAXN];
Data tmp[MAXN];
int cnta;

int headg[MAXT];
int nextg[MAXE];
int tog[MAXE];
int weightg[MAXE];
int cntg;

int headp[MAXT];
int nextp[MAXM << 1];
int top[MAXM << 1];
int weightp[MAXM << 1];
int cntp;

void addEdge(int u, int v, int w) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    weightg[cntg] = w;
    headg[u] = cntg;
}

void addOp(int x, int u, int w) {
    nextp[++cntp] = headp[x];
    top[cntp] = u;
    weightp[cntp] = w;
    headp[x] = cntp;
}

void merge(int l, int mid, int r) {
    int pre = 0, cur = 0;
    for (int p1 = l - 1, p2 = mid + 1; p2 <= r; p2++) {
        cur = ++cntt;
        while (p1 + 1 <= mid && arr[p1 + 1].b <= arr[p2].b) {
            p1++;
            addEdge(arr[p1].i, cur, 0);
        }
        if (pre > 0) {
            addEdge(pre, cur, 0);
        }
        for (int e = headp[arr[p2].i]; e > 0; e = nextp[e]) {
            int u = top[e];
            int w = weightp[e];
            addEdge(cur, u, w);
        }
        pre = cur;
    }
    int p1 = l, p2 = mid + 1, ti = 0;
    while (p1 <= mid && p2 <= r) {
        if (arr[p1].b <= arr[p2].b) {
            tmp[++ti] = arr[p1++];
        } else {
            tmp[++ti] = arr[p2++];
        }
    }
    while (p1 <= mid) {
        tmp[++ti] = arr[p1++];
    }
    while (p2 <= r) {
        tmp[++ti] = arr[p2++];
    }
    for (int i = l, j = 1; i <= r; i++, j++) {
        arr[i] = tmp[j];
    }
}

void cdq(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    merge(l, mid, r);
}

void buildGraph() {
    for (int i = 1; i <= n; i++) {
        arr[i] = {i,a[i],b[i]};
    }
    sort(arr + 1, arr + n + 1, DataCmp);
    cntt = n;
    for (int l = 1, r = 1; l <= n; l = ++r) {
        int a = arr[l].a;
        int b = arr[l].b;
        while (r + 1 <= n && a == arr[r + 1].a && b == arr[r + 1].b) {
            r++;
        }
        int x = ++cntt;
        for (int i = l; i <= r; i++) {
            int u = arr[i].i;
            addEdge(u, x, 0);
            for (int e = headp[u]; e > 0; e = nextp[e]) {
                addEdge(x, u, weightp[e]);
                addOp(x, u, weightp[e]);
            }
        }
        arr[++cnta] = {x, a, b};
    }
    cdq(1, cnta);
}