// 表现良好的最长时间段
// 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数
// 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是 劳累的一天
// 所谓 表现良好的时间段 ，意味在这段时间内，「劳累的天数」是严格 大于 不劳累的天数
// 请你返回 表现良好时间段 的最大长度

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longesWPI(vector<int>& hours)
{
    //使用哈希表记录某个前缀和最早出现的位置
    unordered_map<int, int> map;
    //初始化:前缀和和为0的位置是-1(表示没有元素时的前缀和)
    map[0] = -1;
    int ans = 0;//最长满足条件的子数组长度
    int sum = 0;//当前前缀和
    for (int i = 0; i < hours.size();i++)
    {
        //计算前缀和:大于8小时的工作日加1,否则减1
        sum += (hours[i] > 8) ? 1 : -1;

        //如果当前前缀和大于0,说明从开头到当前位置的子数组满足条件
        if(sum>0)
        {
            ans = i + 1;//更新最长子数组长度
        }
        else
        {
            //如果当前前缀和减1存在于哈希表中,说明存在一个子数组的和为1
            if(map.find(sum-1)!=map.end())
            {
                ans = max(ans, i - map[sum - 1]);//更新最长子数组长度
            }
        }

        //如果当前前缀和不在哈希表中,记录它的位置
        if(map.find(sum)==map.end())
        {
            map[sum] = i;
        }
    }
    return ans;//返回最长满足条件的子数组长度
}

int main()
{
    vector<int> hours;
    int n, num;

    //从标准输入流读取数据
    cin >> n;//输入数组长度
    for (int i = 0; i < n;i++)
    {
        cin >> num;
        hours.push_back(num);//将输入的数字存入数组
    }

    cout << longesWPI(hours) << endl;//输出结果

    return 0;
}