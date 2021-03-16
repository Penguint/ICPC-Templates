## Log2

### y = floor(log2(x))

2^y 是第一个小于等于 x 的 2^k. 

```c++
int floorlog2(int x) {
    return floor(log2(x) + EPS);
}

// Quick lookup table for floor(log2(i)),
// 1 <= x <= N
int _floorlog2[N];
void init_floorlog2(int n) {
    for (int i = 2; i <= n; i++)
        _floorlog2[i] = _floorlog2[i / 2] + 1;
}
int floorlog2(int x) {
    return _floorlog2[x]; 
}

// Binary approach
int32_t floorlog2(int x) {
    return 32 - __builtin_clz(x) - 1;
}
```

### y = ceil(log2(x))

2^y 是第一个大于等于 x 的 2^k. 

```c++
int ceillog2(int x) {
    return ceil(log2(x) + EPS);
}

// Quick lookup table for ceil(log2(i)),
// 1 <= x <= N
int _ceilog2[N];
void init_ceillog2(int n) {
    for (int i = 2; i <= n; i++)
        _ceillog2[i] = _ceillog2[(i + 1) / 2] + 1;
}
int ceillog2(int x) {
    return _ceillog2[x]; 
}

// Binary approach
unsigned int nextPowerOf2(unsigned int n)   
{ 
    n--; 
    n |= n >> 1; 
    n |= n >> 2; 
    n |= n >> 4; 
    n |= n >> 8; 
    n |= n >> 16; 
    n++; 
    return n; 
}
int32_t ceillog2(int x) {
    return 32 - __builtin_clz(nextPowerOf2(x)) - 1;
}
```
