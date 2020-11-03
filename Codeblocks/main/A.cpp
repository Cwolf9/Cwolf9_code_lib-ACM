#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 5e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
char s[MXN];
int st[MXN], len[MXN], val[MXN], sid[MXN];
int nex[MXN][26], siz, cnt[MXN], sum[MXN], islca[MXN], choose[MXN], fk[MXN];
int lasnode, flag;
int new_node() {
    ++ siz;
    clr(nex[siz], -1);
    cnt[siz] = sum[siz] = islca[siz] = choose[siz] = fk[siz] = 0;
    return siz;
}
void add(int st, int len, int id, int l) {
    int rt = 0;
    rep(i, 0, len) {
        if(id == l) cnt[rt] = 1;
        else ++ cnt[rt];
        if(cnt[rt] >= cnt[lasnode]) lasnode = rt;
        int now = s[st + i] - 'a';
        if(nex[rt][now] == -1) {
            nex[rt][now] = new_node();
        }
        // debug(rt, nex[rt][now], now)
        rt = nex[rt][now];
    }
    if(id == l) cnt[rt] = 1;
    else ++ cnt[rt];
    if(cnt[rt] >= cnt[lasnode]) lasnode = rt;
}
void add2(int st, int len, int ip) {
    int rt = 0;
    if(lasnode == 0) {
        flag = 0;
        return;
    }
    rep(i, 0, len) {
        ++ sum[rt];
        if(islca[rt]) flag = 0;
        int now = s[st + i] - 'a';
        rt = nex[rt][now];
        if(rt == lasnode) break;
    }
    ++ sum[rt];
    if(islca[rt]) flag = 0;
    if(ip) islca[rt] = 1;
    fk[rt] = 1;
}
void check(int rt) {
    // debug(rt, sum[rt], islca[rt], fk[rt])
    rep(i, 0, 26) {
        if(nex[rt][i] != -1) {
            check(nex[rt][i]);
        }
    }
}
void dfs(int rt) {
    vector<pii> vs;
    rep(i, 0, 26) {
        if(nex[rt][i] == -1) continue;
        vs.eb(mk(sum[nex[rt][i]], i));
    }
    sort(all(vs));
    int lo = -1;
    for(int i = 0; i < (int)vs.size(); ++i) {
        if(vs[i].fi == 1) lo = i;
    }
    if(lo != -1) {
        if(fk[rt]) {
            rep(i, 0, lo + 1) {
                choose[nex[rt][vs[i].se]] = 1;
            }
        }else {
            // debug(111, lo)
            nex[rt][vs[0].se] = -1;
            rep(i, 1, lo + 1) {
                choose[nex[rt][vs[i].se]] = 1;
            }
        }
    }
    rep(i, lo + 1, (int)vs.size()) {
        dfs(nex[rt][vs[i].se]);
    }
    vs.clear();
    vs.shrink_to_fit();
}
void getAns(int rt, int &ans) {
    ++ ans;
    if(choose[rt]) return;
    rep(i, 0, 26) {
        if(nex[rt][i] != -1) getAns(nex[rt][i], ans);
    }
}
bool cmp(const int&a, const int&b) {
    return val[a] < val[b];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    // freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    int tim = read(), cas = 0;
    while(tim --) {
        printf("Case #%d: ", ++ cas);
        n = read();
        flag = 1;
        siz = -1;
        new_node();
        int lenl = 0;
        rep(i, 0, n) {
            scanf("%s%d", s + lenl, val + i);
            st[i] = lenl;
            len[i] = strlen(s + lenl);
            lenl += len[i];
            sid[i] = i;
        }
        sort(sid, sid + n, cmp);
        int l = 0;
        lasnode = 0;
        rep(ti, 0, n) {
            int i = sid[ti], ni = sid[ti + 1];
            add(st[i], len[i], i, l);
            // debug(i, val[i], val[ni])
            if(ti == n - 1 || val[i] != val[ni]) {
                // debug(lasnode)
                add2(st[i], len[i], l != ti);
                l = ti + 1;
                lasnode = 0;
            }
        }
        // check(0);
        if(flag == 0) {
            printf("-1\n");
            continue;
        }
        dfs(0);
        int ans = 0;
        getAns(0, ans);
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}