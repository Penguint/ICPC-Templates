## Dijsktra

```c++
void Dijkstra01(Graph &g, int s, vector<ll> &d, vector<int> &vis) {
    d[s] = 0;
    priority_queue<pii> q;
    q.emplace_back(-d[s], s);
    while (q.size()) {
        int u = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (Edge e : g[u]) {
            int v = e.v;
            auto w = e.w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.emplace_back(-d[v], v);
            }
        }
    }
}
```