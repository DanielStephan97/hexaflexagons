/**
 * Author: HPI programming club
 * Date: 2019-11-10
 * License: CC0
 * Source: N/A
 * Description: Flow algorithm with guaranteed complexity $O(VE^2)$.
 * To obtain the actual flow, look at positive values only.
 * Status: Working
 */
struct edge {
    int from, to;
    ll flow, cap;
    edge* twin;
};
struct EkFlow {
    EkFlow(int n) : adj(n) {}
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
    ll eddy(int s, int t) {
        ll flow = 0;
        while(true) {
            vector<edge *> inc(adj.size(), nullptr);
            queue<int> q{{s}};
            while (!q.empty()) {
                auto v = q.front(); q.pop();
                for (auto e : adj[v])
                    if (!inc[e->to] && e->flow < e->cap)
                        q.push(e->to), inc[e->to] = e;
            }
            if (!inc[t]) break;
            ll aug = 1e18;
            for (int v = t; v != s; v = inc[v]->from)
                aug = min(aug, inc[v]->cap - inc[v]->flow);
            flow += aug;
            for (int v = t; v != s; v = inc[v]->from)
                inc[v]->flow += aug, inc[v]->twin->flow -= aug;
        }
        return flow;
    }
};
