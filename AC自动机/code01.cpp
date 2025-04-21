#include <vector>
using namespace std;

//目标字符串的数量
const int MAXN = 200010;

//所以目标字符串的总字符数量
const int MAXS = 200010;

//记录每个目标串的结尾节点编号
vector<int> end(MAXN);

//AC自动机
vector<vector<int>> tree(MAXS, vector<int>(26));

vector<int> fail(MAXS);

int cnt = 0;