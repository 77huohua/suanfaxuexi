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
using namespace std;

double a, b, c, p;

int main() {
	cin >> a >> b >> c;
	p = (a + b + c) / 2;
	printf("%.1f", sqrt(p * (p - a) * (p - b) * (p - c)));
}