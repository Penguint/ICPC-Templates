# 单调队列
 - v1.2
 - require: C++98
 - [x] 封装
 - [x] 已测试

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