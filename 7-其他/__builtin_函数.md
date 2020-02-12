## __builtin_函数

参考来源：[https://gcc.gnu.org/onlinedocs/gcc-9.2.0/gcc/Other-Builtins.html]()

```cpp
int __builtin_ffs (unsigned int x)       // 求x的二进制数中最低位1的位置
// __builtin_ffs(0100) == 3;

int __builtin_clz (unsigned int x)       // 求x的二进制数前导0的个数(ps:一共有32位)
// __builtin_clz(0100) == 29;

int __builtin_ctz (unsigned int x)       // 求x的二进制数末尾0的个数
// __builtin_ctz(0100) == 2;

int __builtin_clrsb (int x)              // (since GCC 4.7.4)求x的二进制数最高位开始的连续的和符号位相同的位数

int __builtin_popcount (unsigned int x)  // 求x的二进制数中的1的个数
// __builtin_popcount(0100) == 1;

int __builtin_parity (unsigned int x)    // 求x的二进制数中1的个数的奇偶性(奇数为1 偶数为0)
// __builtin_parity(0100) == 1;

int __builtin_ffsll (unsigned long long)
int __builtin_clzll (unsigned long long)
int __builtin_ctzll (unsigned long long)
int __builtin_clrsbll (long long)        // (since GCC 4.7.4)
int __builtin_popcountll (unsigned long long)
int __builtin_parityll (unsigned long long)
```