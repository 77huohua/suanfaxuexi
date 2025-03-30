// 最强祝福力场
// 小扣在探索丛林的过程中，无意间发现了传说中"落寞的黄金之都"
// 而在这片建筑废墟的地带中，小扣使用探测仪监测到了存在某种带有「祝福」效果的力场
// 经过不断的勘测记录，小扣将所有力场的分布都记录了下来
// forceField[i] = [x,y,side]
// 表示第 i 片力场将覆盖以坐标 (x,y) 为中心，边长为 side 的正方形区域。
// 若任意一点的 力场强度 等于覆盖该点的力场数量
// 请求出在这片地带中 力场强度 最强处的 力场强度
// 注意：力场范围的边缘同样被力场覆盖。

#include <set>
#include <vector>
using namespace std;
class Solution
{
private:
    // 在排序后的set中查找v的位置
    int findRank(const set<long long> &nums, long long v)
    {
        auto it = nums.lower_bound(v);
        return distance(nums.begin(), it) + 1; // 返回位置索引
    }

    // 在差分数组中添加矩形区域的增量
    void add(vector<vector<int>> &diff, int a, int b, int c, int d)
    {
        diff[a][b] += 1;
        diff[c + 1][d + 1] += 1;
        diff[c + 1][b] -= 1;
        diff[a][d + 1] -= 1;
    }

public:
    // 计算最大祝福力场的覆盖次数
    int fieldOfGreatestBlessing(vector<vector<int>> &fields)
    {
        int n = fields.size();
        if (n == 0)
            return 0;

        set<long long> xs, ys;

        // 收集所有x和y坐标
        for (int i = 0; i < n; i++)
        {
            long long x = fields[i][0];
            long long y = fields[i][1];
            long long r = fields[i][2];
            xs.insert((x << 1) - r);
            xs.insert((x << 1) + r);
            ys.insert((y << 1) - r);
            ys.insert((y << 1) + r);
        }

        // 将set转换为vector
        vector<long long> xVec(xs.begin(), xs.end());
        vector<long long> yVec(ys.begin(), ys.end());

        int sizex = xVec.size();
        int sizey = yVec.size();

        // 初始化差分数组
        vector<vector<int>> diff(sizex + 2, vector<int>(sizey + 2, 0));

        // 处理每个力场，更新差分数组
        for (int i = 0; i < n; i++)
        {
            long long x = fields[i][0];
            long long y = fields[i][1];
            long long r = fields[i][2];
            int a = findRank(xs, (x << 1) - r);
            int b = findRank(ys, (y << 1) - r);
            int c = findRank(xs, (x << 1) + r);
            int d = findRank(ys, (y << 1) + r);
            add(diff, a, b, c, d);
        }

        int ans = 0;
        // 构建前缀和数组并找到最大值
        for (int i = 1; i < diff.size(); i++)
        {
            for (int j = 1; j < diff[0].size(); j++)
            {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
                ans = max(ans, diff[i][j]);
            }
        }
        return ans;
    }
};