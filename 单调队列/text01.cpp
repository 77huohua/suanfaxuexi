// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。

#include <vector>
#include <deque>
using namespace std;

vector<int> maxSlidingWindow(vector<int> &arr, int k)
{
    deque<int> dq;   // 使用 deque 模拟双端队列
    vector<int> ans; // 存储结果

    int n = arr.size();

    // 先形成长度为k-1的窗口
    for (int i = 0; i < k - 1; i++)
    {
        // 维护双端队列的单调性（从大到小）
        while (!dq.empty() && arr[dq.back()] <= arr[i])
        {
            dq.pop_back(); // 移除队列尾部比当前元素小的元素
        }
        dq.push_back(i); // 将当前元素的索引加入队列
    }

    // 滑动窗口
    for (int i = k - 1; i < n; i++)
    {
        // 将当前元素加入队列
        while (!dq.empty() && arr[dq.back()] <= arr[i])
        {
            dq.pop_back(); // 移除队列尾部比当前元素小的元素
        }
        dq.push_back(i); // 将当前元素的索引加入队列

        // 收集答案
        ans.push_back(arr[dq.front()]); // 当前窗口的最大值是队列头部的元素

        // 移除队列头部已经不在窗口中的元素
        if (dq.front() == i - k + 1)
        {
            dq.pop_front();
        }
    }

    return ans;
}