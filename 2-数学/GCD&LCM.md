## GCD & LCM
 - require: c++98
 - [x] 封装
 - [ ] 测试

gcd: 最大公因数 (greatest common divisor)   
lcm: 最小公倍数 (least common multiple)

递归版本参考 `std::gcd()` 源码。
非递归版本参考GNU `__gcd()` 源码。  

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

### 递归 GCD
```cpp
template <class T> T gcd(T m, T n) {
    return m == 0 ? n : n == 0 ? m : gcd(n, m % n);
}
```

### 非递归 GCD
```cpp
template <class T> T gcd(T a, T b) {
    while (b != 0) {
        T t = a % b;
        a = b;
        b = t;
    }
    return a;
}
```

### LCM
```cpp
template <class T> T lcm(T m, T n) {
    return (m != 0 && n != 0) ? (m / gcd(m, n)) * n : 0;
}
```
