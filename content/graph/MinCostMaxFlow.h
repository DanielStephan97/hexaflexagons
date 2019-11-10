/**
 * Author: HPI programming club
 * Date: 2019-11-10
 * Source: 
 * Description: Min-cost max-flow.
 *  Negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 *  Without negative cost edges remove bellman-ford and $O(EV)$ from runtime
 * Status: Tested
 * Time: Approximately $O(EF\log V + EV)$, F flow value.
 */
struct edge {
    int from, to;
    ll flow, cap, cost;
    edge* twin;
};
struct flow {
    flow(int n, int s, int t) : adj(n), s(s), t(t) {}
    vector<vector<edge*>> adj;
    int s, t;
    void add_edge(int a, int b, ll cap, ll cost) {
        auto ab = new edge{a, b, 0, cap, cost, nullptr};
        auto ba = new edge{b, a, 0, 0, -cost, ab};
        ab->twin = ba;
        adj[a].push_back(ab);
        adj[b].push_back(ba);
    }
    void bellman_ford(vector<ll>& dist) {
        dist.assign(adj.size(), LONGINF);
        vector<bool> inq(adj.size(), false);
        queue<int> q{{s}};
        inq[s] = true; dist[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop(); inq[v] = false;
            for (auto e : adj[v]) {
                if (e->flow < e->cap && dist[e->from] + e->cost < dist[e->to]) {
                    dist[e->to] = dist[e->from] + e->cost;
                    if (!inq[e->to])
                        inq[e->to] = true, q.push(e->to);
                }
            }
        }
    }
    pair<ll, ll> costflow() {
        int n = adj.size();
        vector<ll> dist(n), pi(n);
        vector<edge *> inc(n);
        bellman_ford(pi);
        ll value = 0;
        while (1) {
            dist.assign(n, LONGINF);
            inc.assign(n, nullptr);
            priority_queue<pair<ll, int>> q;
            q.emplace(0, s);
            dist[s] = 0;
            while (q.size()) {
                auto[d, v] = q.top(); q.pop(); d = -d;
                if (d > dist[v]) continue;
                for (auto e : adj[v]) {
                    auto new_dist = d + pi[v] + e->cost - pi[e->to];
                    if (e->flow < e->cap && new_dist < dist[e->to]) {
                        dist[e->to] = new_dist;
                        q.emplace(-new_dist, e->to);
                        inc[e->to] = e;
                    }
                }
            }
            if (!inc[t]) break;
            for (int i = 0; i < n; ++i) pi[i] += dist[i];
            ll aug = LONGINF;
            for (int v = t; v != s; v = inc[v]->from)
                aug = min(aug, inc[v]->cap - inc[v]->flow);
            value += aug;
            for (int v = t; v != s; v = inc[v]->from)
                inc[v]->flow += aug, inc[v]->twin->flow -= aug;
        }
        ll cost = 0;
        for (auto& row : adj)
            for (auto e : row)
                cost += e->flow * e->cost;
        cost /= 2;
        return {value, cost};
    }
};
