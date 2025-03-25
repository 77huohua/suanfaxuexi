#include "text01.cpp"

/*
二进制乘法竖式和十进制一致

如 a 001011
   b 000110
   ---------X
     000000
    001011
   001011 
   ---------+
    1000010
*/

int multiply(int a,int b)
{
    int ans = 0;
    while (b!=0)
    {
        if((b&1)!=0)//b的最后一位不为0
        {
            ans = add(ans, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return ans;
}