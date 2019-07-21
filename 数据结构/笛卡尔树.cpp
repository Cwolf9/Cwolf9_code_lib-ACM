/*
 * key满足二叉搜索树的性质，value满足堆的性质
 * 模板题：hdu6305，sgu155，poj1785
 *
 * https://blog.csdn.net/acdreamers/article/details/11353117
 */

struct DT{
    int l, r, pre;
}dt[MXN];
int build(int _n) {
    top = 0;
    for (int i = 0; i <= _n; ++i) dt[i].l = dt[i].r = dt[i].pre = vis[i] = 0;
    stak[++ top] = 1;
    for (int i = 2; i <= _n; ++i) {
        while(top > 0 && ar[i] < ar[stak[top]]) -- top;
        if(top) {
            dt[i].pre = stak[top];
            dt[i].l = dt[stak[top]].r;
            dt[dt[stak[top]].r].pre = i;
            dt[stak[top]].r = i;
        }else {
            dt[stak[1]].pre = i;
            dt[i].l = stak[1];
        }
        stak[++ top] = i;
    }
    for (int i = 1; i <= n; i++) vis[dt[i].l] = vis[dt[i].r] = 1;
    int rt = 0;
    for (int i = 1; i <= n; i++) if (vis[i] == 0) rt = i;
    return rt;//stak[1]
}