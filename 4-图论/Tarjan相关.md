## Tarjan相关
 - require: C++11
 - [ ] 封装
 - [ ] 测试

$O(M)$

注意 scc, belong 这些额外信息能省略则省略， 能化简则化简，否则虽然复杂度是对的，但是可能被卡常。

若被卡常，先考虑实现上可优化的点。要算该种实现的复杂度。

```cpp
struct Edge {
    int v;
};
vector<Edge> edges(m);

vector<int> dfn(N), low(N), inst(N);
stack<int> st;
int tim = 0;
void Tarjan(vector<vector<int>> &adj, int u, vector<vector<int>> &scc, vector<int> &belong) {
    dfn[u] = low[u] = ++tim;
    st.push(u), inst[u] = 1;

    for (auto i : adj[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
            Tarjan(adj, v, scc, belong);
            low[u] = min(low[u], low[v]);
        } else if (inst[v])
            low[u] = min(low[u], dfn[v]);
    }
    
    if (low[u] == dfn[u]) {
        scc.push_back({});
        int v;
        do {
            v = st.top();
            st.pop(), inst[v] = 0;
            scc.back().push_back(v);
            belong[v] = scc.size() - 1;
        } while (v != u);
    }
};

// 遍历全图
vector<vector<int>> scc;
vector<int> belong(n, -1);
dfn.assign(n, 0);
for (int i = 0; i < n; i++)
    if (!dfn[i])
        tarjan(adj, i, scc, belong);

// 计算每个scc的出度入度
vector<int> out_d(n), in_d(n);
for (int u = 0; u < n; u++) {
    for (auto i : adj[u]) {
        int v = edges[i].v;
        if (belong[u] != belong[v]) {
            out_d[belong[u]]++;
            in_d[belong[v]]++;
        }
    }
}
```