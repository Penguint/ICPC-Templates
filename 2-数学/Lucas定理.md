## Lucas 定理

计算 `C(n, m) % p` n, m < 1e9, p < 1e6

Lucas定理：对于非负整数 *n*, *m* 和质数 *p*，
$$
{n \choose m}\equiv\prod_{i=0}^{k}{{n_i \choose m_i}}={{n_k \choose m_k}{n_{k-1} \choose m_{k-1}}\cdots{n_0 \choose m_0}}\pmod{p}
$$

其中
$$
n = n_kp^k + n_{k-1}p^{k-1} \cdots n_1p + n_0,
$$

$$
m = m_kp^k + m_{k-1}p^{k-1} \cdots m_1p + m_0
$$

有引理：对于 *n = sp + q*, *m = tp + r*
$$
{sp + q \choose tp + r} \equiv {s \choose t}{q \choose r}\pmod{p}
$$
Lucas(n, m, P) 返回 C(n, m) 对 P 取模的结果

```cpp
// int C(int n, int m);
int lucas(ll n, ll m, int P = mod) {
    if (n < m) return 0;
    if (!m || n == m) return 1;
    return 1ll * lucas(n / P, m / P, P) * C(n % P, m % P, P) % P;
}
```

### 扩展 Lucas 定理

计算 `C(n, m) % mod` 

```c++
// ll CRT();
ll calc(ll n, ll x, ll P) {
  if (!n) return 1;
  LL s = 1;
  for (int i = 1; i <= P; i++)
    if (i % x) s = s * i % P;
  s = Pow(s, n / P, P);
  for (int i = n / P * P + 1; i <= n; i++)
    if (i % x) s = s * i % P;
  return s * calc(n / x, x, P) % P;
}
ll multilucas(ll m, ll n, ll x, ll P) {
  int cnt = 0;
  for (int i = m; i; i /= x) cnt += i / x;
  for (int i = n; i; i /= x) cnt -= i / x;
  for (int i = m - n; i; i /= x) cnt -= i / x;
  return qpow(x, cnt, P) % P * calc(m, x, P) % P * inv(calc(n, x, P), P) %
         P * inv(calc(m - n, x, P), P) % P;
}
ll exlucas(ll m, ll n, ll P) {
  vector<ll> p, a;
  for (LL i = 2; i * i <= P; i++) {
    if (P % i == 0) { 
      p.push_back(1);
      while (P % i == 0) p.back() *= i, P /= i;
      a.push_back(multilucas(m, n, i, p.back()));
    }
  }
  if (P > 1) p.push_back(P), a.push_back(multilucas(m, n, P, P));
  return CRT(a.size(), a, p);
}
```