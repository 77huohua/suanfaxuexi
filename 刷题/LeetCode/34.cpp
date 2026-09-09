class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto Lit = lower_bound(nums.begin(), nums.end(), target);
        if (!(Lit != nums.end() && *Lit == target)) 
        {
            return{ -1,-1 };
        }
        auto Rit = upper_bound(nums.begin(), nums.end(), target);
        return { (int)(Lit - nums.begin()),(int)(Rit - nums.begin())-1 };
    }
};