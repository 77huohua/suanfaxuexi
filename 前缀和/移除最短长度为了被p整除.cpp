// 使数组和能被P整除
// 给你一个正整数数组 nums，请你移除 最短 子数组（可以为 空）
// 使得剩余元素的 和 能被 p 整除。 不允许 将整个数组都移除。
// 请你返回你需要移除的最短子数组的长度，如果无法满足题目要求，返回 -1 。
// 子数组 定义为原数组中连续的一组元素。

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int minSubarray(vector<int>& nums,int p)
{
    //计算整个数组的余数
    int mod = 0;
    for(int num:nums)
    {
        mod = (mod + num) % p;
    }
    if(mod==0)
    {
        return 0;//如果余数为0,说明整个数组已经满足条件
    }

    //哈希表用于储存前缀和的余数及其对应的位置
    unordered_map<int, int> map;
    map[0] = -1;//初始化:前缀和余数为0的位置是-1(表示没有元素时的前缀和)

    int ans = INT_MAX;//初始化答案为最大值
    int cur = 0;//当前前缀和的余数

    for (int i = 0; i < nums.size();i++)
    {
        cur = (cur + nums[i]) % p;//计算当前前缀和的余数

        //计算需要查找的目标余数
        int find = (cur >= mod) ? (cur - mod) : (cur + p - mod);

        //如果目标余数存在于哈希表中,说明找到了一个子数组
        if(map.find(find)!=map.end())
        {
            ans = min(ans, i - map[find]);//更新最短子数组长度
        }

        //如果当前余数不在哈希表中,记录它的位置
        if(map.find(cur)==map.end())
        {
            map[cur] = i;
        }
    }

    //如果ans仍为初始值,说明没有找到满足条件的子数组,返回-1
    return (ans == nums.size()) ? -1 : ans;
}

int main()
{
    vector<int> nums;
    int p, num;

    //从标准输入流读取数据
    int n;
    cin >> n;//输入数组长度
    for (int i = 0; i < n;i++)
    {
        cin >> num;
        nums.push_back(num);//将输入的数字存入数组
    }
    cin >> p;//输入模数p
    cout << minSubarray(nums, p) << endl;//输出结果
    return 0;
}