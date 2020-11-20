#include <bits/stdc++.h>
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
const int MXN = 2e5 + 5;
const int mo=10000007;
int BZ;
typedef long long ll;
struct hsh{
	ll key;
	int bz,v;
} h[mo];
int n;
bool nei_query(int u,int v){
	ll key=(ll)u*(n+1)+v;
	int i=key%mo;
	for (;h[i].bz==BZ && h[i].key!=key;++i==mo?i=0:i);
	if (h[i].bz==BZ) return h[i].v;
	return 0;
}
void nei_set(int u,int v,int c){
	ll key=(ll)u*(n+1)+v;
	int i=key%mo;
	for (;h[i].bz==BZ && h[i].key!=key;++i==mo?i=0:i);
	h[i]={key,BZ,c};
}
int main() {
    n = 100000;
    nei_set(1, 2, 1);
    int x = nei_query(1, 2);
    cout << x << endl;
    return 0;
}