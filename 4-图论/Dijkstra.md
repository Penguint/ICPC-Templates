## Dijsktra

```c++
struct Edge {
    int v;
    ll w;
};
using Graph = vector<vector<Edge>>;

Graph G;

const ll INF = 1e18 + 5;
vector<ll> d;
vector<int> vis;
void Dijkstra(int s) {
    d[s] = 0;
    priority_queue<pii> q;
    q.push({-d[s], s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (Edge e : G[u]) {
            int v = e.v;
            ll w = e.w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.push({-d[v], v});
            }
        }
    }
}
```