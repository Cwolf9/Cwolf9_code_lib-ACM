/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
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
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
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
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;  // 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;

// using uint128 = __uint128_t;
using ull = unsigned long long;
using ll = long long;
using uint = unsigned int;
using pli = pair<ull, uint>;
 
namespace prime {
#define eb emplace_back
#define sz(x) ((int)(x).size())
	ull mod;
	inline ull mul(ull a, ull b) {
  		if (mod < int(2e9)) return a * b % mod;
  		ull k = ((long double)a * b / mod + 0.1);
  		ull res = a * b - k * mod;
  		if ((ll)res < 0) res += mod;
  		return res;
	}
	inline ull add(ull a, ull b) {
		if ((a += b) >= mod) a -= mod;
		return a;
	}
	inline ull kpow(ull a, ull b) {
		ull res = 1;
		for (; b; a = mul(a, a), b >>= 1) if (b & 1) res = mul(res, a);
		return res;
	}
	inline ull sqr(ull x) { return x * x; }
	bool composite(ull n, const uint* base, int m) {
		int s = __builtin_ctzll(n - 1);
		ull d = (n - 1) >> s; mod = n;
		for (int i = 0, j; i < m; ++i) {
			ull a = kpow(base[i], d);
			if (a == 1 || a == n - 1) continue;
			for (j = s - 1; j > 0; --j) { a = mul(a, a); if (a == n - 1) break; }
			if (j == 0) return 1;
		}
		return 0;
	}
	bool is_prime(ull n) { // reference: http://m...content-available-to-author-only...t.com
		assert(n < (ull(1) << 63));
		static const uint base[][7] = {
			{2, 3},
			{2, 299417},
			{2, 7, 61},
			{15, 176006322, 4221622697u},
			{2, 2570940, 211991001, 3749873356u},
			{2, 2570940, 880937, 610386380, 4130785767u},
			{2, 325, 9375, 28178, 450775, 9780504, 1795265022}
		};
		if (n <= 1) return 0;
		if (!(n & 1)) return n == 2;
		if (n <= 8) return 1;
		int x = 6, y = 7;
		if (n < 1373653) x = 0, y = 2;
		else if (n < 19471033) x = 1, y = 2;
		else if (n < 4759123141) x = 2, y = 3;
		else if (n < 154639673381) x = y = 3;
		else if (n < 47636622961201) x = y = 4;
		else if (n < 3770579582154547) x = y = 5;
		return !composite(n, base[x], y);
	}
	vector<uint> primes;
	void init(uint n) {
		uint sq = sqrt(n);
		vector<bool> isp(n + 1, 1);
		primes.clear();
		for (uint i = 2; i <= sq; ++i) if (isp[i]) {
			if (i != 2) primes.eb(i);
			for (uint j = i * i; j <= n; j += i) isp[j] =  0;
		}
	}
	ull brent(ull n, ull c) { // n must be composite and odd.
		const ull s = 256;
		ull y = 1; c %= n; mod = n;
		for (ull l = 1; ; l <<= 1) {
			ull x = y;
			for (int i = 0; i < l; ++i) y = add(mul(y, y), c);
			ull p = 1;
			for (int k = 0; k < l; k += s) {
				ull sy = y;
				for (int i = 0; i < min(s, l - k); ++i) {
					y = add(mul(y, y), c);
					p = mul(p, add(y, n - x));
				}
				ull g = __gcd(n, p);
				if (g == 1) continue;
				if (g == n) for (g = 1, y = sy; g == 1; ) y = add(mul(y, y), c), g = __gcd(n, add(y, n - x));
				return g;
			}
		}
	}
	vector<pli> factors(ull n) {
		assert(n < (1ull << 63));
		if (n <= 1) return {};
		vector<pli> ret;
		if (!(n & 1)) {
			uint e = __builtin_ctzll(n);
			ret.eb(2, e);
			n >>= e;
		}
		ull lim = sqr(primes.back());
		for (auto &&p: primes) {
			if (sqr(p) > n) break;
			uint e = 0;
			while (n % p == 0) n /= p, e++;
			if (e) ret.eb(p, e);
		}
		uint s = sz(ret);
		while (n > lim && !is_prime(n)) {
			for (ull c = 1; ; ++c) {
				ull p = brent(n, c);
				if (!is_prime(p)) continue;
				uint e = 1; n /= p;
				while (n % p == 0) n /= p, e++;
				ret.eb(p, e);
				break;
			}
		}
		if (n > 1) ret.eb(n, 1);
		if (sz(ret) - s >= 2) sort(ret.begin() + s, ret.end());
		return ret;
	}
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    cout << 1 << endl;
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
