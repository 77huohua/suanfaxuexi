#include <memory>
using namespace std;

class bitset
{
    public:
        shared_ptr<int[]> set;
        bitset(int n);
        void add(int num);//添加
        void remove(int num);//删除
        void reverse(int num);//如果有就删除，没有就添加
};

bitset::bitset(int n)
{
    set = make_shared<int[]>((n + 31) / 32); //(a+b-1)/b=a/b向上取整
}

void bitset::add(int num)
{
    set[num / 32] |= 1 << (num % 32);
}

void bitset::remove(int num)
{
    set[num / 32] = set[num / 32] & (~(1 << (num % 32)));
}

void bitset::reverse(int num)
{
    set[num / 32] ^= 1 << (num % 32);
}


