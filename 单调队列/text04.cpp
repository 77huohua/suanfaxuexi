// 和至少为K的最短子数组
// 给定一个数组arr，其中的值有可能正、负、0
// 给定一个正数k
// 返回累加和>=k的所有子数组中，最短的子数组长度

#include <iostream>
#include <vector>
#include <climits> // 用于INT_MAX

using namespace std;

const int MAXN = 100001;

// 前缀和数组，sum[0]表示前0个数的和，sum[i]表示前i个数的和
long long sum[MAXN];

// 双端队列，用于存储可能的候选前缀和的索引
int deque[MAXN];
int h, t; // 队列的头和尾指针

int shortestSubarray(vector<int> &arr, int K)
{
    int n = arr.size();

    // 计算前缀和
    sum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        sum[i + 1] = sum[i] + arr[i];
    }

    h = 0; // 队列头指针初始化
    t = 0; // 队列尾指针初始化

    int ans = INT_MAX; // 初始化最短子数组长度为最大值

    // 遍历前缀和数组
    for (int i = 0; i <= n; i++)
    {
        // 尝试从队列头部找到满足条件的前缀和
        while (h < t && sum[i] - sum[deque[h]] >= K)
        {
            // 如果当前前缀和减去队列头部的前缀和 >= K，说明找到了一个可能的解
            ans = min(ans, i - deque[h++]); // 更新最短长度，并移动队列头部
        }

        // 维护双端队列的单调性
        // 如果当前前缀和小于等于队列尾部的前缀和，则移除尾部元素
        while (h < t && sum[deque[t - 1]] >= sum[i])
        {
            t--; // 移除尾部元素
        }

        // 将当前前缀和的索引加入队列尾部
        deque[t++] = i;
    }

    // 如果找到了解，返回最短长度；否则返回-1
    return (ans != INT_MAX) ? ans : -1;
}