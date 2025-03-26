#include <memory>
using namespace std;
class NQueens
{
public:
    int totalNQueens1(int n)
    {
        if (n < 1)
        {
            return 0;
        }
        shared_ptr<int[]> arr = make_shared<int[]>(n);
        return f1(0, arr, n);
    }

    // i:当前来到的行
    // path:0...i-1行的皇后,都摆在了哪些列
    // 返回 : 0...i-1行已经摆完了，i...n-1行可以去尝试的情况下还能找到几种有效的方法

    int f1(int i, shared_ptr<int[]> &path, int n)
    {
        if (i == n)
        {
            return 1;
        }
        int res = 0;
        for (int j = 0; j < n; j++)
        {
            if (check(path, i, j))
            {
                path[i] = j;
                res += f1(i + 1, path, n);
            }
        }
        return res;
    }

    // 当前在i行 j列的位置, 摆了一个皇后
    // 0...1-i行的皇后状况,path[0...i-1]
    // 返回会不会冲突,不会冲突,有效!true
    // 会冲突,无效返回false
    bool check(shared_ptr<int[]> &path, int i, int j)
    {
        // 当前行 i
        // 当前列 j
        for (int k = 0; k < i; k++)
        {
            // 0...i-1
            // 之前行 k
            // 之前列 path[k]
            if (j == path[k] || abs(i - k) == abs(path[k] - j))
            {
                return 0;
            }
        }
        return 1;
    }

    //用位信息表示路径实现的N皇后问题
    int totalNQueen2(int n)
    {
        if(n<1)
        {
            return 0;
        }
        int limit = (1 << n) - 1;
        return f2(limit, 0, 0, 0);
    }

    //之前皇后的列的影响:col
    //之前皇后的左下对角线的影响: left
    //之前皇后的右下对角线的影响: right
    int f2(int limit,int col,int left,int right)
    {
        if(col==limit)
        {
            //所以皇后放完了
            return 1;
        }
        //总限制
        int ban = col | left | right;
        //~ban: 1可放皇后 0不能放
        int candidate = limit & (~ban);
        //放置皇后的尝试
        int place = 0;
        //一共有多少有效的方法
        int ans = 0;
        while (candidate!=0)
        {
            //提取出最右侧的1
            //candidat 0 0 1 1 1 0
            //place    0 0 0 0 1 0
            place = candidate & (-candidate);
            //candidat 0 0 1 1 0 0
            candidate ^= place;
            ans += f2(limit, col | place, (left | place) >> 1, (right | place) << 1);
        }
        return ans;
    }
};