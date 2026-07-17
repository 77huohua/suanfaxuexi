#include<iostream>
using namespace std;

int  n, k,ans;
int pos;

int main() {
	int t;
	cin >> t;
	while (t--)
	{
		ans = 0;
		cin >> n >> k;
		for (pos = 1;pos <= n - 2 * k + 1;pos += k) {
			cout << "? " << pos << endl;
			cout.flush();
			int x;
			cin >> x;
			ans ^= x;
		}
		int start = max(pos, n - 2 * k + 2);
		int end = n - k + 1;
		for (int i = start;i <= end;i++) {
			cout << "? " << i << endl;
			cout.flush();
			int x;
			cin >> x;
			ans ^= x;
		}
		cout << "! " << ans << endl;
		cout.flush();
	}
	return 0;
}