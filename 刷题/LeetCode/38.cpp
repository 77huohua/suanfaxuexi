class Solution {
public:
    string countAndSay(int n) {
        if(n==1){
            return "1";
        }
        string s=countAndSay(n-1);
        string ret="";
        for(int i=0;i<s.size();i++){
            char cur=s[i];
            int longc=1;
            while(i+1<s.size()&&s[i]==s[i+1]){
                i++;
                longc++;
            }
            ret=ret+to_string(longc)+cur;
        }
        return ret;
    }
};