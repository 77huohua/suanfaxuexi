#include "text01.cpp"

/*a-b=a+(-b)
-b=add(~b,1)
*/

int minus(int a,int b)
{
    return add(a, add(~b, 1));
}