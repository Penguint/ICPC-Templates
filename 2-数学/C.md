## 组合数 C(n, m)

 - require: c++98
 - [x] 封装
 - [ ] 测试

$$
C(n, m) = C_{n}^{m} = {n \choose m} = \frac{n!}{m!(n-m)!}
$$

### 广义组合数

用于广义二项式定理中。

n 扩展到整数域：

$$
{n \choose m} = 
\begin{cases}
    \frac{n!}{m!(n-m)!} & m \ge 0, n \ge m \\
    0 & m \ge 0, 0 \le n < m \\
    {m - 1 - n \choose m} & m \ge 0, n < 0
\end{cases}
$$

n 扩展到实数域：

$$
{r \choose k} = \frac{r(r-1)\cdots(r-k+1)}{k!} = \frac{r^{\underline{k}}}{k!} = \frac{(r)_k}{k!}
$$

### 预处理阶乘

支持 n < 1e6;

预处理 $O(n)$, 查询 $O(1)$

```cpp
// int fac();
// int invfac();
inline int C(int n,int m) {
    // if (n < 0) return C(m - 1 - n, m); // n 扩展到整数域
    if (n < m) return 0;
    return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
}
```

```c++
int C(int m,int n,int p,int pk)   //处理组合数
{
	int nn = fac_pk(n, p, pk), mm = fac_pk(m, p, pk), 
		nm = fac_pk(n - m, a, b), po=0;  //求阶乘
	for (int i = n; i; i /= a) po += i / a;     //处理n^p中的p
	for (int i = m; i; i /= a) po -= i / a;
	for (int i = n - m; i; i /= a) po -= i / a;
	return nn * qpow(p, po, pk) % pk * inv(mm, pk) % pk * inv(nm,pk) % pk; 
}
inline ll C(ll n,ll m,,ll p,ll pk)
//求C(n,m)%mod,其中唯一分解之后质因子为p,总乘积为pk(pi^ci)
{
	if(m>n)return 0;
	ll a=mul(n,p,pk),b=mul(m,p,pk),c=mul(n-m,p,pk),k=0;
	//先求一下n!%pi^ci,m!%pi^ci,(n-m)!%pi^ci 
	for(ll i=n;i;i/=p)k+=i/p;
	for(ll i=m;i;i/=p)k-=i/p;
	for(ll i=n-m;i;i/=p)k-=i/p;
	//先除掉n!,m!,(n-m)!在%mod下的质因子p
	ll ans=1ll*a*rev(b,pk)%pk*rev(c,pk)%pk*poww(p,k,pk)%pk;
	//除去质因子p之后直接逆元求组合数(剩余部分) 
	return 1ll*ans*(mod/pk)%mod*rev(mod/pk,pk)%mod;
	//找到逆元了再乘回去(CRT合并)
}
```