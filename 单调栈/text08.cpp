// 大鱼吃小鱼问题
// 给定一个数组arr，每个值代表鱼的体重
// 每一轮每条鱼都会吃掉右边离自己最近比自己体重小的鱼，每条鱼向右找只吃一条
// 但是吃鱼这件事是同时发生的，也就是同一轮在A吃掉B的同时，A也可能被别的鱼吃掉
// 如果有多条鱼在当前轮找到的是同一条小鱼，那么在这一轮，这条小鱼同时被这些大鱼吃
// 请问多少轮后，鱼的数量就固定了
// 比如 : 8 3 1 5 6 7 2 4
// 第一轮 : 8吃3；3吃1；5、6、7吃2；4没有被吃。数组剩下 8 5 6 7 4
// 第二轮 : 8吃5；5、6、7吃4。数组剩下 8 6 7
// 第三轮 : 8吃6。数组剩下 8 7
// 第四轮 : 8吃7。数组剩下 8。
// 过程结束，返回4

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100001; // 最大数组大小
int arr[MAXN];           // 存储鱼的体重
int n;                   // 鱼的数量
int stack[MAXN][2];      // 栈，用于存储鱼的体重和对应的轮数
int r;                   // 栈顶指针

int main()
{
    // 从标准输入读取数据
    while (cin >> n)
    { // 读取每组输入
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i]; // 读取每条鱼的体重
        }
        cout << turns() << endl; // 计算并输出结果
    }
    return 0;
}

// 计算最大轮数的函数
int turns()
{
    r = 0;       // 重置栈顶指针
    int ans = 0; // 最大轮数

    // 从后往前处理每条鱼
    for (int i = n - 1, curTurns; i >= 0; i--)
    {
        curTurns = 0; // 当前鱼的轮数初始化为0

        // 当栈不为空且栈顶鱼的体重小于当前鱼的体重时
        while (r > 0 && stack[r - 1][0] < arr[i])
        {
            // 更新当前轮数为当前轮数+1和栈顶鱼轮数的最大值
            curTurns = max(curTurns + 1, stack[--r][1]);
        }

        // 将当前鱼的体重和轮数压入栈
        stack[r][0] = arr[i];
        stack[r++][1] = curTurns;

        // 更新最大轮数
        ans = max(ans, curTurns);
    }

    return ans; // 返回最大轮数
}