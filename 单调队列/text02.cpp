// 绝对差不超过限制的最长连续子数组
// 给你一个整数数组 nums ，和一个表示限制的整数 limit
// 请你返回最长连续子数组的长度
// 该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit
// 如果不存在满足条件的子数组，则返回 0

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

// 窗口内最大值的更新结构（单调队列）
int maxDeque[MAXN];
// 窗口内最小值的更新结构（单调队列）
int minDeque[MAXN];
int maxh, maxt, minh, mint;
int *arr;

int longestSubarray(vector<int> &nums, int limit)
{
    maxh = maxt = minh = mint = 0;
    arr = &nums[0]; // 获取数组的首地址
    int n = nums.size();
    int ans = 0;

    for (int l = 0, r = 0; l < n; l++)
    {
        // [l, r)，r是下一个要加入窗口的元素的位置
        while (r < n && ok(limit, nums[r]))
        {
            push(r++);
        }
        // 当前窗口[l, r)是l开头的子数组能向右延伸的最大范围
        ans = max(ans, r - l);
        pop(l);
    }
    return ans;
}

// 判断如果加入数字number，窗口最大值 - 窗口最小值是否依然 <= limit
// 依然 <= limit，返回true
// 不再 <= limit，返回false
bool ok(int limit, int number)
{
    // 计算新窗口的最大值
    int currentMax = (maxh < maxt) ? max(arr[maxDeque[maxh]], number) : number;
    // 计算新窗口的最小值
    int currentMin = (minh < mint) ? min(arr[minDeque[minh]], number) : number;
    return (currentMax - currentMin) <= limit;
}

// 将r位置的数字加入窗口，维护最大值和最小值的单调队列
void push(int r)
{
    // 维护最大值的单调队列
    while (maxh < maxt && arr[maxDeque[maxt - 1]] <= arr[r])
    {
        maxt--;
    }
    maxDeque[maxt++] = r;

    // 维护最小值的单调队列
    while (minh < mint && arr[minDeque[mint - 1]] >= arr[r])
    {
        mint--;
    }
    minDeque[mint++] = r;
}

// 窗口左边界移动，处理过期元素
void pop(int l)
{
    // 如果最大值队列的队头元素是过期的（即等于l），则弹出
    if (maxh < maxt && maxDeque[maxh] == l)
    {
        maxh++;
    }
    // 如果最小值队列的队头元素是过期的（即等于l），则弹出
    if (minh < mint && minDeque[minh] == l)
    {
        minh++;
    }
}