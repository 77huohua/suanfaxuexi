#include <vector>
using namespace std;

vector<int> sum;

void NumArray(vector<int> nums)
{
    sum.push_back(0);
    for (int i = 0; i <= nums.size();i++)
    {
        sum.push_back(sum[i - 1] + nums[i - 1]);
    }
}

int sumRange(int left,int right)
{
    return sum[right + 1] - sum[left];
}