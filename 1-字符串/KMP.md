## KMP

查找字符串 T 在字符串 S 中出现的所有位置。

```c++
vector<int> KMP(string &S, string &T) {
    vector<int> nxt;

    nxt.push_back(-1);
    for (int i = 0, j = -1; i < sz(T);) {
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != sz(T) && T[i] == T[j]) // 加上这三行才是KMP，否则是MP
                nxt.push_back(nxt[j]);    //
            else                            // 
                nxt.push_back(j);
        } else
            j = nxt[j];
    }

    vector<int> res;
    for (int i = 0, j = 0; i < sz(S) && j < sz(T);) {
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == sz(T)) {
                res.push_back(i - j);
                j = nxt[j];
            }
        } else
            j = nxt[j];
    }
    return res;
}
```

```c++
int get(string &str, int x, char ch) {
    while (1) {
        if (str[x] == ch) return x + 1;
        if (!x) return 0;
        x = nxt[x];
    }
}

vector<int> KMP(string &s, string &str) {
    int n = s.size(), m = str.size();
    vector<int> nxt(m + 1);
    for (int i = 2; i <= m; ++i) nxt[i] = get(str, nxt[i - 1], str[i - 1]);

    vector<int> res;
    int t = 0;
    for (int i = 0; i < n; ++i) {
        t = get(str, t, s[i]);
        if (t == m)
            res.push_back(i - m + 1);
    }
    return res;
}
```
