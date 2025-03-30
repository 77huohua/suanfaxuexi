// 航班预订统计
    // 这里有 n 个航班，它们分别从 1 到 n 进行编号。
    // 有一份航班预订表 bookings ，
    // 表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi]
    // 意味着在从 firsti 到 lasti
    // （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
    // 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。

    #include <vector>
using namespace std;

vector<int> corpFlightBookings(vector<vector<int>>&bookings,int n)
{
    //创建一个差分数组,用于记录每个座位的预订变化
    vector<int> cnt(n + 2, 0);

    //遍历每个预订操作
    for(auto& book:bookings)
    {
        //对于每个预订操作,更新差分数组
        cnt[book[0]] += book[2];//在开始座位加上预订的座位数
        cnt[book[1] + 1] -= book[2];//在结束座位的下一个位置减去预订的座位数
    }

    //计算前缀和,还原每个座位的最终预订情况
    for (int i = 1; i < cnt.size();i++)
    {
        cnt[i] += cnt[i - 1];//当前座位的预订数等于前一个座位的预订数加上当前的变化
    }

    //提取结果数组
    vector<int> ans(n);
    for (int i = 0; i < n;i++)
    {
        ans[i] = cnt[i + 1];//将差分数组中的结果复制到结果数组中
    }
    return ans;
}