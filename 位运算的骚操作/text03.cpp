/*返回大于等于n的最小的2的某次幂*/

class text03
{
public:
    int near2power(int n);
};

int text03::near2power(int n)
{
    if (n <= 0)
        return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}
/*假如10100,先-1 成10011(主要是防止它正好是2的某次幂)
左移取或得 11---，在左移的1111-同理，最后得到11111，+1得到答案*/