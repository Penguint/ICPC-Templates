## EXGCD 扩展欧几里德
 - require: c++98
 - [x] 封装
 - [ ] 测试

$$ ax + by = gcd(a, b) $$

Solve $x$, $y$

```cpp
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){x=1;y=0;return a;}
	ll c=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return c;
}
```

### 应用：EXCRT 扩展中国剩余定理（求解同余方程组）

```cpp
pair<ll, ll> ex_crt(vector<ll> m, vector<ll> r, int nn) // <最小解，[1,nn]解个数>
{
    int n = m.size();
    // cout << n<< "\n";
    ll M = m[0], R = r[0], x, y, gcd;
    for (int i = 1; i < n; i++) {
        gcd = exgcd(M, m[i], x, y);
        if ((r[i] - R) % gcd)
            return {-1, 0};
        ll gx = m[i] / gcd;
        x = x * (r[i] - R) / gcd;
        x %= gx;
        R += x * M;
        M = M / gcd * m[i];
        R %= M;
    }
    if (R <= 0)
        R += M;
    if (nn < R)
        return {R, 0};
    return make_pair(R, (nn - R) / M + 1);
}
```
