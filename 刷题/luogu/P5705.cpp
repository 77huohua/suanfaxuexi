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

double f;

int main() {
	cin >> f;
	int a = f * 10;
	vector<int> arr(4);
	arr[0] = a / 1000;
	arr[1] = (a % 1000) / 100;
	arr[2] = (a % 100) / 10;
	arr[3] = a % 10;
	cout << arr[0] * 0.001 + arr[1]*0.01 + arr[2] *0.1 + arr[3];
}