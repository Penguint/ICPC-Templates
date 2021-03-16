## LCA

```c++
    int ts; // table_size
    vector<vi> anc;
    vi in, out;

    void get_ancestor(int u) {
        ts = 32 - __builtin_clz(n) + 1; // table size
        anc = vector<vi>(n, vi(ts, -1));
        function<void(int, int)> dfs = [&](int u, int p) {
            anc[u][0] = p;
            for (int i = 0; i < ts - 1; i++)
                anc[u][i + 1] = anc[u][i] == -1
                                    ? -1
                                    : anc[anc[u][i]][i];
            for (auto &e : adj[u]) {
                int v = e;
                if (v == p)
                    continue;
                dfs(v, u);
            }
        };
        dfs(u, -1);
    }

    void get_in_out(int u) {
        in = vi(n);
        out = vi(n);
        int timer = 0;
        function<void(int, int)> dfs = [&](int u, int p) {
            in[u] = ++timer;
            for (auto &e : adj[u]) {
                int v = e;
                if (v == p)
                    continue;
                dfs(v, u);
            }
            out[u] = ++timer;
        };
        dfs(u, -1);
    }

    bool is_ancestor(int a, int b) {
        return in[a] <= in[b] && out[b] <= out[a];
    }

    int lca(int a, int b) {
        if (is_ancestor(a, b))
            return a;
        for (int i = ts - 1; i >= 0; i--)
            if (anc[a][i] != -1 &&
                !is_ancestor(anc[a][i], b))
                a = anc[a][i];
        return anc[a][0];
    }
```