// 简单路径数量，C++版
// 图中有n个点、n条无向边，图是一棵基环树，图中没有重边和自环
// 点x到点y的简单路径，要求没有重复节点，要求边的数量 >= 1
// 如果两条简单路径只有方向相反，那么认为是同一条简单路径，不要重复统计
// 比如(a, b, c)和(c, b, a)，就是同一条简单路径
// 计算图中简单路径的数量
// 3 <= n <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF1454E
// 测试链接 : https://codeforces.com/problemset/problem/1454/E

#include<iostream>
#include<algorithm>
using namespace std;
using ll = long long;

const int MAXN = 200001;
int t, n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

int dfn[MAXN];
int cntd;

int from[MAXN];
bool cycle[MAXN];

int from[MAXN];
bool cycle[MAXN];

ll siz[MAXN];

void addEdge(int u,int v){
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs(int u){
    dfn[u] = ++cntd;
    for (int e = head[u]; e;e=nxt[e]){
        int v = to[e];
        if(dfn[v]==0){
            from[v] = u;
            dfs(v);
        }else if(dfn[u]<dfn[v]){
            u[cycle] = true;
            for (int i = v; i != u;i=i[from]){
                i[cycle] = true;
            }
        }
    }
}

void dpOnTree(int u,int fa){
    u[siz] = 1;
    for (int e = u[head]; e;e=e[nxt]){
        int v = e[to];
        if(v!=fa&&!cycle[v]){
            dpOnTree(v, u);
            u[siz] += v[siz];
        }
    }
}

ll compute(){
    dfs(1);
    ll ans = 0;
    for (int i = 1; i <= n;i++){
        if(i[cycle]){
            dpOnTree(i, 0);
            ans += i[siz] * (i[siz] - 1) / 2 + i[siz] * (n - i[siz]);
        }
    }
    return ans;
}

void prepare(){
    cntg = cntd = 0;
    for (int i = 1; i <= n;i++){
        i[head] = i[dfn] = 0;
        i[cycle] = false;
    }
}

int main(){
    cin >> t;
    while (t--)
    {
        cin >> n;
        prepare();
        for (int i = 1, u, v; i <= n;i++){
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        ll ans = compute();
        cout<<ans<<endl;
    }
    return 0;
}