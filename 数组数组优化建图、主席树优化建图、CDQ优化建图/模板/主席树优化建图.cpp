// 主席树优化建图，C++版
// 点的编号范围1~n，点权范围1~v，初始时袋子为空，没有任何边，实现如下方法
// add(x, xv)，编号为x、点权为xv的点进入袋子，该编号已经入袋则忽略
// rangeToX(l, r, x, w)，袋中点权范围l~r的每个点，向点x连边权为w的边
// xToRange(x, l, r, w)，点x向袋中点权范围l~r的每个点，连边权为w的边
// rangeToRange(l1, r1, l2, r2, w)，范围向范围连边，具体含义如下
// 袋中点权l1~r1的每个点，向袋中点权l2~r2的每个点，连边权为w的边
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

int rootOut[MAXN];
int rootIn[MAXN];
int ls[MAXT];
int rs[MAXT];
int curVersion;

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

int buildOut(int l, int r) {
    int rt = ++cntt;
    if (l < r) {
        int mid = (l + r) >> 1;
        ls[rt] = buildOut(l, mid);
        rs[rt] = buildOut(mid + 1, r);
        addEdge(ls[rt], rt, 0);
        addEdge(rs[rt], rt, 0);
    }
    return rt;
}

int buildIn(int l, int r) {
    int rt = ++cntt;
    if (l < r) {
        int mid = (l + r) >> 1;
        ls[rt] = buildIn(l, mid);
        rs[rt] = buildIn(mid + 1, r);
        addEdge(rt, ls[rt], 0);
        addEdge(rt, rs[rt], 0);
    }
    return rt;
}

int addOut(int jobx, int jobv, int l, int r, int i) {
    int rt = ++cntt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    addEdge(i, rt, 0);
    if (l == r) {
        addEdge(jobx, rt, 0);
    } else {
        int mid = (l + r) >> 1;
        if (jobv <= mid) {
            ls[rt] = addOut(jobx, jobv, l, mid, ls[rt]);
            addEdge(ls[rt], rt, 0);
        } else {
            rs[rt] = addOut(jobx, jobv, mid + 1, r, rs[rt]);
            addEdge(rs[rt], rt, 0);
        }
    }
    return rt;
}

int addIn(int jobx, int jobv, int l, int r, int i) {
    int rt = ++cntt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    addEdge(rt, i, 0);
    if (l == r) {
        addEdge(rt, jobx, 0);
    } else {
        int mid = (l + r) >> 1;
        if (jobv <= mid) {
            ls[rt] = addIn(jobx, jobv, l, mid, ls[rt]);
            addEdge(rt, ls[rt], 0);
        } else {
            rs[rt] = addIn(jobx, jobv, mid + 1, r, rs[rt]);
            addEdge(rt, rs[rt], 0);
        }
    }
    return rt;
}

void add(int x, int xv) {
    if (!inBag[x]) {
        inBag[x] = true;
        curVersion++;
        rootOut[curVersion] = addOut(x, xv, 1, v, rootOut[curVersion - 1]);
        rootIn[curVersion] = addIn(x, xv, 1, v, rootIn[curVersion - 1]);
    }
}

void rangeToX(int jobl, int jobr, int jobx, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(i, jobx, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            rangeToX(jobl, jobr, jobx, jobw, l, mid, ls[i]);
        }
        if (jobr > mid) {
            rangeToX(jobl, jobr, jobx, jobw, mid + 1, r, rs[i]);
        }
    }
}

void rangeToX(int l, int r, int x, int w) {
    rangeToX(l, r, x, w, 1, v, rootOut[curVersion]);
}

void xToRange(int jobx, int jobl, int jobr, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(jobx, i, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            xToRange(jobx, jobl, jobr, jobw, l, mid, ls[i]);
        }
        if (jobr > mid) {
            xToRange(jobx, jobl, jobr, jobw, mid + 1, r, rs[i]);
        }
    }
}

void xToRange(int x, int l, int r, int w) {
    xToRange(x, l, r, w, 1, v, rootIn[curVersion]);
}

void rangeToRange(int l1, int r1, int l2, int r2, int w) {
    int x = ++cntt;
    int y = ++cntt;
    rangeToX(l1, r1, x, 0);
    xToRange(y, l2, r2, 0);
    addEdge(x, y, w);
}