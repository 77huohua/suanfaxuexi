class Solution {
public:
    vector<vector<int>> ret;
    vector<int> now;
    vector<int> Candidates;
    void dfs(int i, int left) {
        //终止条件
        if (left < 0) {
            return;
        }
        if (left == 0) {
            ret.push_back(now);
            return;
        }
        if (i == Candidates.size()) {
            return;
        }

        //拿
        now.push_back(Candidates[i]);
        dfs(i+1, left - Candidates[i]);
        //回溯
        now.pop_back();
        //不拿
        while (i+1<Candidates.size()&&Candidates[i]==Candidates[i+1])
        {
            i++;
        }
        dfs(i + 1, left);
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        Candidates = candidates;
        dfs(0, target);
        return ret;
    }
};