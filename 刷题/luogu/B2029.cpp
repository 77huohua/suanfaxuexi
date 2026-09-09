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

int h, r;

int main() {
	cin >> h >> r;
	double del = 3.14 * r * r * h;
	cout << ceil(20000 / del) << endl;
}