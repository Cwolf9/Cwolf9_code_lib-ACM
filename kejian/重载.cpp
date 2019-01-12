#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <unordered_map>

namespace lh {
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

}
using namespace lh;//我的namespace


const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 1e3 + 7;

int n;
struct lp {
    int val, id;
    friend bool operator<(const lp &a, const lp &b) {
        if(a.val != b.val) return a.val > b.val;
        return a.id < b.id;
    }
}cw[MXN];

int main(int argc, char const *argv[]) {
    priority_queue<int> Q;//大的在前面
    priority_queue<int,std::vector<int>, greater<int> > Q1;//小的在前面
    priority_queue<lp> Q2;//val小的在前面，其次时id大的在前面
    sort(cw, cw + n);//val大的在前面，其次时id小的在前面
    return 0;
}