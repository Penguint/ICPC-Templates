## EXGCD 扩展欧几里德
 - require: c++98
 - [x] 封装
 - [ ] 测试

$$ ax + by = gcd(a, b) $$

Solve $x$, $y$

### 递归

```cpp
ll exgcd(ll a,ll b,ll &x,ll &y){
	if (!b) { x = 1, y = 0; return a; }
	ll c = exgcd(b, a % b, y, x); y -= a / b * x; return c;
}
```

### 迭代

```c++
int exgcd(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}
```