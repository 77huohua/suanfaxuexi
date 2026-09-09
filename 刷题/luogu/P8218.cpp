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

const int MAXN = 100010;
int sum[MAXN];
int arr[MAXN];
int n, m;

int main() {
	cin >> n;
	for (int i = 1;i <= n;i++) {
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}
	cin >> m;
	for (int i = 1,l,r;i <= m;i++) {
		cin >> l >> r;
		cout << sum[r] - sum[l - 1] << endl;
	}
}