#include <bits/stdc++.h>
using namespace std;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline long long read() {
    long long x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(long long x, bool f = true) {
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
struct Point {
    int x;
    int y;
};
struct Interval {
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};
/*================Header Template==============*/
#define fi first
#define se second
#define mk make_pair
#define o2(x) (x) * (x)
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 1e5 + 5;
const int MXE = MXN * 2 + 1;
class Solution {
public:
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    struct lp {
        int x, y, tm;
    }A, B, cat, mouse, food;
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        int n = grid.size();
        int m = grid[0].length();
        vector<vector<int>> cm(n, vector<int>(m, 101));
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<lp> Q;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == 'C') cat.x = i, cat.y = j;
                if(grid[i][j] == 'M') mouse.x = i, mouse.y = j;
                if(grid[i][j] == 'F') food.x = i, food.y = j;
            }
        }
        cat.tm = mouse.tm = food.tm = 0;
        Q.push(cat);
        cm[cat.x][cat.y] = 0;
        while(!Q.empty()) {
            A = Q.front();
            Q.pop();
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j <= catJump; ++j) {
                    int px = A.x + j * dir[i][0];
                    int py = A.y + j * dir[i][1];
                    if(px < 0 || py < 0 || px >= n || py >= m) continue;
                    if(grid[px][py] == '#') break;
                    if(cm[px][py] <= A.tm + 1) continue;
                    cm[px][py] = A.tm + 1;
                    B.x = px, B.y = py, B.tm = A.tm + 1;
                    Q.push(B);
                }
            }
        }

        bool ans = 0;
        Q.push(mouse);
        while(!Q.empty()) {
            A = Q.front();
            Q.pop();
            vis[A.x][A.y] = 1;
            if(grid[A.x][A.y] == 'F' && A.tm <= 1000) ans = 1;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j <= mouseJump; ++j) {
                    int px = A.x + j * dir[i][0];
                    int py = A.y + j * dir[i][1];
                    if(px < 0 || py < 0 || px >= n || py >= m) continue;
                    if(grid[px][py] == '#') break;
                    if(vis[px][py]) continue;
                    if(grid[px][py] != 'F' && cm[px][py] <= A.tm + 1) continue;
                    if(grid[px][py] == 'F' && cm[px][py] < A.tm + 1) continue;
                    B.x = px, B.y = py;
                    B.tm = A.tm + 1;
                    Q.push(B);
                }
            }
        }
        return ans;     
    }
};
Solution s;
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    //freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    vector<int> U = vector<int>{3,4,6, 16};
    vector<int> V = vector<int>{1,3,4,5,2,6,8,7,9};
    vector<int> VAL = vector<int>{1,7,4,0,9,4,8,8,2,4};
    vector<Interval> IntV = vector<Interval>{Interval(0, 2), Interval(4, 7), Interval(9, 9)};
    vector<vector<int> > vvInt = vector<vector<int> >{{1,2},{2,4},{4,8}};
    vector<Point> par = vector<Point>{{1, 2},{3,4}};

    if(1) {
        debug(x)
    }else {
        // for(int y: x) printf("%d ", y);
        printf("\n");
    }
#ifdef LH_LOCAL
#endif
    return 0;
}

/*

*/
