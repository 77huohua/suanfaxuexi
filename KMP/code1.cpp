#include <string>
#include <vector>
using namespace std;

vector<int> nextArray(string& str)
{
    int m = str.size();
    if(m==1)
    {
        return vector<int>(1, -1);
    }
    vector<int> next(m);
    next[0] = -1;
    next[1] = 0;
    int i = 2, cn = 0;
    while (i<m)
    {
        if(str[i-1]==str[cn])
        {
            next[i++] = ++cn;
        }
        else if(cn>0)
        {
            cn = next[cn];
        }
        else
        {
            next[i++] = 0;
        }
    }
    return next;
}

int kmp(string s1,string s2)
{
    //s1中当前比对的位置是x
    //s2中当前比对的位置是y
    int n = s1.size(), m = s2.length(), x = 0, y = 0;
    vector<int> next = nextArray(s2);
    while (x<n&&y<m)
    {
        if(s1[x]==s2[y])
        {
            x++;
            y++;
        }
        else if(y==0)
        {
            x++;
        }
        else
        {
            y = next[y];
        }
    }
    return y == m ? x - y : -1;
}

