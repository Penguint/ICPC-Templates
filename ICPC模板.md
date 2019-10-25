
# 目录  <!-- omit in toc -->
- [1 字符串](#1-字符串)
- [2 数学](#2-数学)
  - [2.1 GCD & LCM](#21-gcd--lcm)
  - [2.2 扩展GCD](#22-扩展gcd)
- [3 数据结构](#3-数据结构)
  - [3.1 单调队列](#31-单调队列)
  - [3.2 ZKW线段树](#32-zkw线段树)
  - [3.3 并查集](#33-并查集)
- [4 图论](#4-图论)
- [5 动态规划](#5-动态规划)
- [6 计算几何](#6-计算几何)
- [7 其他](#7-其他)
  - [7.1 高精度](#71-高精度)
  - [7.2 二分答案](#72-二分答案)
  - [7.3 Berlekamp-Massey](#73-berlekamp-massey)
  - [7.4 Java高精度根号](#74-java高精度根号)
  - [7.5 博弈论](#75-博弈论)
  - [7.6 蔡勒公式](#76-蔡勒公式)

<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 1 字符串





<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 2 数学

## 2.1 GCD & LCM
 - require: c++98
 - [x] 封装
 - [ ] 测试

gcd: 两个整数的最大公因数 (greatest common divisor)   
lcm: 两个整数的最小公倍数 (least common multiple)

非递归版本参考于GNU `__gcd()` 源码。  
递归版本参考于 `std::gcd()` 源码。

### 相关函数  <!-- omit in toc -->
 - `std::gcd()`
   - 定义在 `<numeric>`
   - require: C++17
 - `std::lcm()`
   - 定义在 `<numeric>`
   - require: C++17
 - `__gcd()`
   - 定义在`<algorithm>`
   - require: C++98, GNU平台

### 2.1.1 非递归 GCD  <!-- omit in toc -->
```C++
template <typename T> T gcd(T m, T n) {
    while (n != 0) {
        T t = m % n;
        m = n;
        n = t;
    }
    return m;
}
```

### 2.1.2 递归 GCD  <!-- omit in toc -->
```C++
template <typename T> T gcd(T m, T n) {
    return m == 0 ? n : n == 0 ? m : gcd(n, m % n);
}
```

### 2.1.3 LCM  <!-- omit in toc -->
```C++
template <typename T> T lcm(T m, T n) {
    return (m != 0 && n != 0) ? (m / gcd(m, n)) * n : 0;
}
```

## 2.2 扩展GCD




<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 3 数据结构

## 3.1 单调队列
 - require: C++98
 - [x] 封装
 - [x] 测试

这个版本相当于是对STL库中 `deque` 的重写，但引入了比较模板类。实际使用场景比较灵活，可能并不能照搬，但可以作为参考，并在STL的 `deque` 太慢时作为替换。

```C++
template <typename T, typename Cmp = less_equal<T> > struct Monoq {
    Cmp comp;
    const static int N = MAXN;
    T q[N];
    int ft, bk;
    inline Monoq() : ft(0), bk(0) {}
    inline bool empty() { return bk - ft <= 0; }
    inline int size() { return bk - ft; }
    inline T front() { return q[ft]; }
    inline T back() { return q[bk - 1]; }
    inline void push(T x) {
        while (!empty() && comp(x, back()))
            bk--;
        q[bk++] = x;
    }
    inline void pop_back() {
        if (!empty())
            bk--;
    }
    inline void pop_front() {
        if (!empty())
            ft++;
    }
    inline void clear() { ft = 0, bk = 0; }
    inline T *begin() { return q + ft; }
    inline T *end() { return q + bk; }
};

int a[50] = {3, 6, 7, 5, 3, 5, 6, 2, 9, 1, 2, 7, 0, 9, 3, 6, 0, 6, 2, 6};
struct MyCmp {
    inline bool operator()(int x, int y) {
        return a[x] <= a[y]; // strict increase monoq
        // return a[x] >= a[y]; // strict decrease monoq
    }
};

Monoq<int, MyCmp> q;
```

## 3.2 ZKW线段树
 - require: C++98
 - HDU1698
 - [ ] 封装
 - [x] 测试


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

## 3.3 并查集
 - require:
 - [x] 封装
 - [x] 测试


```C++
using namespace std;

class UnionFindSet {
  public:
    int f[150001];
    int n;
    void clear() {
        for (int i = 0; i < n; i++)
            f[i] = i;
    }
    int find(int x) {
        if (f[x] != x)
            f[x] = find(f[x]);
        return f[x];
    }
    void Union(int x, int y) {
        f[find(x)] = find(y);
    }
} animal;
```




<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 4 图论



<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 5 动态规划

<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 6 计算几何




<!-- 分页符 -->
<div style="page-break-after: always;"></div>

# 7 其他

## 7.1 高精度
 - require: C++11
 - [x] 封装
 - [ ] 测试

高精度四则运算。
```C++
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Unsigned_BigInt {
    ll k = 10; // base-k positional notation
    vector<ll> a;
    Unsigned_BigInt() {
        a.clear();
        a.push_back(0);
    }
    Unsigned_BigInt(ll v) {
        a.clear();
        a.push_back(abs(v));
        this->regular();
    }
    Unsigned_BigInt(string s) {
        a.clear();
        for (ll i = s.length() - 1; i >= 0 && s[i] != '-'; i--)
            a.push_back(s[i] - '0');
    }
    void regular() {
        for (ll i = 0; i < a.size(); i++)
            if (a[i] >= k || a[i] < 0) {
                if (i + 1 < a.size())
                    a[i + 1] += (a[i] >= 0 ? a[i] / k : (a[i] + 1) / k - 1);
                else
                    a.push_back(a[i] / k);
                a[i] = (a[i] % k + k) % k;
            }
    }
    void give(ll i, ll v) {
        if (i < a.size())
            a[i] += v;
        else
            a.push_back(v);
    }
    void shrink() {
        for (ll i = a.size() - 1; i >= 0 && a[i] == 0; i--)
            a.pop_back();
        if (a.empty())
            a.push_back(0);
    }
    bool operator<(const Unsigned_BigInt &b) const {
        if (a.size() == b.a.size()) {
            ll i = a.size() - 1;
            while (a[i] == b.a[i] && i >= 0)
                i--;
            return i >= 0 ? a[i] < b.a[i] : false;
        } else
            return a.size() < b.a.size();
    }
    Unsigned_BigInt operator+(const Unsigned_BigInt &b) const {
        Unsigned_BigInt c;
        for (ll i = 0; i < max(a.size(), b.a.size()); i++)
            c.give(i,
                   (i < a.size() ? a[i] : 0) + (i < b.a.size() ? b.a[i] : 0));
        c.regular();
        return c;
    }
    Unsigned_BigInt operator-(const Unsigned_BigInt &b) const {
        Unsigned_BigInt c;
        bool less = *this < b;
        for (ll i = 0; i < max(a.size(), b.a.size()); i++) {
            ll temp = (i < a.size() ? a[i] : 0) - (i < b.a.size() ? b.a[i] : 0);
            c.give(i, !less ? temp : -temp);
        }
        c.regular();
        c.shrink();
        return c;
    }
    Unsigned_BigInt operator*(const ll &b) const {
        ll bb = abs(b);
        Unsigned_BigInt c;
        for (ll i = 0; i < a.size(); i++)
            c.give(i, a[i] * bb);
        c.regular();
        return c;
    }
    Unsigned_BigInt operator*(const Unsigned_BigInt &b) const {
        Unsigned_BigInt c;
        for (ll i = 0; i < b.a.size(); i++)
            for (ll j = 0; j < a.size(); j++)
                c.give(j + i, a[j] * b.a[i]);
        c.regular();
        return c;
    }
    Unsigned_BigInt operator/(const ll &b) const {
        ll bb = abs(b);
        Unsigned_BigInt c = *this;
        ll dividend = 0;
        for (ll i = a.size() - 1; i >= 0; i--) {
            dividend = dividend * k + a[i];
            c.a[i] = dividend / bb;
            dividend %= bb;
        }
        c.shrink();
        return c;
    }
    ll operator%(const ll &b) const {
        ll r = 0;
        for (ll i = a.size() - 1; i >= 0; i--)
            r = ((r * k) % b + a[i]) % b;
        return r;
    }
    void print() {
        for (auto it = a.rbegin(); it != a.rend(); it++)
            // cout << *it;
            printf("%lld", *it);
        // cout << endl;
        printf("\n");
    }
};

struct BigInt {
    bool sign = false; // 0: +, 1: -
    Unsigned_BigInt num;
    BigInt() : sign(0), num(Unsigned_BigInt()) {}
    BigInt(ll v) : sign(v < 0), num(Unsigned_BigInt(v)) {}
    BigInt(string s) : sign(s[0] == '-'), num(Unsigned_BigInt(s)) {}
    BigInt(Unsigned_BigInt num, bool sign = false) : sign(sign), num(num) {}
    bool operator<(const BigInt &b) const {
        if (sign ^ b.sign)
            return sign;
        else
            return ((!sign) ? num < b.num : b.num < num);
    }
    BigInt operator+(const BigInt &b) const {
        if (sign)
            return -(-*this - b); // a + b == -(-a - b)
        if (b.sign)
            return *this - (-b); // a + b == a - (-b)
        return BigInt(num + b.num);
    }
    BigInt operator-() const { return BigInt(num, !sign); }
    BigInt operator-(const BigInt &b) const {
        if (sign)
            return -(-*this + b); // a - b == -(-a + b)
        if (b.sign)
            return *this + (-b); // a - b == a + (-b)
        return BigInt(num - b.num, num < b.num);
    }
    BigInt operator*(const ll &b) const {
        return BigInt(num * b, sign ^ b < 0);
    }
    BigInt operator*(const BigInt &b) const {
        return BigInt(num * b.num, sign ^ b.sign);
    }
    BigInt operator/(const ll &b) const {
        return BigInt(num / b, sign ^ b < 0);
    }
    ll operator%(const ll &b) const { return sign ? -(num % b) : num % b; }
    void print() {
        // cout << (!sign || (num.a.size() == 1 && num.a[0] == 0) ? "" : "-");
        printf(!sign || (num.a.size() == 1 && num.a[0] == 0) ? "" : "-");
        num.print();
    }
};

ostream &operator<<(ostream &os, const Unsigned_BigInt &b) {
    for (auto it = b.a.rbegin(); it != b.a.rend(); it++)
        os << *it;
    return os;
}
ostream &operator<<(ostream &os, const BigInt &b) {
    os << (!b.sign || (b.num.a.size() == 1 && b.num.a[0] == 0) ? "" : "-");
    os << b.num;
    return os;
}

int main() {
    string s1;
    string s2;
    // freopen("./test.in", "r", stdin);
    // freopen("./test.out", "w", stdout);

    while (cin >> s1 >> s2) {
        cout << (BigInt(s1) * BigInt(s2));
        // (BigInt(s1) * BigInt(s2)).print();
    }

    // fclose(stdin);
    // fclose(stdout);
}
```

## 7.2 二分答案
 - require: C++11
 - [x] 封装
 - [ ] 测试

对给定函数的 `y`，二分查找 `x`

### 离散  <!-- omit in toc -->

```C++
#include <bits/stdc++.h>
using namespace std;

template <typename T> bool dec(T _a, T _b) { return greater<T>()(_a, _b); }
template <typename T> bool inc(T _a, T _b) { return less<T>()(_a, _b); }
// template <typename T> bool incid(T _a, T _b) {
//     return less<T>()(a[_a].id, a[_b].id);
// }

int a[10] = {7, 5, 5, 5, 3, 3, 3, 1, 1, 1};

template <typename Tx = int, typename Ty = int>
Tx upperbound(Ty(getval)(Tx), Tx first, Tx last, const Ty &val,
              bool(comp)(Ty, Ty) = inc<Ty>) {
    Tx len = last - first;
    while (len > 0) {
        Tx half = len >> 1;
        Tx middle = first + half;
        if (comp(val, getval(middle)))
            len = half;
        else {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template <typename Tx = int, typename Ty = int>
Tx lowerbound(Ty(getval)(Tx), Tx first, Tx last, const Ty &val,
              bool(comp)(Ty, Ty) = inc<Ty>) {
    Tx len = last - first;
    while (len > 0) {
        Tx half = len >> 1;
        Tx middle = first + half;
        if (comp(getval(middle), val)) {
            first = middle + 1;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

int geta(int i) { return a[i]; }

int main() { cout << upperbound(geta, 0, 10, 1, dec<int>); }
```

## 7.3 Berlekamp-Massey
 - require: 
 - [x] 封装
 - [ ] 测试

求解线性递推第 `n` 项， 下标从 `0` 开始

```C++
#include <bits/stdc++.h>
 
using namespace std;
#define rep(i,a,n) for (long long i=a;i<n;i++)
#define per(i,a,n) for (long long i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((long long)(x).size())
typedef vector<long long> VI;
typedef long long ll;
typedef pair<long long,long long> PII;
const ll mod=1e9+7;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head
 
long long n;
namespace linear_seq
{
    const long long N=10010;
    ll res[N],base[N],_c[N],_md[N];
 
    vector<long long> Md;
    void mul(ll *a,ll *b,long long k)
    {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k)
            _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (long long i=k+k-1;i>=k;i--) if (_c[i])
            rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    long long solve(ll n,VI a,VI b)
    { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
//        printf("%d\n",SZ(b));
        ll ans=0,pnt=0;
        long long k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (long long p=pnt;p>=0;p--)
        {
            mul(res,res,k);
            if ((n>>p)&1)
            {
                for (long long i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s)
    {
        VI C(1,1),B(1,1);
        long long L=0,m=1,b=1;
        rep(n,0,SZ(s))
        {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n)
            {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            }
            else
            {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    long long gao(VI a,ll n)
    {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
};
 
int main()
{
    while(~scanf("%I64d", &n))
    {   printf("%I64d\n",linear_seq::gao(VI{1,5,11,36,95,281,781,2245,6336,18061, 51205},n-1));
    }
}
```

## 7.4 Java高精度根号
 - require: Java 8
 - [x] 封装
 - [ ] 测试

牛顿迭代法 (Newton-Raphson method)

```Java
import java.math.BigDecimal;
import java.math.RoundingMode;

public class Main {

    private static final BigDecimal SQRT_DIG = new BigDecimal(1000);
    private static final BigDecimal SQRT_PRE = new BigDecimal(10).pow(SQRT_DIG.intValue());

    private static BigDecimal sqrtNewtonRaphson(BigDecimal c, BigDecimal xn, BigDecimal precision) {
        BigDecimal fx = xn.pow(2).add(c.negate());
        BigDecimal fpx = xn.multiply(new BigDecimal(2));
        BigDecimal xn1 = fx.divide(fpx, 2 * SQRT_DIG.intValue(), RoundingMode.HALF_DOWN);
        xn1 = xn.add(xn1.negate());
        BigDecimal currentSquare = xn1.pow(2);
        BigDecimal currentPrecision = currentSquare.subtract(c);
        currentPrecision = currentPrecision.abs();
        if (currentPrecision.compareTo(precision) <= -1)
            return xn1;
        return sqrtNewtonRaphson(c, xn1, precision);
    }

    public static BigDecimal bigSqrt(BigDecimal c) {
        return sqrtNewtonRaphson(c, new BigDecimal(1), new BigDecimal(1).divide(SQRT_PRE));
    }
}
```

## 7.5 博弈论

### 7.5.1 Bash Game  <!-- omit in toc -->

有一堆 `n` 个物品，两个人轮流从中取物，规定每次取 `[1, m]` 个，最后取光者为胜。

```C++
int Bash(int n, int m){
    return n % (m + 1);
}
```

### 7.5.2 Wythoff Game  <!-- omit in toc -->

有两堆物品，数量分别为 `a` 和 `b` ，两人轮流从其中一堆取 `[1, +∞]` 个，或从两堆中同时取相等的 `[1, +∞]` 个物品，最后取光者为胜。

```C++
int Wythoff(int a, int b) {
    double k = (sqrt(5.0) + 1) / 2;
    return floor(k * abs(a - b)) != min(a,b);
}v
```

### 7.5.3 Nim Game  <!-- omit in toc -->

有若干堆物品，每堆有 `v[i]` 个物品，双方轮流从中取物品，每一次从一堆物品中取 `[1, v[i]]` 个，取到最后一件物品的人获胜。

```C++
int Nim(vector<int> v) {
    int res = 0;
    for (int i : v)
        res ^= i;
    return res;
}
```

## 7.6 蔡勒公式
 - require:
 - [x] 封装
 - [ ] 测试

输入年、月、日，计算格里高利历的星期。

有两种表示星期的方式：

 - Zeller
    |     |           |
    | --- | --------- |
    | 0   | Saturday  |
    | 1   | Sunday    |
    | 2   | Monday    |
    | 3   | Tuesday   |
    | 4   | Wendesday |
    | 5   | Thursday  |
    | 6   | Friday    |

 - ISO week date
    |     |           |
    | --- | --------- |
    | 1   | Monday    |
    | 2   | Tuesday   |
    | 3   | Wendesday |
    | 4   | Thursday  |
    | 5   | Friday    |
    | 6   | Saturday  |
    | 7   | Sunday    |

```C++
int Zeller(int y, int m, int d) {
    if (m == 1 || m == 2)
        m += 12, y = y - 1;
    int h = (d + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    int w = (h + 5) % 7 + 1; // ISO week date (1 = Monday, 7 = Sunday)
    return w;
}
```