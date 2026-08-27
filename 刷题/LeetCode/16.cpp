class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int ret = 0x77ffffff;
        for (int a = 0; a < nums.size(); a++)
        {
            if (a > 0 && nums[a] == nums[a - 1])
                continue;
            int b = a + 1;
            int c = nums.size() - 1;
            while (b < c)
            {
                if (nums[a] + nums[b] + nums[c] == target)
                {
                    return target;
                }
                if (abs(ret - target) > abs(nums[a] + nums[b] + nums[c] - target))
                {
                    ret = nums[a] + nums[b] + nums[c];
                }
                if (nums[a] + nums[b] + nums[c] < target)
                {
                    b++;
                }
                else
                {
                    c--;
                }
            }
        }
        return ret;
    }
};