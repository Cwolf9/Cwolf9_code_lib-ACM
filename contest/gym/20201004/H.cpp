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
class Node {
    public:
    int d, s;
    int id;
    bool operator<(const Node&B) const{
        return d - s > B.d - B.s;
    }
}cw[maxn];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    read(n);
    read(m);
    rep(i, 0, n) {
        read(cw[i].d);
        read(cw[i].s);
        cw[i].id = i;
    }
    sort(cw, cw + n);
    int all = 1 << n;
    int num = 0, who = 0;
    for(int i = 1; i < all; ++i) {
        int tmp = m, cnt = 0;
        for(int j = 0; j < n; ++j) {
            if((i >> j) & 1) {
                if(tmp >= max(cw[j].s, cw[j].d)) {
                    tmp -= cw[j].s;
                    ++ cnt;
                }
            }
        }
        if(cnt > num) {
            num = cnt;
            who = i;
        }
    }
    if(num == 0) {
        printf("0\n");
    }else {
        int tmp = m;
        int cnt = 0;
        vector<int> vs;
        for(int j = 0; j < n; ++j) {
            if((who >> j) & 1) {
                if(tmp >= max(cw[j].s, cw[j].d)) {
                    tmp -= cw[j].s;
                    vs.emplace_back(cw[j].id + 1);
                    ++ cnt;
                }
            }
        }
        printf("%d\n", cnt);
        for(int x: vs) printf("%d ", x);
        printf("\n");
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}