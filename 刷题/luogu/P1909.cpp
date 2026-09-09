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

int n;
pair<int, int> arr[3];

int main() {
	cin >> n;
	for (int i = 0;i < 3;i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	cout << min({ (n + arr[0].first - 1) / arr[0].first * arr[0].second,(n + arr[1].first - 1) / arr[1].first * arr[1].second,(n + arr[2].first - 1) / arr[2].first * arr[2].second });
}