#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<climits>
#include<cmath>
#include<queue>
#include<cstring>
#include<bit>
#include<memory>
#include<bitset>
#include<string>
#include<format>
using namespace std;


int main() {
    long long s, v;
    cin >> s >> v;
    long long walk = (s + v - 1) / v;
    long long total = walk + 10;
    long long deadline = 8 * 60;
    long long depart = ((deadline - total) % 1440 + 1440) % 1440;  
    int H = depart / 60;
    int M = depart % 60;
    cout << format("{:02d}:{:02d}\n", H, M);
    return 0;
}