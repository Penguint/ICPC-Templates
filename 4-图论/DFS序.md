## DFS序
 - [ ] 封装
 - [ ] 测试

```cpp
struct t_node {
    int ti, to;

    bool is_ancestor(t_node a) { return a.ti <= ti && to <= a.to; }
};

vector<t_node> vertexs(n);

int timestamp;
void dfs(int u, int p, int depth) {
    vertexs[u].tin = ++timestamp;

    for (int v : g[u])
        if (v == p) continue;
            dfs(v, depth + 1, u);

    vertexs[u].tout = ++timestamp;  
}

// demo
int main() {

    timestamp = 0;
    dfs(1, 0, -1);
    
}
```