/*求n是不是3的幂*/

class text02
{
public:
    bool isPower0fThree(int n);
};

bool text02::isPower0fThree(int n)
{
    return n > 0 && 1162261467 % n == 0; // 这个数是3的19次幂,int里最大的3的某次幂，如果一个数只是3的次幂，则一定是他的倍数，有别的因子就不会是0
}
