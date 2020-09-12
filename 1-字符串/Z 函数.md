## Z 函数（扩展 KMP）

Z 函数为字符串 s 每一个后缀 s_suffix 和 s 本身的 LCP

### string 版

```c++
vector<int> z_function(string s) {
    int n = (int)s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
```

### char[] 版

```c++
void z_function(char s[], int n, int z[]) {
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
```

### 字符串匹配极速版

专用于两个字符串的匹配。

传入两个字符串，避免了字符串拷贝。

```c++
void z_function(char s1[], int n1, char s2[], int n2, int ext[], int nxt[]){
    int i = 0, p = 0; nxt[0] = n2;
    while (i < n1 && i < n2 && s1[i] == s2[i]) ++i; ext[p] = i;
    for (int i = 1; i < n1; ++i) {
        if(i + nxt[i - p] < p + ext[p]) ext[i] = nxt[i - p];
        else {
            int j = max(0, p + ext[p] - i);
            while (i + j < n1 && j < n2 && s1[i + j] == s2[j]) ++j;
            ext[i] = j; p = i;
        }
    }
}

// 使用
char a[N], b[N];
int za[N], zb[N];
int main() {
    /* ... */
    z_function(b + 1, lenb - 1, b, lenb, zb + 1, zb); // 预处理模式串
    z_function(a, lena, b, lenb, za, zb);
    /* ... */
}
```

