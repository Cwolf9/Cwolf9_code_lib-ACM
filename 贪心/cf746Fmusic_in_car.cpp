#include<bits/stdc++.h>
using namespace std;

const int MXN = 1e6 + 7;
const int INF = 0x3f3f3f3f;
/*
n首歌,w首歌可以少听t/2,区间时长不超过k，问最大价值
*/
int n, m, k;
int ar[MXN], br[MXN], cr[MXN];
struct lp{
    int x, id;
    friend bool operator < (const lp &a, const lp &b) {
        if(a.x != b.x) return a.x < b.x;
        return a.id < b.id;
    }
};
/*
双指针：
对于双指针内的区间选取时间最长的m首歌少听t/2，这是最优的
选择少听t/2时间的歌曲与其价值无关，因为我只是要保证这个区间的长度小于k
如果无法保证区间时间长度小于k，就要右移第一个指针
用两个set，一个保存区间内前m长的歌曲，一个保存其他歌曲，模拟过程即可
*/
int main() {
#ifndef ONLINE_JUDGE
    //freopen("1.in", "r", stdin);
#endif 
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &br[i]), cr[i] = br[i]/2;
    set<lp> st1, st2;
    int ans = 0, tmp = 0, tim = 0, s = 1;
    for(int i = 1; i <= n; ++i) {
        if(st1.size() < m || (*st1.begin()).x < cr[i]) {
            assert(st1.size() <= m);
            if(st1.size() == m) {
                tim = tim + cr[(*st1.begin()).id];
                //printf("--%d--\n", cr[(*st1.begin()).id]);
                st2.insert((*st1.begin()));
                st1.erase(st1.begin());
                st1.insert(lp{cr[i], i});
            }else st1.insert(lp{cr[i], i});
            tim += (br[i] - cr[i]);
        }else {
            tim += br[i];
            st2.insert(lp{cr[i], i});
        }
        tmp += ar[i];
        s = min(s, i);
        while(tim > k) {
            if(st1.empty() && st2.empty()) {
                assert(0);
                tim = tmp = 0;
                s = INF;
                break;
            }
            set<lp>::iterator X;
            lp Y;
            if(st2.empty()) {
                Y.x = Y.id = -1;
            }else {
                X = st2.lower_bound(lp{cr[s], s});
                Y.x = (*X).x; Y.id = (*X).id;
            }
            tmp -= ar[s];
            if(Y.x == cr[s] && Y.id == s) {
                tim -= br[s];
                st2.erase(X);
            }else {
                X = st1.lower_bound(lp{cr[s], s});
                tim -= (br[s] - cr[s]);
                st1.erase(X);
                if(st2.empty() == 0) {
                    X = st2.end(); -- X;
                    Y.x = (*X).x; Y.id = (*X).id;
                    st2.erase(X);
                    st1.insert(Y);
                    tim = tim - br[Y.id] + br[Y.id] - cr[Y.id];
                }
            }
            ++ s;
        }
        //printf("** %d %d %d %d\n", i, s, tim, tmp);
        ans = max(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}