#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {putchar('0');if (f) putchar('\n');return;}
    if (x < 0) { putchar('-');x = -x;}
    static char s[23];int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
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
void debug_out(const T &f, const R &... r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
struct Point {
    int x;
    int y;
};
class Solution {
public:
    int odd[10001], even[10001];
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n == 1;
        odd[0] = 0;
        odd[1] = nums[1];
        even[0] = even[1] = nums[0];
        for(int i = 2; i < n; ++i) {
            odd[i] = odd[i - 1], even[i] = even[i - 1];
            if(i % 2 == 0) even[i] += nums[i];
            else odd[i] += nums[i];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(((i != 0?odd[i - 1]:0) + even[n - 1] - even[i]) == ((i != 0?even[i - 1]:0) + odd[n - 1] - odd[i])) {
                ++ ans;
            }
        }
        return ans;
    }
};
Solution ss;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    vector<int> ar = vector<int>{5, 6, 1, 4, 2};
    vector<vector<int> > br = vector<vector<int> >{{1,2},{2,4},{4,8}};
    vector<Point> par = vector<Point>{{1, 2},{3,4}};
    // ss.minimumEffort(br);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
/*
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string a, b;
        for(string x: word1) a += x;
        for(string x: word2) b += x;
        return a == b;
    }
};
class Solution {
public:
    string getSmallestString(int n, int k) {
        string ans;
        for(int i = 0; i < n; ++i) {
            char c = 'a' + max(1, k - (n - 1 - i) * 26) - 1;
            ans += c;
            k -= c - 'a' + 1;
        }
        return ans;
    }
};
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n == 1;
        vector<int> odd(n), even(n);
        odd[1] = nums[1];
        even[0] = even[1] = nums[0];
        for(int i = 2; i < n; ++i) {
            odd[i] = odd[i - 1], even[i] = even[i - 1];
            if(i % 2 == 0) even[i] += nums[i];
            else odd[i] += nums[i];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(((i != 0?odd[i - 1]:0) + even[n - 1] - even[i]) == ((i != 0?even[i - 1]:0) + odd[n - 1] - odd[i])) {
                ++ ans;
            }
        }
        return ans;
    }
};
class Solution {
public:
    pair<int,int> vs[100001];
    int minimumEffort(vector<vector<int>>& tasks) {
        auto cmp = [&](const pair<int,int> &a, const pair<int,int> &b) {
            return max(a.second, a.first + b.second) < max(b.second, b.first + a.second);
        };
        int i = 0, n = tasks.size();
        for(vector<int> item: tasks) {
            vs[i ++] = make_pair(item[0], item[1]);
        }
        sort(vs, vs + n, cmp);
        int ans = 0, res = 0;
        for(int i = 0; i < n; ++i) {
            pair<int,int> x = vs[i];
            if(res < x.second) {
                ans += x.second - res;
                res = x.second;
            }
            res -= x.first;
        }
        return ans;
    }
};
*/