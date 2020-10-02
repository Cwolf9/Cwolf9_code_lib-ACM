#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
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
constexpr int maxn = 4e5 + 5;
constexpr int maxe = 2e6 + 5;
int n, m;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim;
    read(tim);
    while(tim --) {
        read(n);
        int cnt = 0;
        LL ans = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q1;
        for(int i = 1, x; i <= n; ++i) {
            read(x);
            if(!Q1.empty() && x > Q1.top().first) {
                ans += x - Q1.top().first;
                if(Q1.top().second == 1) cnt += 2;
                Q1.pop();
                Q1.push(make_pair(x, 0));
            }
            Q1.push(make_pair(x, 1));
        }
        printf("%lld %d\n", ans, cnt);
    }
    return 0;
}
