## GCD & LCM
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

### 非递归 GCD  <!-- omit in toc -->
```cpp
template <typename T> T gcd(T m, T n) {
    while (n != 0) {
        T t = m % n;
        m = n;
        n = t;
    }
    return m;
}
```

### 递归 GCD  <!-- omit in toc -->
```cpp
template <typename T> T gcd(T m, T n) {
    return m == 0 ? n : n == 0 ? m : gcd(n, m % n);
}
```

### LCM  <!-- omit in toc -->
```cpp
template <typename T> T lcm(T m, T n) {
    return (m != 0 && n != 0) ? (m / gcd(m, n)) * n : 0;
}
```
