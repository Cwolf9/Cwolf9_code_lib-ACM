#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
mt19937 rng(time(NULL));
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
constexpr int maxn = 2e5 + 5;
constexpr int maxe = 2e6 + 5;
int n, m;
class node {
    public:
    int x, y;
    bool operator<(const node&B) const {
        if(x != B.x) return x < B.x;
        return y < B.y;
    }
}ar[maxn], br[maxn];
vector<int> mp[maxe];
int suf[maxe];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1;
    // read(tim);
    while(tim --) {
        read(n);
        read(m);
        rep(i, 1, n + 1) {
            read(ar[i].x);
            read(ar[i].y);
        }
        rep(i, 1, m + 1) {
            read(br[i].x);
            read(br[i].y);
            mp[br[i].x].emplace_back(br[i].y);
        }
        sort(br + 1, br + m + 1);
        vector<int> vs;
        rep(i, 1, m + 1) {
            if(!vs.empty() && br[i].y >= br[vs.back()].y) vs.pop_back();
            vs.push_back(i);
        }
        int vsl = vs.size();
        vector<int> vtx;
        vtx.emplace_back(0);
        vtx.emplace_back(1);
        rep(i, 1, n + 1) {
            int Mx = 0;
            rep(tj, 0, vsl) {
                if(ar[i].y == br[vs[tj]].y) {
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x);
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x + 1);
                    if(tj > 0) {
                        vtx.emplace_back(br[vs[tj - 1]].x - ar[i].x);
                        vtx.emplace_back(br[vs[tj - 1]].x - ar[i].x + 1);
                        rep(k, br[vs[tj - 1]].x, br[vs[tj]].x + 2) vtx.emplace_back(k - ar[i].x);
                    }
                }else if(ar[i].y <= br[vs[tj]].y && (tj == vsl - 1 || ar[i].y >= br[vs[tj + 1]].y)) {
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x);
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x + 1);
                }
            }
        }
        shuffle(all(vs), rng);
        rep(i, 1, n + 1) {
            int Mx = 0;
            rep(tj, 0, vsl) {
                if(br[vs[tj]].x >= ar[i].x && br[vs[tj]].y >= ar[i].y && (vtx.size() < 90000 || rng() % 3 > 0)) {
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x);
                    vtx.emplace_back(br[vs[tj]].x - ar[i].x + 1);
                }
            }
        }
        rep(i, 0, 1000001) {
            if(mp[i].size()) sort(all(mp[i]));
        }
        suf[1000001] = -1;
        per(i, 1000000, 0) {
            suf[i] = suf[i + 1];
            if(mp[i].size()) suf[i] = max(suf[i], mp[i].back());
        }
        // rep(i, 1, n + 1) {
        //     rep(j, 1, m + 1) {
        //         if(br[j].x >= ar[i].x && br[j].y >= ar[i].y) {
        //             vtx.emplace_back(br[j].x - ar[i].x);
        //             vtx.emplace_back(br[j].x - ar[i].x + 1);
        //         }
        //     }
        // }
        my_unique(vtx);
        int ans = 0x3f3f3f3f;
        for(int dx: vtx) {
            int tmp = 0;
            rep(i, 1, n + 1) {
                ar[i].x += dx;
                // debug(ar[i].x, suf[ar[i].x])
                if(suf[ar[i].x] >= ar[i].y) tmp = max(tmp, suf[ar[i].x] - ar[i].y + 1);
            }
            ans = min(ans, tmp + dx);
            // debug(tmp, dx)
            rep(i, 1, n + 1) {
                ar[i].x -= dx;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

// int main() {
// #ifndef ONLINE_JUDGE
//     freopen("D:in.in", "r", stdin);
//     freopen("D:out.out", "w", stdout);
// #endif
//     int tim;
//     read(tim);
//     while(tim --) {
//         read(n);
//         read(m);
//         rep(i, 1, n + 1) {
//             read(ar[i].x);
//             read(ar[i].y);
//         }
//         rep(i, 1, m + 1) {
//             read(br[i].x);
//             read(br[i].y);
//         }
//         sort(br + 1, br + m + 1);
//         vector<int> vs;
//         rep(i, 1, m + 1) {
//             if(!vs.empty() && br[i].y >= br[vs.back()].y) vs.pop_back();
//             vs.push_back(i);
//         }
//         int ansx = 0, ansy = 0;
//         rep(i, 1, n + 1) {
//             int tmp = 0;
//             rep(j, 1, m + 1) {
//                 if(j == 1) {
//                     // if()
//                 }else if(j == m) {

//                 }
//             }
//         }
//     }
//     return 0;
// }
