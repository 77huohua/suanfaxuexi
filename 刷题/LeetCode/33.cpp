class Solution {
public:
    int search(vector<int>& nums, int target) {
        int Last = *nums.rbegin();
        int l = -1, r = ((int)nums.size()) - 1;
        while (l+1<r)
        {
            int mid = l + ((r - l) >> 1);
            int x = nums[mid];
            if (target > Last && Last >= x) {
                r = mid;
            }
            else if (x > Last && Last >= target) {
                l = mid;
            }
            else
            {
                if (x < target) {
                    l = mid;
                }
                else
                {
                    r = mid;
                }
            }
        }
        return nums[r] == target ? r : -1;
    }
};