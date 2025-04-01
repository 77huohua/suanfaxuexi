// 你可以安排的最多任务数目
// 给你 n 个任务和 m 个工人。每个任务需要一定的力量值才能完成
// 需要的力量值保存在下标从 0 开始的整数数组 tasks 中，
// 第i个任务需要 tasks[i] 的力量才能完成
// 每个工人的力量值保存在下标从 0 开始的整数数组workers中，
// 第j个工人的力量值为 workers[j]
// 每个工人只能完成一个任务，且力量值需要大于等于该任务的力量要求值，即workers[j]>=tasks[i]
// 除此以外，你还有 pills 个神奇药丸，可以给 一个工人的力量值 增加 strength
// 你可以决定给哪些工人使用药丸，但每个工人 最多 只能使用 一片 药丸
// 给你下标从 0 开始的整数数组tasks 和 workers 以及两个整数 pills 和 strength
// 请你返回 最多 有多少个任务可以被完成。

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

// 任务分配函数
int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills, int strength)
{
    // 对任务和工人的能力进行排序
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    int tsize = tasks.size();
    int wsize = workers.size();
    int ans = 0;

    // 使用二分查找确定最多可以完成的任务数量
    for (int l = 0, r = min(tsize, wsize), m; l <= r;)
    {
        m = (l + r) / 2; // 中点，尝试完成m个任务
        // 检查是否可以完成m个任务
        if (f(tasks, workers, 0, m - 1, wsize - m, wsize - 1, strength, pills))
        {
            ans = m; // 如果可以完成，记录结果并尝试更大的值
            l = m + 1;
        }
        else
        {
            r = m - 1; // 如果不能完成，尝试更小的值
        }
    }
    return ans;
}

// 检查是否可以完成指定数量的任务
bool f(const vector<int> &tasks, const vector<int> &workers,
       int tl, int tr, int wl, int wr, int s, int pills)
{
    deque<int> dq; // 双端队列，用于存储可以完成的任务
    int cnt = 0;   // 已使用的药的数量

    // 遍历工人和任务
    for (int i = wl, j = tl; i <= wr; i++)
    {
        // 工人i尝试完成任务j到tr之间的任务
        while (j <= tr && tasks[j] <= workers[i])
        {
            dq.push_back(j); // 如果工人i可以完成任务j，将任务加入队列
            j++;
        }

        if (!dq.empty() && tasks[dq.front()] <= workers[i])
        {
            dq.pop_front(); // 如果队列不为空且任务可以完成，移除任务
        }
        else
        {
            // 如果任务需要吃药才能完成
            while (j <= tr && tasks[j] <= workers[i] + s)
            {
                dq.push_back(j); // 将可以完成的任务加入队列
                j++;
            }
            if (!dq.empty())
            {
                cnt++;         // 使用一个药
                dq.pop_back(); // 移除队列中的最后一个任务（因为工人i吃了药后可以完成这个任务）
            }
            else
            {
                return false; // 如果队列为空，说明无法完成任务
            }
        }
    }
    return cnt <= pills; // 检查使用的药是否在允许范围内
}
