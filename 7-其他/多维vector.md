## 多维 vector

```c++
template <size_t I, class T> struct n_vector : vector<n_vector<I - 1, T>> {
    using vector<n_vector<I - 1, T>>::vector;
    template <class... Args>
    n_vector(size_t n, Args... args)
        : vector<n_vector<I - 1, T>>(n, n_vector<I - 1, T>(args...)) {}
};
template <class T> struct n_vector<1, T> : vector<T> {
    using vector<T>::vector;
};
```