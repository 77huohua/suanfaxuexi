class Solution {
public:
    int longestValidParentheses(string s) {
        int n=s.size();
        bitset<30010> is_valid;
        stack<int> st;
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                st.push(i);
            }else if(!st.empty()){
                is_valid[i]=is_valid[st.top()]=true;
                st.pop();
            }
        }
        int ans=0,cnt=0;
        for(int i=0;i<n;i++){
            if(is_valid[i]){
                cnt++;
                ans=max(ans,cnt);
            }else{
                cnt=0;
            }
        }
        return ans;
    }
};