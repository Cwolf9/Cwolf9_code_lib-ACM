#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
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
constexpr int INF = 0x3f3f3f3f;
constexpr int maxn = 1e6 + 5;
constexpr int maxe = 2e6 + 5;

int n, m;
class Node {
    public:
    int l, r, fa;
}cw[maxn];
int ar[maxn], las[maxn], vis[maxn], cnt[maxn];
vector<int> mp[maxn];
constexpr int MXN = 1e7 + 2;
bool noprime[MXN];
int pp[MXN/10], pcnt;
void init_prime() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i;
        for(int j = 0; j < pcnt && i*pp[j] < MXN; ++j) {
            noprime[i*pp[j]] = 1;
            if(i % pp[j] == 0) break;
        }
    }
}
class ST {
    public:
    // int tid;
    int sum[maxn<<2], is[maxn << 1];
    void push_up(int rt) {sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];}
    void build(int l, int r, int rt) {
        if(l == r) {
            sum[rt] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    void push_down(int rt) {
        if(is[rt] == 0) return;
        sum[rt << 1] = sum[rt << 1 | 1] = 0;
        is[rt << 1] = is[rt << 1 | 1] = 1;
        is[rt] = 0;
    }
    void single(int p, int l, int r, int rt) {
        if(l == r) {
            sum[rt] = 0;
            return;
        }
        push_down(rt);
        int mid = (l + r) >> 1;
        if(p <= mid) single(p, l, mid, rt << 1);
        else single(p, mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    void update(int L, int R, int l, int r, int rt) {
        if(sum[rt] == 0 || L > R) return ;
        if(L <= l && r <= R) {
            is[rt] = 1;
            sum[rt] = 0;
            return ;
        }
        push_down(rt);
        int mid = (l + r) >> 1;
        if(R <= mid) {
            if(sum[rt << 1]) update(L, R, l, mid, rt << 1);
        }else if(L > mid) {
            if(sum[rt << 1 | 1]) update(L, R, mid + 1, r, rt << 1 | 1);
        }else {
            update(L, mid, l, mid, rt << 1);
            update(mid + 1, R, mid + 1, r, rt << 1 | 1);
        }
    }
    int query(int L, int R, int l, int r, int rt) {
        if(sum[rt] == 0 || L > R) return -1;
        if(l == r) return l;
        push_down(rt);
        int mid = (l + r) >> 1;
        if(R <= mid) {
            if(sum[rt << 1]) return query(L, R, l, mid, rt << 1); else return -1;
        }else if(L > mid) {
            if(sum[rt << 1 | 1]) return query(L, R, mid + 1, r, rt << 1 | 1);else return -1;
        }else {
            int a = query(L, mid, l, mid, rt << 1);
            if(a != -1) return a;
            return query(mid + 1, R, mid + 1, r, rt << 1 | 1);
        }
    }
}tree;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    // n = 10;
    // rep(i, 1, n + 1) ar[i] = i;
    read(n);
    rep(i, 1, n + 1) read(ar[i]);
    // debug(pcnt)
    tree.build(1, n, 1);
    int rt = 0, flag = 1;
    rep(i, 1, n + 1) {
        rep(j, 0, pcnt) {
            if(ar[i] % pp[j] == 0) {
                mp[i].emplace_back(j);
                while(ar[i] % pp[j] == 0) ar[i] /= pp[j];
            }
            if(pp[j] > ar[i] || ar[i] == 1) break;
        }
        int Mx = 0;
        for(int x: mp[i]) {
            Mx = max(Mx, las[x]);
        }
        if(Mx) {
            int pos = tree.query(Mx + 1, i - 1, 1, n, 1);
            // debug(i, Mx, pos)
            if(pos == -1) {
                flag = 0;
                break;
            }
            vis[i] = vis[Mx] = vis[pos] = 1;
            tree.update(Mx, i, 1, n, 1);
            if(rt == 0) rt = pos;
            cw[pos].l = Mx;
            cw[pos].r = i;
            cw[Mx].fa = pos;
            cw[i].fa = pos;
            for(int x: mp[Mx]) {
                las[x] = 0;
            }
        }
        for(int x: mp[i]) las[x] = i;
    }
    if(flag == 0) printf("impossible\n");
    else if(rt == 0) {
        rep(i, 0, n) printf("%d%c", i, " \n"[i == n]);
    }else {
        // debug(rt)
        // rep(i, 1, n + 1) {
        //     debug(i, cw[i].l, cw[i].r)
        // }
        int L = -1;
        rep(i, 1, n + 1) {
            if(vis[i]) {
                if(L != -1) rep(j, L, i) cw[j + 1].l = j, cw[j].fa = j + 1;
                L = -1;
            }else if(L == -1) L = i;
        }
        if(L != -1) {
            rep(i, L, n + 1) {
                cw[i - 1].r = i;
                cw[i].fa = i - 1;
            }
        }
        rep(i, 1, n + 1) printf("%d%c", cw[i].fa, " \n"[i == n]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}