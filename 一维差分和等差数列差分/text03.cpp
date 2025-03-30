/*我们把山顶上的湖泊看作一条长度为 m 的直线，一开始水深都在水平线上，我们视作此时的水深为 '0'

接下来，在一瞬间，小正方形的"朋友"们跳起并扎入水中，导致在入水点的水降低而远离入水点的水升高，注意两个 "朋友" 可能在同一地点入水。

小正方形的每个朋友有一个体积数值 v，当体积为 v 的一个朋友跳入水中，我们设入水点为 i，将会导致 i−v+1 到 i 的水位依次降低 1,2,⋯,v

同样地，第 i 到 i+v−1 的水位会依次降低 v,v−1,⋯,1.

相对应地，i−v 的水位不变， i−v−1 到 i−2∗v 水位依次增加 1,2,⋯,v， i−2∗v 到 i−3∗v+1 水位依次增加 v,v−1,⋯,1

同样，i+v 水位不变，i+v+1 到 i+2∗v 水位增加 1,2,⋯,v，i+2∗v 到 i+3∗v−1 水位依次增加 v,v−1,⋯,1

现在小正方形想要穿过这个湖，他想要知道在这 n 个"朋友"跳入水中后湖上每个节点的水位，你能帮帮它吗？*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAXN = 1000001;//湖泊宽度,正式位置的范围是1~m
const int OFFSET = 30001;//偏移量,用于处理边界问题
vector<int> arr(OFFSET + MAXN + OFFSET);//差分数组,用于存储水位变化
int n, m;//n是落水人数,m是湖泊的正式位置数量

void set(int l, int r, int s, int e, int d);

// 初始化差分数组
void init()
{
    for (int i = 0; i < OFFSET + MAXN + OFFSET;i++)
    {
        arr[i] = 0;
    }
}

//处理落水事件
void fall(int v,int x)
{
    //落水事件会对四个区间产生影响,分别处理这四个区间
    set(x - 3 * v + 1, x - 2 * v, 1, v, 1);
    set(x - 2 * v + 1, x, v - 1, -v, -1);
    set(x + 1, x + 2 * v, -v + 1, v, 1);
    set(x + 2 * v + 1, x + 3 * v - 1, v - 1, 1, -1);
}

//差分数组的更新操作
void set(int l,int r,int s,int e,int d)
{
    //为了防止越界,所有位置都加上OFFSET
    //这样可以确保所有位置的在数组的有效范围内
    arr[l + OFFSET] += s;
    arr[l + 1 + OFFSET] += d - s;
    arr[r + 1 + OFFSET] -= d + e;
    arr[r + 2 + OFFSET] += e;
}

//构建最终的水位数组
void build()
{
    //第一次前缀和计算
    for (int i = 1; i <= m + OFFSET;i++)
    {
        arr[i] += arr[i - 1];
    }
    //第二次前缀和计算
    for (int i = 1; i <= m + OFFSET;i++)
    {
        arr[i] += arr[i - 1];
    }
}

int main()
{
    //输入处理
    while (cin>>n>>m)
    {
        init();//初始化差分数组
        for (int i = 0; i < n;i++)
        {
            int v, x;
            cin >> v >> x;
            fall(v, x); //处理落水事件
        }
        build();//构建最终的水位数组
        // 输出结果
        cout << arr[OFFSET + 1];
        for (int i = 2; i <= m; i++)
        {
            cout << " " << arr[OFFSET + i];
        }
        cout << endl;
    }
    return 0;
}