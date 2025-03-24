#include <vector>
using namespace std;
class code
{

public:
    void swap(int &a, int &b); // 两数交换
    int Max(int a, int b);//返回最大值
    int sign(int n);//用于Max
    int flip(int n);//用于sign
    int Max2(int a, int b);
    
    /*给一个大小为n的数组，里面装的是0到n，缺了一个，找出来返回*/
    int missNumber(vector<int>& arr);
    /*求0到n的异或和，再求数组的异或和，两个异或，得到缺的数*/
};

void code::swap(int &a, int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
/*、
刚开始 a=a b=b
第一步 a=a^b b=b
然后   a=a^b b=a^b^b=a^(b^b)=a^0=a
然后   a=a^b^a=b b=a
*/

int code::Max(int a,int b)//问题 a-b可能溢出
{
    int c = a - b;
    int returnA = sign(c);
    // c非负,returnA=1;
    // c负数,returnA=0;
    int returnB = flip(returnA);
    // c非法,returnB=0;
    // c负数,returnB=1;

    return a * returnA + b * returnB;
}

int code::sign(int n)
{
    return flip(n >> 31);
}

int code::flip(int n)
{
    return n ^ 1;
}

int code::Max2(int a,int b)
{
    //c可能是溢出的
    int c=a-b;

    int sa = sign(a);//a的符号
    int sb = sign(b);
    int sc = sign(c);
    int diffAB=sa^sb;//判断A和B符号是否相反,相反为1,相同为0
    int sameAB = flip(diffAB);//与diffAB相反
    int returnA = diffAB * sa + sameAB * sc;//如果AB异号且a是整数 或 AB同号且c非负
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}

int code::missNumber(vector<int>& arr)
{
    int All = 0, has = 0;
    for (int i = 0; i < arr.size();i++)
    {
        
    }
}