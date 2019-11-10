/**
 * Author: HPI programming club
 * Date: 2019-11-10
 * License: CC0
 * Source: 
 * Description: Flow algorithm with complexity $O(V^2E)$.
 * $O(\sqrt{V}E)$ for unit graphs (especially bipartite matching).
 * To obtain the actual flow, look at positive values only.
 * Status: Tested
 */
struct edge {
    int from, to;
    ll flow, cap;
    edge* twin;
};
struct flow {
    flow(int n, int s, int t) : adj(n), s(s), t(t) {}
    vector<vector<edge*>> adj;
    int s, t;
    void add_edge(int a, int b, ll cap) {
        auto ab = new edge{a, b, 0, cap, nullptr};
        //auto ba = new edge{b, a, 0, cap, ab}; //undirected graph
        auto ba = new edge{b, a, 0, 0, ab}; //directed graph
        ab->twin = ba;
        adj[a].push_back(ab);
        adj[b].push_back(ba);
    }
    ll dfs(int v, ll aug, vector<int> &dist, vector<int> &next) {
        if (v == t) return aug;
        for (int& i = next[v]; i<adj[v].size(); ++i) {
            auto e = adj[v][i];
            if (e->flow == e->cap || dist[e->to] != dist[v] + 1) continue;
            if(ll pushed = dfs(e->to,min(aug, e->cap - e->flow), dist, next)) {
                e->flow += pushed;
                e->twin->flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    ll dinic() {
        ll flow = 0;
        while(true) {
            vector<int> dist(adj.size(), INTINF);
            dist[s] = 0;
            queue<int> q{{s}};
            while (!q.empty()) {
                auto v = q.front(); q.pop();
                for (auto e : adj[v])
                    if (dist[e->to] == INTINF &&e->flow < e->cap)
                        q.push(e->to), dist[e->to] = dist[v] + 1;
            }
            if (dist[t] == INTINF) break;
            vector<int> next(adj.size(), 0);
            while(ll aug = dfs(s,LONGINF, dist, next)) flow += aug;
        }
        return flow;
    }
};
