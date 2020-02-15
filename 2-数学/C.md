## C(n, m)
 - require: c++98
 - [x] 封装
 - [ ] 测试

### 朴素打表 $O(n ^ 2)$
```cpp
ll _C[1000][1000];
void make_C(int n, int mod = mod) { // n 为可能用到的最大的数
    for (int i = 0; i <= n; i++) {
        _C[i][0] = _C[i][i] = 1ll;
        for (int j = 1; j < i; j++)
            _C[i][j] = (_C[i - 1][j - 1] + _C[i - 1][j]) % mod;
    }
}
inline int C(int n, int m) { return _C[n][m]; }
```

### 阶乘 & 阶乘的逆元
```cpp
// int fac()
// int invfac()
inline int C(int n,int m) {
    if(n < m)
        return 0;
    return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
}
```

