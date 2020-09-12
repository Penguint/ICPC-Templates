## XOR 线性基

```c++
template<int d = 31>
struct xor_basis {
    vector<int> bs;
    xor_basis() { bs.resize(d); }
    void insert(int x) { get(x, 1); }
    int get(int x, int update = 0) {
        for (int i = d; i >= 0; i--) if (x >> i & 1) {
            if (!bs[i] && update) { bs[i] = x; break; }
            x ^= bs[i];
        }
        return x;
    }
};
```