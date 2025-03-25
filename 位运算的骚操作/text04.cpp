/*给你两个整数left 和 right ,表示区间[left,right]
返回此区间所有数字&的结果
包含left,right端点*/

class text04
{
public:
    int rangeBitwiseAnd(int left, int right);
};

int text04::rangeBitwiseAnd(int left, int right)
{
    while ((left < right))
    {
        right -= right & -right;
    }
    return right;
}

/*假如right>left
设right   100010010
则right-1=100010001
因为 right>left 所以right必然要与right-1按位与
则right最后一位1必然保不住
类推下去*/
