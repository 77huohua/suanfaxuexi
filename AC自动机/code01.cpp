#include <vector>
#include <deque>
#include <string>
using namespace std;

//目标字符串的数量
const int MAXN = 200010;

//所以目标字符串的总字符数量
const int MAXS = 200010;

//记录每个目标串的结尾节点编号
vector<int> end_m(MAXN);

//AC自动机
vector<vector<int>> tree(MAXS, vector<int>(26));

vector<int> fail(MAXS);

int cnt = 0;

//每个节点记录词频
vector<int> times(MAXS);

//可以用作队列或栈,一个容器而已
deque<int> box(MAXS);

//链式前向星,为了建立fail指针的反图
vector<int> head(MAXS);

vector<int> next_m(MAXS);

vector<int> to(MAXS);

int edge;

//遍历fail反图,递归会爆栈,so用非递归代替
vector<bool> visited(MAXS);

//ACAM加入目标字符串
void insert(int i,string str)
{
    int u = 0;
    for (int j = 0, c; j < str.size();j++)
    {
        c = str[j] - 'a';
        if(tree[u][c]==0)
        {
            tree[u][c] = ++cnt;
        }
        u = tree[u][c];
    }
    //每个目标字符串的结尾节点编号
    end_m[i] = u; 
}

//加入所有目标字符串之后
//设置fail指针 以及 设置直接直通表
//做了ACAM固定的优化
void setFail()
{
    //box当作队列来使用
    int l = 0,r=0;
    for (int i = 0; i <= 25;i++)
    {
        if(tree[0][i]>0)
        {
            box[r++] = tree[0][i];
        }
    }
    while (l<r)
    {
        int u = box[l++];
        for (int i = 0; i <= 25;i++)
        {
            if(tree[u][i]==0)
                tree[u][i] = tree[fail[u]][i];
            else
            {
                fail[tree[u][i]] = tree[fail[u]][i];
                box[r++] = tree[u][i];
            }
        }
    } 
}

void addEdge(int u,int v)
{
    next_m[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

//逻辑是对的
//but递归开太多层了可能会爆栈
void f1(int u)
{
    for (int i = head[u]; i > 0;i=next_m[i])
    {
        f1(to[i]);
        times[u] += times[to[i]];
    }
}

//用栈来模拟递归
void f2(int u)
{
    //box当做栈使用
    int r = 0;
    box[r++] = u;
    int cur;
    while (r>0)
    {
        cur = box[r - 1];
        if(!visited[cur])
        {
            visited[cur] = true;
            for (int i = head[cur]; i > 0;i=next_m[i])
            {
                box[r++] = to[i];
            }
        }
        else
        {
            r--;
            for (int i = head[cur]; i > 0;i=next_m[i])
            {
                times[cur] += times[to[i]];
            }
        }
    }
    
}