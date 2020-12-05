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

class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        set<int> ar;
        for(int x: nums) {
            if(x & 1) x <<= 1;
            ar.insert(x);
        }
        int ans = INF;
        while((int)ar.size() >= 2) {
            auto p = prev(ar.end());
            int pp = *p;
            ans = min(ans, pp - *ar.begin());
            if(pp % 2 == 0) {
                ar.erase(p);
                ar.insert(pp / 2);
            }else break;
        }
        auto p = prev(ar.end());
        ans = min(ans, *p - *ar.begin());
        return ans;
    }
};
Solution s;
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    //freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    vector<int> arr = vector<int>{1,2,3,4};
    vector<int> arr2 = vector<int>{1,4,2,5,2,2};
    vector<Interval> ar = vector<Interval>{Interval(0, 2), Interval(4, 7), Interval(9, 9)};
    vector<vector<int> > br = vector<vector<int> >{{1,2},{2,4},{4,8}};
    vector<Point> par = vector<Point>{{1, 2},{3,4}};
    auto x = 1;
    s.minimumDeviation(arr);
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
https://leetcode-cn.com/contest/weekly-contest-217

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
class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int ans = 0;
        for(vector<int> &x: accounts) {
            ans = max(ans, accumulate(all(x), 0));
        }
        return ans;
    }
};

class Solution {
public:
	int dq[MXN];
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int l = 0, r = 0;
        vector<int> ans;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if((int)ans.size() + n - i == k) {
            	while(r > l && nums[dq[r]] > nums[i]) -- r;
				dq[++r] = i;
				ans.eb(nums[dq[l + 1]]);
				++ l;
			}else {
				while(r > l && nums[dq[r]] > nums[i]) -- r;
				dq[++r] = i;
			}
        }
        return ans;
    }
};

class Solution {
public:
	int vis[MXN<<1], num[MXN<<1];
    int minMoves(vector<int>& nums, int limit) {
		int n = nums.size(), ans = 2 * n;
		int l = 0, r = n - 1;
        for(int i = 0; i <= limit + limit; ++i) vis[i] = 0;
		while(l < r) {
			int a = nums[l], b = nums[r];
            if(a > b) swap(a, b);
            ++ vis[a + 1];
            -- vis[b + limit + 1];
            ++ num[a + b];
			++ l, -- r;
		}
        for(int i = 1; i <= limit + limit; ++i) {
            vis[i] += vis[i - 1];
        }
        for(int i = 1; i <= limit + limit; ++i) {
            ans = min(ans, (vis[i] - num[i]) + (n / 2 - vis[i]) * 2);
        }
		return ans;
    }
};

class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        set<int> ar;
        for(int x: nums) {
            if(x & 1) x <<= 1;
            ar.insert(x);
        }
        int ans = INF;
        while((int)ar.size() >= 2) {
            auto p = prev(ar.end());
            int pp = *p;
            ans = min(ans, pp - *ar.begin());
            if(pp % 2 == 0) {
                ar.erase(p);
                ar.insert(pp / 2);
            }else break;
        }
        auto p = prev(ar.end());
        ans = min(ans, *p - *ar.begin());
        return ans;
    }
};
*/
