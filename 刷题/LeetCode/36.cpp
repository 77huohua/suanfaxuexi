

class Solution {
public:
    bool bsPush(bitset<9>& Bitset, int op) {
        if (Bitset[op - 1]) {
            return false;
        }
        else
        {
            Bitset[op - 1] = true;
            return true;
        }
    }
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bitset<9>>> bs(3,vector<bitset<9>>(9));
        for (int i = 0;i < 9;i++) {
            for (int j = 0;j < 9;j++) {
                if (board[i][j] == '.')
                    continue;
                //行
                if (!bsPush(bs[0][i], board[i][j] - '0')) {
                    return false;
                }
                //列
                if (!bsPush(bs[1][j], board[i][j] - '0')) {
                    return false;
                }
                //格
                int k = (i / 3) * 3 + (j / 3);
                if (!bsPush(bs[2][k], board[i][j] - '0')) {
                    return false;
                }
            }
        }
        return true;
    }
};