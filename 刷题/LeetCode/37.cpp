class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        bool row_has[9][9]{};
        bool col_has[9][9]{};
        bool sub_box_has[3][3][9]{};
        vector<pair<int,int>> empty_pos;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                char b=board[i][j];
                if(b=='.'){
                    empty_pos.emplace_back(i,j);
                }else{
                    int x=b-'1';
                    row_has[i][x]=col_has[j][x]=sub_box_has[i/3][j/3][x]=true;
                }
            }
        }
        auto get_candidates=[&](int i,int j)->int{
            int candidates=9;
            for(int x=0;x<9;x++){
                if(row_has[i][x]||col_has[j][x]||sub_box_has[i/3][j/3][x]){
                    candidates--;
                }
            }
            return candidates;
        };
        priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> empty_pq;
        for(auto& [i,j]:empty_pos){
            empty_pq.emplace(get_candidates(i,j),i,j);
        }
        auto dfs=[&](this auto&& dfs)->bool{
            if(empty_pq.empty()){
                return true;
            }
            auto [_,i,j]=empty_pq.top();
            empty_pq.pop();

            int candidates=0;
            for(int x=0;x<9;x++){
                if(row_has[i][x]||col_has[j][x]||sub_box_has[i/3][j/3][x]){
                    continue;
                }
                board[i][j]='1'+x;
                row_has[i][x]=col_has[j][x]=sub_box_has[i/3][j/3][x]=true;

                if(dfs()){
                    return true;
                }

                row_has[i][x]=col_has[j][x]=sub_box_has[i/3][j/3][x]=false;
                candidates++;
            }
            empty_pq.emplace(candidates,i,j);
            return false;

        };
        dfs();
    }
};