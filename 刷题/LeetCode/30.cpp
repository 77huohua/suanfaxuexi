class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int WordLen=words[0].size();
        int WindowLen=WordLen*words.size();
        map<string,int> TargetCnt;
        for(auto& w:words){
            TargetCnt[w]++;
        }
        vector<int>Ans;
        for(int Start=0;Start<WordLen;Start++){
            map<string,int> Cnt;
            int Overload=0;//拼接过多的单词数量
            for(int Right=Start+WordLen;Right<=s.size();Right+=WordLen){
                string InWord=s.substr(Right-WordLen,WordLen);
                if(Cnt[InWord]==TargetCnt[InWord]){
                    Overload++;
                }
                Cnt[InWord]++;
                int Left=Right-WindowLen;
                if(Left<0){
                    continue;
                }
                if(Overload==0){
                    Ans.push_back(Left);
                }
                string OutWord=s.substr(Left,WordLen);
                Cnt[OutWord]--;
                if(Cnt[OutWord]==TargetCnt[OutWord]){
                    Overload--;
                }
            }
        }
        return Ans;
    }
};