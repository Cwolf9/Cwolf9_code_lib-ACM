#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
inline long long read(){long long x = 0;Finish_read=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return x;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;return x;}
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
constexpr int MXN = 1e6 + 5;
constexpr int MXE = 2e6 + 5;
int n, m;
class Query {
    public:
    int op, l, r, h;
    void R() {
        op = read();
        if(op == 0) {
            l = read();
            h = read();
        }else {
            l = read();
            r = read();
            h = read();
        }
    }
}q[MXN];
class lp {
    public:
	int l,r,sum;
}cw[MXN*20];
int rak[MXN], tot;
vector<int> vs;
inline int get_id(int x) {
    return lower_bound(all(vs), x) - vs.begin() + 1;
}
void update(int l,int r,int last,int &cur,int x){
	cw[++tot]=cw[last];
	cw[tot].sum = cw[last].sum + 1;
	cur=tot;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)update(l,mid,cw[last].l,cw[cur].l,x);
	else update(mid+1,r,cw[last].r,cw[cur].r,x);
}
int query(int l,int r,int last,int cur,int k){
	if(l==r)return cw[cur].sum-cw[last].sum;
	int mid=(l+r)>>1;
	if(k<=mid)return query(l,mid,cw[last].l,cw[cur].l,k);
	else {
		int ans=query(mid+1,r,cw[last].r,cw[cur].r,k);
		ans+=cw[cw[cur].l].sum-cw[cw[last].l].sum;
		return ans;
	}
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        m = read();
        debug(n, m)
        vs.clear();
        tot = 0;
        cw[0] = {0, 0, 0};
        rep(i, 0, m) {
            q[i].R();
            vs.emplace_back(q[i].h);
        }
        my_unique(vs);
        
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}