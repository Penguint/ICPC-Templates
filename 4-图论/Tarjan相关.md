## Tarjan相关
 - require: C++11
 - [ ] 封装
 - [ ] 测试
  
```cpp

struct Edge {
    int v;
};

vector<Edge> E[i];
vector<vector<int>> G(n, vector<int>());

vector<int> low(n), dfn(n), belong(n), instack(n);
stack<int> st;
int scc = 0;
// vector<int> scc;
int timestamp = 0;
function<void(int)> tarjan;
tarjan = [&](int u) {
    dfn[u] = low[u] = ++timestamp;
    st.push(u);
    instack[u] = 1;
    for (auto i : G[u]) {
        int v = E[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++scc;
        // scc.push_back(0);
        int v;
        do {
            v = st.top();
            belong[v] = scc;
            // belong[v] = scc.size() - 1;
            // ++scc.back();
            st.pop();
            instack[v] = 0;
        } while (v != u);
    }
};

// 遍历全图
for (int i = 0; i < n; i++)
    if (!dfn[i])
        tarjan(i, x);

// 计算每个scc的出度入度
vector<int> out_d(n), in_d(n);
for (int u = 0; u < n; u++) {
    for (auto i : G[u]) {
        int v = E[i].v;
        if (belong[u] != belong[v]) {
            out_d[belong[u]]++;
            in_d[belong[v]]++;
        }
    }
}
```