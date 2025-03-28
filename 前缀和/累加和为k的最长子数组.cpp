// 返回无序数组中累加和为给定值的最长子数组长度
// 给定一个无序数组arr, 其中元素可正、可负、可0
// 给定一个整数aim
// 求arr所有子数组中累加和为aim的最长子数组长度

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 100001;
vector<int> arr(MAXN);
int n, aim;
unordered_map<int, int> map;

int ans;//累加和

int compute()
{
    map.clear();
    map[0] = -1;//初始化前缀和为0的位置为-1
    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n;i++)
    {
        // sum:0...i整体累加和
        sum += arr[i];

        //sum-aim 这个累加和最早出现在哪
        if(map.find(sum-aim)!=map.end())
        {
            ans = max(ans, i - map[sum - aim]);
        }
        if(map.find(sum)==map.end())
        {
            map[sum] = i;
        }
        return ans;
    }
}

int main()
{
    cin >> n >> aim;
    for (int i = 0; i < n;i++)
    {
        cin >> arr[i];
    }
    cout << compute();
}