class text01
{
public:
    // 判断一个数是否是2的n次幂
    bool isPower0fTow(int n);
};

bool text01::isPower0fTow(int n)
{
    return n > 0 && n == (n & -n);
}

