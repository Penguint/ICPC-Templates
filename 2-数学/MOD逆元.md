## mod逆元 Inverse element

有逆元的条件：n, p 互质

### 费马小定理（当p为大于2的质数） O(log P)

```cpp
// qpow();
int inv(int n, int mod = mod) { return qpow(n, mod - 2); }
```

### 扩展欧几里德

$a*x \equiv 1 \mod p$

它的另一种写法为

$a*x+p*y = 1$

```cpp
int inv(int n, int mod = mod) {
    int x, y;
    if (exgcd(n, mod, x, y) != 1)
        return -1;
    return x;
}
```

### 欧拉函数

```cpp
// qpow();
// eurler_phi();
int inv(int n. int mod = mod) {
    return qpow(n, eurler_phi(mod) - 1);
}
```

### 递推

```cpp
ll _inv[1000000];
void make_inv(int n, int mod = mod) {
    _inv[1] = 1ll;
    for (int i = 2; i <= n; i++) {
        _inv[i] = _inv[mod % i] * (mod - mod / i) % mod;
    }
}
inline int inv(int n) { return _inv[n]; }
```