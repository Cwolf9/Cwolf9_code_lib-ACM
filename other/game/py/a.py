import math
import sys
sys.setrecursionlimit(100005)

n = int(input())
ar = []
fa = []
cnt = []
vis = []
ar = list(map(int, input().split()))
for i in range(n + 1):
    fa.append(i)
    cnt.append(0)
    vis.append(0)
def Fi(x):
    if fa[x] == x:
        return x
    else:
        fa[x] = Fi(fa[x])
        return fa[x]

for i in range(n):
    px = Fi(i + 1)
    py = Fi(ar[i])
    fa[px] = py

for i in range(n):
    x = Fi(i+1)
    cnt[x] = cnt[x] + 1

ans = 1
mod = 1
for i in range(n):
    if cnt[i + 1] > 0 and vis[cnt[i+1]] == 0:
        ans = ans * cnt[i + 1]
        ans = ans // (math.gcd(ans, cnt[i + 1]))
        vis[cnt[i+1]] = 1
    mod = mod * 10
# print(ans.__mod__(mod))
print(ans)