// 返回无序数组中正数和负数个数相等的最长子数组长度
// 给定一个无序数组arr，其中元素可正、可负、可0
// 求arr所有子数组中正数与负数个数相等的最长子数组的长度

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

const int MAXN = 100001;
vector<int> arr(MAXN);
int n;
unordered_map<int, int> map;

int compute()
{
    map.clear();
    map[0] = -1;//初始化哈希表,前缀和为0的位置是-1
    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n;i++)
    {
        sum += arr[i];//计算前缀和
        if(map.find(sum)!=map.end())
        {
            //如果当前前缀和已经在哈希表中存在,说明找到了一个子数组的和为0
            ans = max(ans, i - map[sum]);
        }
        else
        {
            //否则将当前前缀和及其索引存入哈希表
            map[sum] = i;
        }
    }
    return ans;
}

int main()
{
    string line;
    while ((getline(cin,line)))
    {
        istringstream iss(line);
        iss >> n;//读取数组长度
        arr.resize(n);//调整数组大小
        for (int i = 0; i < n;i++)
        {
            int num;
            iss >> num;
            if(num!=0)
            {
                arr[i] = (num > 0) ? 1 : -1;//将非零值转换为1或-1
            }
            else
            {
                arr[i] = 0;//零值保持不变
            }
        }
        cout << compute() << endl;//输出结果
    }
    return 0;
}