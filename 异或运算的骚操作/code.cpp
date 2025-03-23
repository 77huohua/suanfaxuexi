class code
{

public:
    void swap(int &a, int &b); // 两数交换
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