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

int Mother;
int Cur;

int main() {
	for (int i = 1;i <= 12;i++) {
		int tmp;
		cin >> tmp;
		Cur += 300;
		Cur -= tmp;
		if (Cur < 0) {
			cout << -i << endl;
			return 0;
		}
		Mother += Cur / 100;
		Cur %= 100;
	}
	cout << Mother * 120 + Cur << endl;
	return 0;
}