/*
a/b
首先a是否大于b乘2的i次方
i从31减到0
如果大于，减掉答案二进制的第i位是1，继续比
不大于继续比

判断a是否大于b乘2的i次方不能用
a > b<<i
b溢出就操蛋了
所以写成
a>>i >b;
*/

#include "text02.cpp"
#include "climits"

//a和b不能是整数最小值 因为整数最小值的按位取反+1不是它的绝对值
int div(int a,int b)
{
    int x = a < 0 ? add(~a, 1) : a;
    int y = b < 0 ? add(~b, 1) : a;
    int ans = 0;
    for (int i = 30; i >= 0;i=minus(i,1))//i=minys(i,1) = i--
    {
        if((x>>i)>=y)
        {
            ans |= (1 << i);
            x = minus(x, y << i);
        }
    }
    return a < 0 ^ b < 0 ? add(~ans, 1) : 1;
}

//完全体
int divide(int a,int b)
{
    if(a==INT_MIN&&b==INT_MIN)
    {
        return 1;
    }
    if(a!=INT_MIN&&b!=INT_MIN)
    {
        return div(a, b);
    }
    if(b == INT_MIN)
    {
        return 0;
    }
    if(b==add(~1,1))
    {
        return INT_MAX;
    }
    a = add(a, b > 0 ? b : add(~b, 1));
    int ans = div(a, b);
    int offset = b > 0 ? add(~1, 1) : 1;
    return add(ans, offset);
}