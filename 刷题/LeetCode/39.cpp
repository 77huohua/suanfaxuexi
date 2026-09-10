class Solution {
public:
    vector<vector<int>> ret;
    vector<int> now;
    vector<int> Candidates;
    void dfs(int i, int left) {
        //终止条件
        if (i == Candidates.size()) {
            return;
        }
        if (left < 0) {
            return;
        }
        if (left == 0) {
            ret.push_back(now);
            return;
        }

        //拿
        now.push_back(Candidates[i]);
        dfs(i, left - Candidates[i]);
        //回溯
        now.pop_back();
        //不拿
        dfs(i + 1, left);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        Candidates = candidates;
        dfs(0, target);
        return ret;
    }
};