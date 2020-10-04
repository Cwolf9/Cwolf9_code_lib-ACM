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
constexpr int maxn = (1<<21) + 5;
constexpr int maxe = 2e6 + 5;
int n, m;
// int num[maxn], pre[maxn], suf[maxn];
// vector<int> ans[maxn];
int cnt[maxn], ar[maxn];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // rep(i, 1, maxn) {
    //     if(i % 2 == 0) num[i] = num[i / 2] + 1;
    //     pre[i] = pre[i - 1] + num[i];
    //     // printf("%02d, ", num[i]);
    //     // if(i % 8 == 0) printf("\n");
    // }
    // // suf[maxn - 1] = num[maxn - 1];
    // // per(i, maxn - 2, 1) {
    // //     suf[i] = suf[i + 1] + num[i];
    // // }
    // // debug(ans[1].size())
    // rep(i, 2, 28) {
    //     int f = -1, t = 0;
    //     rep(j, 1, i) {
    //         if(pre[j] == pre[i] - pre[i - j]) {
    //             f = 1;
    //             ans[i].emplace_back(j);
    //             if(i == 27) debug(i, j)
    //             // ans[i].emplace_back(i - j);
    //             t = 0;
    //         }else {
    //             // if(t == 3) break;
    //             f = 0;
    //             ++ t;
    //         }
    //     }
    //     my_unique(ans[i]);
    //     // if(i <= 20) debug(ans[i].size())
    // }
    int tim = 1;
    read(tim);
    while(tim --) {
        read(n);
        // n = 1000000;
        int Mx = 0;
        for(int i = 1; i <= n; ++i) {
            int x = i;
            read(x);
            Mx = max(Mx, x);
            ++ cnt[x];
        }
        LL res = 0;
        int N = 21;
        int all = 1<<N;
        for(int i = 0; i < all; ++i) {
            ar[i] = cnt[i];
        }
        for(int i = 0; i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
            if(mask & (1<<i))
                ar[mask] += ar[mask^(1<<i)];
        }
        
        rep(i, 1, all) {
            // if(cnt[i]) debug(i, ar[i], cnt[i])
            res += (LL)ar[i] * cnt[i];
        }
        // per(i, Mx, 1) {
        //     for(int x: ans[i]) {
        //         res += (LL)cnt[x] * cnt[i];
        //         // debug(x, i, res, cnt[x], cnt[i])
        //     }
        //     res += (LL)cnt[i] * cnt[i];
        // }
        printf("%lld\n", res);
        rep(i, 0, all) ar[i] = cnt[i] = 0;
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}