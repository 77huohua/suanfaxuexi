class Solution {
public:
    string arr[10] = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
    vector<string> letterCombinations(string digits) {
        if (digits.size()==0) {
            return {};
        }
        vector<string> ret;
        string path(digits.size(), 0);
        auto dfs = [&](this auto&& dfs, int i)->void {
            if (i == digits.size()) {
                ret.push_back(path);
                return;
                }
            for (auto c : arr[digits[i] - '0']) {
                path[i] = c;
                dfs(i + 1);
            }
            };
        dfs(0);
        return ret;
    }
};