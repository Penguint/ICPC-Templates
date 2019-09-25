# ZKW线段树
 - v1.1
 - require: C++98
 - HDU1698
 - [ ] 封装
 - [x] 已测试


区间修改 + 区间查询
```C++
#include <bits/stdc++.h>
using namespace std;

const int M = 1 << 17;
const int INF = 1e9;

int T[M + M + 1], lazy[M + M + 1];

void modify(int ll, int rr, int v) {
    ll += M - 1, rr += M + 1;
    for (int i = 20, l, r; i; i--) {
        l = ll >> i, r = rr >> i;
        if (lazy[l]) {
            lazy[l * 2] = lazy[l * 2 + 1] = lazy[l];
            T[l * 2] = T[l * 2 + 1] = lazy[l] * (1 << (i - 1));
            lazy[l] = 0;
        }
        if (lazy[r]) {
            lazy[r * 2] = lazy[r * 2 + 1] = lazy[r];
            T[r * 2] = T[r * 2 + 1] = lazy[r] * (1 << (i - 1));
            lazy[r] = 0;
        }
    }
    for (int l = ll, r = rr, num = 1; l > 1; l >>= 1, r >>= 1, num <<= 1) {
        if ((l ^ r ^ 1) > 1) {
            if (~l & 1)
                lazy[l ^ 1] = v, T[l ^ 1] = v * num;
            if (r & 1)
                lazy[r ^ 1] = v, T[r ^ 1] = v * num;
        }
        T[l >> 1] = T[l] + T[l ^ 1];
        T[r >> 1] = T[r] + T[r ^ 1];
    }
}

int query(int l, int r) {
    int ansL = 0, ansR = 0, ln = 0, rn = 0, nn = 1;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1, nn <<= 1) {
        if (lazy[l])
            ansL = lazy[l] * ln;
        if (lazy[r])
            ansR = lazy[r] * rn;
        if (~l & 1)
            ansL += T[l ^ 1], ln += nn;
        if (r & 1)
            ansR += T[r ^ 1], rn += nn;
    }
    for (; l; l >>= 1, r >>= 1) {
        if (lazy[l])
            ansL = lazy[l] * ln;
        if (lazy[r])
            ansR = lazy[r] * rn;
    }
    return ansL + ansR;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        int n, q;
        cin >> n >> q;
        modify(1, n, 1);
        while (q--) {
            int x, y, z;
            cin >> x >> y >> z;
            modify(x, y, z);
        }
        printf("Case %d: The total value of the hook is %d.\n", ca,
               query(1, n));
    }
}
```
