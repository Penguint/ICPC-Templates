## BM & CH 线性递推

https://www.cnblogs.com/Dance-Of-Faith/p/9810513.html

```cpp
namespace BM{
#define pb push_back
#define SZ(x) ((int)x.size())
#define REP(i, a, b) for (int i = a; i < b; ++i)
  LL Pow(LL x, LL b) {
    LL re = 1;
    x %= MOD, assert(b >= 0);
    for (; b; b >>= 1, x = x * x % MOD)
      if (b & 1) re = re * x % MOD;
    return re;
  }
  VI Bm(VI x) {
    VI ls, cur;
    int pn = 0, lf, ld;
    REP(i, 0, SZ(x)) {
      LL t = -x[i] % MOD;
      REP(j, 0, SZ(cur))
        t = (t + x[i - j - 1] * (LL)cur[j]) % MOD;
      if (!t) continue;
      if (cur.empty()) {
        cur.resize(i + 1);
        lf = i, ld = t;
        continue;
      }
      LL k = -t * Pow(ld, MOD - 2) % MOD;
      VI c(i - lf - 1);
      c.pb(-k);
      REP(j, 0, SZ(ls)) c.pb(ls[j] * k % MOD);
      if (c.size() < cur.size())
        c.resize(cur.size());
      REP(j, 0, SZ(cur))
        c[j] = (c[j] + cur[j]) % MOD;
      if (i - lf + SZ(ls) >= SZ(cur))
        ls = cur, lf = i, ld = t;
      cur = c;
    }
    VI &o = cur;
    REP(i, 0, SZ(o))
      o[i] = (o[i] % MOD + MOD) % MOD;
    return o;
  }
}

namespace CH {
#define SZ(x) ((int)x.size())
  VI g;
  int k;
  inline void Ad(int &a, int b) {
    if ((a += b) >= MOD) a -= MOD;
  }
  VI Mul(VI a, VI b) {
    VI c;
    assert(SZ(a) <= k && SZ(b) <= k);
    c.resize(SZ(a) + SZ(b) - 1);
    for (int i = 0; i < SZ(a); ++i)
      for (int j = 0; j < SZ(b); ++j)
        Ad(c[i + j], (LL)a[i] * b[j] % MOD);
    for (int i = SZ(c) - 1; i >= k; --i)
      for (int j = 0; j <= k; ++j)
        Ad(c[i - k + j], MOD - (LL)c[i] * g[j] % MOD);
    c.resize(k);
    return c;
  }
  VI Solve(VI a, int n) {
    k = SZ(a);
    g.resize(k + 1, 1);
    for (int i = 1; i <= k; ++i)
      g[k - i] = (MOD - a[i - 1]) % MOD;
    VI re(1, 1), x(2, 1);
    x[0] = 0;
    for (; n; n >>= 1, x = Mul(x, x))
      if (n & 1) re = Mul(re, x);
    return re;
  }
}
```

https://blog.csdn.net/kaixinqi/article/details/99672895