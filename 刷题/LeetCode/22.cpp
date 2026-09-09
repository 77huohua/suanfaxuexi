class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string tmp(n << 1, 0);
        vector<string> ret;
        auto dfs = [&](this auto&& dfs, int l, int r)->void {
            if (r == n) {
                ret.push_back(tmp);
                return;
            }
            if (l < n) {
                tmp[l + r] = '(';
                dfs(l + 1, r);
            }
            if (r < l) {
                tmp[l + r] = ')';
                dfs(l, r + 1);
            }
            };
        dfs(0, 0);
        return ret;
    }
};