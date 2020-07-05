#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define eb push_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
int lowbit(int x) { return x & (-x); }
void debug_out() { cerr << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cerr << f << " ";
    debug_out(r...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 7;
const int INF = 0x3f3f3f3f;
int n, m, k;
char ar[MXN], br[MXN];
map<string, int> mp;
string rmp[20];
int cnt[20];
vector<int> vs;
int One[(1<<16)+2];
bool cmp(int a, int b) {
    return One[a] < One[b];
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);
#endif
    // iis;
    char str[5] = "ACGT";
    string tmp;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            tmp = str[i];
            tmp += str[j];
            mp[tmp] = i * 4 + j;
            rmp[i*4+j] = tmp;     
        }
    }
    scanf("%s%s", ar, br);
    n = strlen(ar);
    for(int i = 0; i < n; ++i) {
        tmp = ar[i];
        tmp += br[i];
        ++ cnt[mp[tmp]];
    }
    int sta = 1 << 16, ans = 0, Min, res, ret[4], flag;
    for(int t = 1; t < sta; ++t) {
        res = flag = 0;
        memset(ret, 0, sizeof(ret));
        for(int i = 0; i < 16; ++i) if(t&(1<<i)) {
            ++ res;
            for(int j = 0; j < 2; ++j) {
                switch(rmp[i][j]) {
                    case 'A': ret[0] += (j == 0?1:-1); break;
                    case 'C': ret[1] += (j == 0?1:-1); break;
                    case 'G': ret[2] += (j == 0?1:-1); break;
                    case 'T': ret[3] += (j == 0?1:-1); break;
                    default:
                    assert(0);
                    break;
                }
            }
        }
        for(int i = 0; i < 4; ++i) {
            if(ret[i] != 0) flag = 1;
        }
        if(!flag) {
            vs.eb(t);
            One[t] = res;
        }
    }
    sort(all(vs), cmp);
    for(auto t: vs) {
        Min = INF;
        res = 0;
        for(int i = 0; i < 16; ++i) if(t&(1<<i)) {
            Min = min(Min, cnt[i]);
            ++ res;
        }
        if(Min > 0 && Min != INF && res > 0) {
            ans += Min * res - Min;
            // debug(Min, res, t)
            for(int i = 0; i < 16; ++i) if(t&(1<<i)) {
                cnt[i] -= Min;
            }
        }
    }
    printf("%d\n", ans);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}