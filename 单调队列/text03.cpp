// 接取落水的最小花盆
// 老板需要你帮忙浇花。给出 N 滴水的坐标，y 表示水滴的高度，x 表示它下落到 x 轴的位置
// 每滴水以每秒1个单位长度的速度下落。你需要把花盆放在 x 轴上的某个位置
// 使得从被花盆接着的第 1 滴水开始，到被花盆接着的最后 1 滴水结束，之间的时间差至少为 D
// 我们认为，只要水滴落到 x 轴上，与花盆的边沿对齐，就认为被接住
// 给出 N 滴水的坐标和 D 的大小，请算出最小的花盆的宽度 W

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int MAXN = 100005;

// 存储水滴的x坐标和高度
vector<pair<int, int>> arr(MAXN);
int n, d;

// 双端队列用于维护最大值和最小值
vector<int> maxDeque, minDeque;

int compute()
{
    // 按x坐标对水滴进行排序
    sort(arr.begin(), arr.begin() + n, [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.first < b.first; });

    int ans = INT_MAX; // 初始化答案为最大值
    int l = 0, r = 0;  // 滑动窗口的左右指针

    while (l < n)
    {
        // 扩展右边界直到满足条件
        while (r < n && !ok())
        {
            push(r++);
        }

        // 如果当前窗口满足条件，更新答案
        if (ok())
        {
            ans = min(ans, arr[r - 1].first - arr[l].first);
        }

        // 缩小左边界
        pop(l++);
    }

    return (ans == INT_MAX) ? -1 : ans;
}

// 检查当前窗口的最大值和最小值之差是否大于等于d
bool ok()
{
    if (maxDeque.empty() || minDeque.empty())
    {
        return false;
    }
    int max_val = arr[maxDeque.front()].second;
    int min_val = arr[minDeque.front()].second;
    return (max_val - min_val) >= d;
}

// 将新元素推入窗口，并维护双端队列
void push(int index)
{
    // 维护最大值双端队列
    while (!maxDeque.empty() && arr[maxDeque.back()].second <= arr[index].second)
    {
        maxDeque.pop_back();
    }
    maxDeque.push_back(index);

    // 维护最小值双端队列
    while (!minDeque.empty() && arr[minDeque.back()].second >= arr[index].second)
    {
        minDeque.pop_back();
    }
    minDeque.push_back(index);
}

// 从窗口中弹出左边界元素
void pop(int index)
{
    if (!maxDeque.empty() && maxDeque.front() == index)
    {
        maxDeque.erase(maxDeque.begin());
    }
    if (!minDeque.empty() && minDeque.front() == index)
    {
        minDeque.erase(minDeque.begin());
    }
}

int main()
{
    while (cin >> n >> d)
    {
        arr.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i].first >> arr[i].second;
        }

        int result = compute();
        cout << (result == -1 ? -1 : result) << endl;
    }

    return 0;
}