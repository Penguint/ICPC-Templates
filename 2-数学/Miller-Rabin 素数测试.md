## Miller-Rabin 素数测试

- [x] 封装
- [ ] 测试

```c++
mt19937 rand(chrono::system_clock::now().time_since_epoch().count()); 
bool Miller_Rabin(ll n, int times = 20)
{
	if (n < 2) return 0;
	if (n == 2) return 1;
	if ((n & 1) == 0) return 0;

	ll x = n - 1, sum = 0;
	while (x % 2 == 0)
		x >>= 1, sum++;
 
	while(times--) {
		ll a = rand() % (n - 1) + 1; //取与p互质的整数a
		if (!Witness(a, n, x, sum)) return 0; //费马小定理的随机数检验
	}
	return 1;
}
```