//O(n*log(n)*log(y))
//首先二分找到连续的能吃到的最右端点，再找到下一个可以吃到起点继续吃。
//重复这个过程的复杂度是O(log(n)*log(y))。
//线段树维护区间和，区间最小值，找到向右最多能吃的区间长度是线段树上二分
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 2e5 + 5;
int n, m;
int ar[MXN];
int64 sum[MXN << 2];
int sumfg[MXN << 2], mn[MXN << 2];
void push_up(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mn[rt] = mn[rt << 1 | 1];
}
void build(int l, int r, int rt) {
	sumfg[rt] = 0;
    if(l == r) {
        mn[rt] = ar[l];
        sum[rt] = ar[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    push_up(rt);
}
void push_down(int rt, int l, int mid, int r) {
    if(sumfg[rt] == 0) return;
    assert(sumfg[rt << 1] <= sumfg[rt] && sumfg[rt << 1 | 1] <= sumfg[rt]);
	sumfg[rt << 1] = sumfg[rt << 1 | 1] = sumfg[rt];
    sum[rt << 1] = (int64)sumfg[rt] * (mid - l + 1);
    mn[rt << 1] = sumfg[rt];

    sum[rt << 1 | 1] = (int64)sumfg[rt] * (r - mid);
    mn[rt << 1 | 1] = sumfg[rt];

    sumfg[rt] = 0;
}
int64 qsum(int L, int R, int l, int r, int rt) {
	if(L > R) return 0;
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) return qsum(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return qsum(L, R, l, mid, rt << 1);
    else {
        return qsum(L, mid, l, mid, rt << 1) + qsum(mid + 1, R, mid + 1, r, rt << 1 | 1);
    }
}
void update(int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        sum[rt] = (int64)v * (r - l + 1);
        mn[rt] = v;
        sumfg[rt] = max(sumfg[rt], v);
        return;
    }
    if(l == r) return;
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) {
        update(L, R, v, mid + 1, r, rt << 1 | 1);
    }else if(R <= mid) {
        update(L, R, v, l, mid, rt << 1);
    }else {
		update(L, mid, v, l, mid, rt << 1);
        update(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
    }
    push_up(rt);
}
//find first pos less than or equal than v
int que4(int L, int R, int v, int l, int r, int rt) {
	if(mn[rt] > v) return -1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	push_down(rt, l, mid, r);
	if(L > mid) {
		return que4(L, R, v, mid + 1, r, rt << 1 | 1);
	}else if(R <= mid) {
		return que4(L, R, v, l, mid, rt << 1);
	}else {
		if(mn[rt << 1] > v) return que4(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
		else return que4(L, mid, v, l, mid, rt << 1);
	}
}
int64 Left;
//find first pos you can eat continuously
int que3(int L, int R, int v, int l, int r, int rt) {
	//debug(L, R, v, l, r, rt, Left)
	if(l == r) {
		if(sum[rt] <= v) return l;
		else return -1;
	}
	int mid = (l + r) >> 1;
	push_down(rt, l, mid, r);
	if(L > mid) {
		Left -= sum[rt << 1];
		return que3(L, R, v, mid + 1, r, rt << 1 | 1);
	}else if(R <= mid) {
		return que3(L, R, v, l, mid, rt << 1);
	}else {
		if(sum[rt << 1] - Left < v) {
			v -= (sum[rt << 1] - Left);
			Left = 0;
			return max(mid, que3(mid + 1, R, v, mid + 1, r, rt << 1 | 1));
		}else if(sum[rt << 1] - Left == v) return mid;
		else return que3(L, mid, v, l, mid, rt << 1);
	}
}
//10 10 10 6 6 5 5 5 3 1
//find how many food you can eat greedy
int que2(int p, int v, int l, int r, int rt) {
    if(p <= l && sum[rt] <= v) return r - l + 1;
    if(l == r) return 0;
    int mid = (l + r) >> 1, ans = 0;
    push_down(rt, l, mid, r);
    //debug(l, mid, r, rt, v)
	if(p <= mid) {
		Left = qsum(1, p - 1, 1, n, 1);
        //debug(Left)
		int pos = que3(p, mid, v, 1, n, 1);
		//debug(p, mid, pos, Left)
		int64 tmp = qsum(p, pos, 1, n, 1);
        ans += max(0, pos - p + 1);
        if(pos == n) return ans;
        v -= tmp;
		//find next continuous part to eat
        pos = que4(pos + 1, n, v, 1, n, 1);
        if(pos == -1) return ans;
        ans += que2(pos, v, l, r, rt);
    }else {
        ans += que2(p, v, mid + 1, r, rt << 1 | 1);
    }
    return ans;
}
void work() {
    n = read(), m = read();
    rep(i, 1, n + 1) ar[i] = read();
    build(1, n, 1);
    while(m --) {
        int opt = read(), x = read(), y = read();
		//debug(opt, x, y)
		if(opt == 1) {
            int ls = que4(1, x, y, 1, n, 1);
            if(ls == -1) continue;
            update(ls, x, y, 1, n, 1);
        }else {
			int pos = que4(x, n, y, 1, n, 1);
            int ans = 0;
            if(pos != -1) ans = que2(pos, y, 1, n, 1);
            printf("%d\n", ans);
        }
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for(int cas = 1, tim = 1; cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
/*
10 6
10 10 10 6 6 5 5 5 3 1
2 3 50
2 4 10
1 3 10
2 2 36
1 4 7
2 2 17
*/
