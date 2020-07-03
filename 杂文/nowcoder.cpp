
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int MXN = 1e5 + 7;
const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
int n, m;
class A {
public:
    A() {}
    A(int a, int b, int c) :start(a),last(b),wait(b),id(c){}
    LL start, last, wait, id;
};
A req[MXN];
LL over[MXN], startList[MXN];
bool cmp(const A&a, const A&b) {
    if(a.start != b.start) return a.start < b.start;
    if(a.last != b.last) return a.last < b.last;
    return a.id < b.id;
}
class comp {
public:
    comp() {}
    ~comp() {}
    bool operator() (const A &a, const A &b) {
        if(a.last != b.last) return a.last < b.last;
        return a.id < b.id;
    }
};

priority_queue<A, vector<A>, comp> Q;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i = 0, a, b; i < n; ++i) {
        scanf("%d%d", &a, &b);
        req[i] = A(a, b, i);
    }
    sort(req, req + n, cmp);
    for(int i = 0; i < n; ++i) startList[i] = req[i].start;
    return 0;
}


