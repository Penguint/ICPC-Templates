## Miller-Rabin 素数测试

- [x] 封装
- [ ] 测试

```c++
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    for (a %= mod; b; b >>= 1, a = (__int128)a * (__int128)a % mod)
        if (b & 1) res = (__int128)res * (__int128)a % mod;
    return res;
}

// ll qpow(ll a, ll b, ll mod = mod) {
//     ll res = 1;
//     for (a %= mod; b; b >>= 1, a = a * a % mod)
//         if (b & 1) res = res * a % mod;
//     return res;
// }

// ll qmul(ll a, ll b, ll mod = mod) {
//     ll res = 0;
//     for (a %= mod; b; b >>= 1, a = (a + a) % mod)
//         if (b & 1) res = (res + a) % mod;
//     return res;
// }

// mt19937 ran(chrono::system_clock::now().time_since_epoch().count());   // slow
template<const int test_case>
bool Miller_Rabin(ll x) {
	if (x <= 2) return x == 2;
	if (!(x & 1)) return 0;

	ll s = 0, t = x - 1;
	while (!(t & 1))
		s++, t >>= 1;
 
	for (int i = 0; i < test_case; i++) {
		ll a = rand() % (x - 2) + 2;
		ll b = qpow(a, t, x);

		if (b == 1 || b == x - 1) continue;
		int j;
		for (j = 0; j < s; j++) {
			b = (__int128)b * (__int128)b % x;
			// b = qmul(b, b, x);
			if (b == x - 1) break;
		}
		if (j >= s) return false;
	}
	return true;
}
```