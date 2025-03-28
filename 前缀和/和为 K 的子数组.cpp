/*给你一个整数数组 nums 和一个整数 aim ，请你统计并返回 该数组中和为 aim 的子数组的个数 。
子数组是数组中元素的连续非空序列。*/

#include <vector>
#include <unordered_map>
using namespace std;

int ans;//初始化结果计数器为0
unordered_map<int, int> map;//创建一个哈希表来储存前缀和及出现次数

int subarraySum(vector<int> nums,int aim)
{
    map[0] = 1;//前缀和为0的出现次数设为1
    for (int i = 0, sum = 0; i < nums.size();i++)
    {
        //遍历数组,同时维护一个累加和sum
        sum += nums[i];//将当前元素加入累加和sum中
        //检查哈希表中是否存在键为(sum-aim)的项,如果存在,将其对应的值加到ans中
        if(map.find(sum-aim)!=map.end())
        {
            ans += map[sum - aim];
        }

        //将当前累加和sum作为键,其出现次数加1作为值存入哈希表中
        map[sum]++;
    }
    return ans;//返回结果计数器ans的值,即满足条件的子数组数量
}