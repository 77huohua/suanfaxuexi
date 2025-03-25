/*加法
两数相加等于无进位相加 加上进位
无进位相加为 a^b
进位为 a&b<<1
一直循环此操作直到进位为0
*/

int add(int a,int b)
{
    int ans = 0;
    while (b!=0)
    {
        ans = a ^ b;
        b = (a & b) << 1;
        a = ans;
    }
    return ans;
}