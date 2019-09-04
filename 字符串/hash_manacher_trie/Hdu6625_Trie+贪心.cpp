const int MXN = 1e5 + 7;
const int MXE = 2e6 + 7;
int n, m;
int ar[MXN], br[MXN];
struct Trie {
    int tot;
    int nex[MXE][2], num[MXE], val[MXE];
    Trie(){nex[0][0] = nex[0][1] = -1;}
    void newnode() {
        ++ tot;
        nex[tot][0] = nex[tot][1] = -1;
    }
    void inisert(int x) {
        int rt = 0;
        for(int i = 31, tmp; i >= 0; --i) {
            tmp = ((x>>i)&1);
            if(nex[rt][tmp] == -1) newnode(), nex[rt][tmp] = tot;
            rt = nex[rt][tmp];
            num[rt] ++;
        }
        val[rt] = x;
    }
    void del(int x) {
        int rt = 0;
        for(int i = 31, tmp; i >= 0; --i) {
            tmp = ((x>>i)&1);
            int lst = rt;
            rt = nex[rt][tmp];
            nex[lst][tmp] = -1;
            num[rt] = 0;
        }
    }
}cw[2];
bool check(int id, int rt, int tmp) {
    return cw[id].nex[rt][tmp] != -1 && cw[id].num[cw[id].nex[rt][tmp]] > 0;
}
int getans() {
    int rt1 = 0, rt2 = 0;
    for(int i = 31; i >= 0; --i) {
        if(check(0, rt1, 0) && check(1, rt2, 0)) {
            rt1 = cw[0].nex[rt1][0];
            rt2 = cw[1].nex[rt2][0];
            -- cw[0].num[rt1];
            -- cw[1].num[rt2];
        }else if(check(0, rt1, 1) && check(1, rt2, 1)) {
            rt1 = cw[0].nex[rt1][1];
            rt2 = cw[1].nex[rt2][1];
            -- cw[0].num[rt1];
            -- cw[1].num[rt2];
        }else if(check(0, rt1, 1) && check(1, rt2, 0)) {
            rt1 = cw[0].nex[rt1][1];
            rt2 = cw[1].nex[rt2][0];
            -- cw[0].num[rt1];
            -- cw[1].num[rt2];
        }else if(check(0, rt1, 0) && check(1, rt2, 1)) {
            rt1 = cw[0].nex[rt1][0];
            rt2 = cw[1].nex[rt2][1];
            -- cw[0].num[rt1];
            -- cw[1].num[rt2];
        }
    }
    return cw[0].val[rt1] ^ cw[1].val[rt2];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
//    freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        cw[0].tot = cw[1].tot = 0;
        for(int i = 1; i <= n; ++i) ar[i] = read(), cw[0].inisert(ar[i]);
        for(int i = 1; i <= n; ++i) br[i] = read(), cw[1].inisert(br[i]);
        vector<int> vs;
        for(int i = 1; i <= n; ++i) vs.eb(getans());
        sort(all(vs));
        for(int i = 0; i < SZ(vs); ++i) printf("%d%c", vs[i], " \n"[i == SZ(vs) - 1]);
        for(int i = 1; i <= n; ++i) cw[0].del(ar[i]), cw[1].del(br[i]);
    }
    return 0;
}


const int MXN = 1e5 + 7;
const int MXE = 2e6 + 7;
int n, m;
int ar[MXN], br[MXN];
struct Trie {
    int tot;
    int nex[MXE][2], num[MXE], val[MXE];
    Trie(){nex[0][0] = nex[0][1] = -1;}
    void newnode() {
        ++ tot;
        nex[tot][0] = nex[tot][1] = -1;
    }
    void inisert(int x) {
        int rt = 0;
        for(int i = 30, tmp; i >= 0; --i) {
            tmp = ((x>>i)&1);
            if(nex[rt][tmp] == -1) newnode(), nex[rt][tmp] = tot;
            rt = nex[rt][tmp];
            num[rt] ++;
        }
        val[rt] = x;
    }
    int query(int x) {
        int rt = 0;
        for(int i = 30, tmp; i >= 0; --i) {
            tmp = ((x>>i)&1);
            if(nex[rt][tmp] != -1 && num[nex[rt][tmp]]) rt = nex[rt][tmp];
            else rt = nex[rt][!tmp];
        }
        return val[rt];
    }
    int find() {
        int rt = 0;
        for(int i = 30, tmp; i >= 0; --i) {
            if(nex[rt][0] != -1 && num[nex[rt][0]]) rt = nex[rt][0];
            else if(nex[rt][1] != -1 && num[nex[rt][1]]) rt = nex[rt][1];
        }
        if(rt == 0) return -1;
        return val[rt];
    }
    void del() {
        for(int i = 0; i <= tot + 1; ++i) num[i] = 0, clr(nex[i], -1);
        tot = 0;
    }
    void sub(int x) {
        int rt = 0;
        for(int i = 30, tmp; i >= 0; --i) {
            tmp = ((x>>i)&1);
            rt = nex[rt][tmp];
            num[rt] --;
        }
    }
}cw[2];
/*
 * 这种做法不能保证每次求出来的异或最小值都是单调递增的，但是将n次得到的值排序后一定是正确答案
 * 如果想单纯的求两个01字典树异或最小值，个人感觉还没有较好的复杂度的做法。
 * 关于本题，还有一个出题人提供适用性更加广泛的正解：
 * 现在a中随便找一个数字，然后在b中找一个和他匹配最小的数字，再在a里面找一个和上个数匹配最小的数字，递归下去一定会找到一个大小为2的环
 * 把这个环取出来，在回到上一个位置继续递归下去。得到的n个数字排序即为最终答案。
 * */
vector<int> vs;
int dfs(int id, int x, int lst) {
    int tmp = cw[!id].query(x);
    if(tmp == lst) {
        vs.eb(tmp ^ x);
        cw[id].sub(x);
        cw[!id].sub(tmp);
        return id;
    }
    int ret = dfs(!id, tmp, x);
    if(ret != id) return ret;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
//    freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        for(int i = 1; i <= n; ++i) ar[i] = read(), cw[0].inisert(ar[i]);
        for(int i = 1; i <= n; ++i) br[i] = read(), cw[1].inisert(br[i]);
        vs.clear();
        while(1) {
            int tmp = cw[0].find();
            if(tmp == -1) break;
            dfs(1, tmp, -1);
        }
        sort(all(vs));
        for(int i = 0; i < SZ(vs); ++i) printf("%d%c", vs[i], " \n"[i == SZ(vs) - 1]);
        cw[0].del(), cw[1].del();
    }
    return 0;
}
