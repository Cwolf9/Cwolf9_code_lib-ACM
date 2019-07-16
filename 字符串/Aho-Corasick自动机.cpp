const int MXN_T = 5e4 + 105;
const int CHAR_SIZE = 26;

struct AC_Auto {
    struct Trie {
        int nex[CHAR_SIZE];
        int fail, cnt, is, last;
    } cw[MXN_T];
    int siz, rt;
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
        cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
        cw[siz].last = 0;
    }
    int idx(char c) {
        return c - 'a';
    }
    void add_str(char *s, int len, int id) {
        rt = 0;
        for (int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++siz;
                clr(cw[siz].nex, -1);
                cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
                cw[siz].last = 0;
            }
            rt = cw[rt].nex[now];
        }
        cw[rt].cnt = id;
        cw[rt].is = 1;
    }
    void build_ac() {
        queue<int> Q;
        Q.push(0);
        cw[0].fail = -1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0, pos; i < CHAR_SIZE; ++i) {
                pos = cw[u].nex[i];
                if (~pos) {
                    assert(pos != -1);
                    if (u == 0) cw[pos].fail = u;
                    else {
                        assert(u != -1);
                        int v = cw[u].fail;
                        while (v != -1) {
                            if (cw[v].nex[i] != -1) {
                                cw[pos].fail = cw[v].nex[i];
                                break;
                            }
                            v = cw[v].fail;
                        }
                        if (v == -1) cw[pos].fail = 0;
                    }
                    //last[u] = val[f[u]] ? f[u] : last[f[u]];后缀链接，表示节点rt沿着失配指针往回走遇到的下一个单词节点编号
                    cw[pos].last = cw[cw[pos].fail].is?cw[pos].fail:cw[cw[pos].fail].last;
                    Q.push(pos);
                }else {//建新的边补全图（可选可不选,会改变遍历方式
//                    cw[u].nex[i] = cw[cw[u].fail].nex[i];
                }
            }
        }
    }
    int Get(int x) {
        int res = 0;
        while (x) {
            assert(x != -1);
            res += cw[x].cnt;
            x = cw[x].fail;
        }
        return res;
    }
    int Query(int *s, int len) {
        rt = 0;
        int res = 0;
        for (int i = 0, pos, pv; i < len; ++i) {
            pos = idx(s[i]);
            if (~cw[rt].nex[pos]) rt = cw[rt].nex[pos];
            else {
                assert(rt != -1);
                pv = cw[rt].fail;
                while (pv != -1 && cw[pv].nex[pos] == -1) {
                    assert(pv != -1);
                    pv = cw[pv].fail;
                }
                if (pv == -1) rt = 0;
                else rt = cw[pv].nex[pos];
            }
            assert(rt != -1);
            res += Get(rt);
        }
        return res;
    }
    int Query2(int *s, int len) {
        rt = 0;
        int res = 0;
        for(int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            while(cw[rt].nex[now]==-1&&rt) rt = cw[rt].fail;
//            if(cw[rt].nex[now]!=-1)rt = cw[rt].nex[now];
            rt = cw[rt].nex[now];
            if(rt == -1) rt = 0;
            int tmp = rt;
            while(tmp) {
                if(cw[tmp].cnt == 0) break;
                res += cw[tmp].cnt;
                cw[tmp].cnt = 0;
                tmp = cw[tmp].fail;
            }
        }
        return res;
    }
    // 递归打印匹配文本串str[i]结尾的后缀,以结点j结尾的所有字符串
    void print (int i, int j) {
        if (j) {
            printf("** %d %d %d\n", i, j, cw[j].cnt);
            print (i, cw[j].last);
        }
    }
    int Query3(char *s, int len) {//找和这个字符串匹配的模板
        rt = 0;
        int res = 0;
        for(int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            while(cw[rt].nex[now]==-1&&rt) rt = cw[rt].fail;
            rt = cw[rt].nex[now];
            if(rt == -1) rt = 0;
            if(cw[rt].is) print(i, rt);
            else if(cw[rt].last) print(i, cw[rt].last);
        }
        return res;
    }
}aho;

const int MXN_T = 5e4 + 105;
const int CHAR_SIZE = 26;

struct AC_Auto {
    struct Trie {
        int nex[CHAR_SIZE];
        int fail, cnt, is, last;
    } cw[MXN_T];
    int siz, rt;
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
        cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
        cw[siz].last = 0;
    }
    int idx(char c) {
        return c - 'a';
    }
    void add_str(char *s, int len, int id) {
        rt = 0;
        for (int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++siz;
                clr(cw[siz].nex, -1);
                cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
                cw[siz].last = 0;
            }
            rt = cw[rt].nex[now];
        }
        cw[rt].cnt = id;
        cw[rt].is = 1;
    }
    void build_ac2(){
        queue<int> Q;
        cw[0].fail = 0;
        for(int i = 0; i < CHAR_SIZE; ++i){
            if(cw[0].nex[i] == -1){
                cw[0].nex[i] = 0;
            }else {
                cw[cw[0].nex[i]].fail = 0;
                Q.push(cw[0].nex[i]);
            }
        }
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = 0, pos; i < CHAR_SIZE; ++i) {
                pos = cw[u].nex[i];
                if(pos == -1) {
                    cw[u].nex[i] = cw[cw[u].fail].nex[i];
                }else {
                    cw[pos].fail = cw[cw[u].fail].nex[i];
                    cw[pos].last = cw[cw[pos].fail].is?cw[pos].fail:cw[cw[pos].fail].last;
                    Q.push(pos);
                }
            }
        }
    }
    // 递归打印匹配文本串str[i]结尾的后缀,以结点j结尾的所有字符串
    void print (int i, int j) {
        if (j) {
            printf("** %d %d %d\n", i, j, cw[j].cnt);
            print (i, cw[j].last);
        }
    }
    int Query4(char *s, int len) {//找和这个字符串匹配的模板
        rt = 0;
        for(int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            debug(rt)
            rt = cw[rt].nex[now];
            if(cw[rt].is) print(i, rt);
            else if(cw[rt].last) print(i, cw[rt].last);
        }
        return 0;
    }
}aho;