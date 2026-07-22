// 树状数组优化建图，C++版
// 点的编号范围1~n，点权范围1~v，初始时袋子为空，没有任何边，实现如下方法
// add(x, xv)，编号为x、点权为xv的点进入袋子，该编号已经入袋则忽略
// rangeToX(p, x, w)，袋中点权范围1~p的每个点，向点x连边权为w的边
// xToRange(x, p, w)，点x向袋中点权范围1~p的每个点，连边权为w的边
// rangeToRange(p1, p2, w)，范围向范围连边，具体含义如下
// 袋中点权1~p1的每个点，向袋中点权1~p2的每个点，连边权为w的边
// 建好图之后可以测试图的任何算法，比如dijkstra算法求最短路
// 如下代码在C++环境运行，可以通过对数器验证
// C++版本和java版本逻辑完全一样

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001;
const int MAXV = 1001;
const int MAXT = 10001;
const int MAXE = 10001;
int n, v, cntt;

bool inBag[MAXN];

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cntg;

int outTree[MAXV];
int inTree[MAXV];

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

int lowbit(int i) {
    return i & -i;
}

void addOut(int x, int xv) {
    while (xv <= v) {
        int preo = outTree[xv];
        int curo = ++cntt;
        if (preo > 0) {
            addEdge(preo, curo, 0);
        }
        addEdge(x, curo, 0);
        outTree[xv] = curo;
        xv += lowbit(xv);
    }
}

void addIn(int x, int xv) {
    while (xv <= v) {
        int prei = inTree[xv];
        int curi = ++cntt;
        if (prei > 0) {
            addEdge(curi, prei, 0);
        }
        addEdge(curi, x, 0);
        inTree[xv] = curi;
        xv += lowbit(xv);
    }
}

void add(int x, int xv) {
    if (!inBag[x]) {
        inBag[x] = true;
        addOut(x, xv);
        addIn(x, xv);
    }
}

void rangeToX(int p, int x, int w) {
    while (p > 0) {
        if (outTree[p] > 0) {
            addEdge(outTree[p], x, w);
        }
        p -= lowbit(p);
    }
}

void xToRange(int x, int p, int w) {
    while (p > 0) {
        if (inTree[p] > 0) {
            addEdge(x, inTree[p], w);
        }
        p -= lowbit(p);
    }
}

void rangeToRange(int p1, int p2, int w) {
    int x = ++cntt;
    int y = ++cntt;
    rangeToX(p1, x, 0);
    xToRange(y, p2, 0);
    addEdge(x, y, w);
}