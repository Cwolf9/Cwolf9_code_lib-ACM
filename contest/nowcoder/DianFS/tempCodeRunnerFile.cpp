or(int i = 2, cf; i < 20; ++i) {
                cf = up[u][i-1];
                up[u][i] = up[cf][i-1];
                dis[u][i] = dis[u][i-1] * dis[cf][i-1] % mod;
            }