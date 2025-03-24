#include <vector>
#include <memory>
using namespace std;
class code
{

public:
    void swap(int &a, int &b); // 两数交换
    int Max(int a, int b);     // 返回最大值
    int sign(int n);           // 用于Max
    int flip(int n);           // 用于sign
    int Max2(int a, int b);

    /*给一个大小为n的数组，里面装的是0到n，缺了一个，找出来返回*/
    int missNumber(vector<int> &arr);
    /*求0到n的异或和，再求数组的异或和，两个异或，得到缺的数*/

    /*给定一个数组，其中只有一个数出现的频率为奇数，其他为偶数，求为奇数的那个数*/
    int singleNumber(vector<int> &arr);
    /*所有数都求异或，偶数频率的异或为0，奇数存留*/

    /*给定一个数组,其中有两个数出现的频率为奇数,其他为偶数,求那两个为奇数的那个数*/
    shared_ptr<int[]> singleNumber2(vector<int> &arr);
    /*所有数都求异或，得到A^B然后求A^B的最右侧的1，然后得知A和B2进制的第一个差异，创建第二个数，只对有差异的那一位是1的数异或，得到A或者B，然后与A^B异或得到另一个数*/

    /*数组中只有1种数出现次数小于m次,其他数都出现了m次，返回出现次数小于m次的那种数*/
    int find(vector<int> &arr, int m);
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

int code::Max(int a, int b) // 问题 a-b可能溢出
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

int code::Max2(int a, int b)
{
    // c可能是溢出的
    int c = a - b;

    int sa = sign(a); // a的符号
    int sb = sign(b);
    int sc = sign(c);
    int diffAB = sa ^ sb;                    // 判断A和B符号是否相反,相反为1,相同为0
    int sameAB = flip(diffAB);               // 与diffAB相反
    int returnA = diffAB * sa + sameAB * sc; // 如果AB异号且a是整数 或 AB同号且c非负
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}

int code::missNumber(vector<int> &arr)
{
    int All = 0, has = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        All ^= i;
        has ^= arr[i];
    }
    All ^= arr.size();
    return All ^ has;
}

int code::singleNumber(vector<int> &arr)
{
    int ret = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        ret ^= arr[i];
    }
    return ret;
}

shared_ptr<int[]> code::singleNumber2(vector<int> &arr)
{
    int eor1 = 0;
    for (auto i : arr)
    {
        eor1 ^= i;
    }
    int rightOne = eor1 ^ (-eor1);
    int eor2 = 0;
    for (auto i : arr)
    {
        if ((i & rightOne) == 0)
        {
            eor2 ^= i;
        }
    }
    shared_ptr<int[]> ret = make_shared<int[]>(2);
    ret[0] = eor2;
    ret[1] = eor2 ^ eor1;
    return ret;
}

int code::find(vector<int> &arr, int m)
{
    vector<int> cnts(32);
    for (auto i : arr)
    {
        for (int j = 0; j < 32; j++)
        {
            cnts[j] += (i >> j) & 1;
        }
    }
    // 把每一位都统计进来，出现次数小于m的二进制位对过去的位置%m后不等于0，，得到m的二进制
    int ans = 0;
    for (int i = 0; i < 32; i++)
    {
        if (cnts[i] % m != 0)
        {
            ans |= 1 << i;
        }
    }
    // 把二进制转10进制
    return ans;
}
//