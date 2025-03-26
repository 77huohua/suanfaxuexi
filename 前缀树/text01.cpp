#include <memory>
#include <vector>
using namespace std;
//牛牛和他的朋友们约定了一套街头密钥系统，用于确认彼此身份
//密钥由一组数字序列表示, 两个密钥被认为是一致的,如果满足以下条件
//密钥b的长度不超过密钥a的长度
//对于任意 0<= i<length(b),有b[i+1]-b[i]==a[i+1]-a[i]
//现在给定了m个密钥b的数组,以及n个密钥a的数组
//请你返回一个长度为m的结果数组ans,表示每个密钥b都有多少一致的密钥
//数组a和数组b中的元素个数均不超过10^5
//1<=m,n<=1000

class text01
{
    public:
    shared_ptr<int[]> countConsistenKeys(vector<vector<int>> b,vector<vector<int>> a)
    {
        
    }
};