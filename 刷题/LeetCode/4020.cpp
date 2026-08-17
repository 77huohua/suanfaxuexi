#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int elevatorRequests(int n, vector<int> &requests)
    {
        int now = 0;
        int ans = 0;
        for (auto i : requests)
        {
            ans += abs(now - i);
            now = i;
        }
        return ans;
    }
};