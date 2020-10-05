#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <iomanip>
int main() {
#ifdef LH_LOCAL
    freopen("D:in.txt", "r", stdin);
    freopen("D:out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(12);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i)
            std::cin >> x[i] >> y[i];
        std::vector<std::vector<double>> dist(n, std::vector<double>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                dist[i][j] = dist[j][i] = std::sqrt(1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]));
        std::vector<std::vector<std::vector<double>>> dp(n);
        for (auto &v : dp)
            v.assign(n, std::vector<double>(2, -1));
        std::vector<std::vector<bool>> g(n, std::vector<bool>(n));
        std::function<double(int, int, int)> get = [&](int u, int v, int x) {
            if (dp[u][v][x] >= 0)
                return dp[u][v][x];
            double res = 0;
            for (int w = (u + 1) % n; w != v; w = (w + 1) % n)
                if (g[x ? v : u][w])
                    res = std::max(res, dist[x ? v : u][w] + std::max(get(u, w, 1), get(w, v, 0)));
            return dp[u][v][x] = res;
        };
        int m;
        std::cin >> m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            --u;
            --v;
            g[u][v] = g[v][u] = true;
        }
        double ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (g[i][j])
                    ans = std::max(ans, dist[i][j] + std::max(get(i, j, 0), get(i, j, 1)));
        std::cout << ans << "\n";
    }
    return 0;
}
