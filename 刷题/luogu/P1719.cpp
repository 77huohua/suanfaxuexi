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

const int MAXN = 130;
int arr[MAXN][MAXN];
int sum[MAXN][MAXN];
int n;

int main() {
	cin >> n;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			cin >> arr[i][j];
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
		}
	}
	int ans = 0;
	for (int i = 0;i <= n;i++) {
		for (int j = 0;j <= n;j++) {
			for (int k = i + 1;k <= n;k++) {
				for (int l = j + 1;l <= n;l++) {
					ans = max(ans, sum[k][l] - sum[k][j]-sum[i][l]+sum[i][j]);
				}
			}
		}
	}
	cout << ans << endl;
}