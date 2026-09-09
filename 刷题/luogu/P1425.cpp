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

int a, b, c, d;

int main() {
	cin >> a >> b >> c >> d;
	int H = c - a;
	int M = d - b;
	if (M < 0) {
		H--;
		M += 60;
	}
	cout << H << ' ' << M;
}