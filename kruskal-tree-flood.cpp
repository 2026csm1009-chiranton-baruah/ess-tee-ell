#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long h;
    bool operator<(const Edge& other) const {
        return h < other.h;
    }
};

// DSU Structure
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

const int MAXLOG = 20;
vector<vector<int>> adj;
vector<long long> node_val;
vector<vector<int>> up;
vector<int> depth;

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < MAXLOG; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    for (int i = MAXLOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    
    if (u == v) return u;
    
    for (int i = MAXLOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].h;
    }

    sort(edges.begin(), edges.end());

    int total_nodes = n;
    int max_possible_nodes = 2 * n + 5;
    
    adj.resize(max_possible_nodes);
    node_val.resize(max_possible_nodes, 0);
    
    DSU dsu(max_possible_nodes);

    for (const auto& edge : edges) {
        int root_u = dsu.find(edge.u);
        int root_v = dsu.find(edge.v);
        
        if (root_u != root_v) {
            total_nodes++;
            node_val[total_nodes] = edge.h;
            
            adj[total_nodes].push_back(root_u);
            adj[root_u].push_back(total_nodes);
            
            adj[total_nodes].push_back(root_v);
            adj[root_v].push_back(total_nodes);
            
            dsu.parent[root_u] = total_nodes;
            dsu.parent[root_v] = total_nodes;
            dsu.parent[total_nodes] = total_nodes;
        }
    }

    depth.resize(total_nodes + 1, 0);
    up.assign(total_nodes + 1, vector<int>(MAXLOG, 0));

    // DFS to set up LCA binary lifting for all tree components
    for (int i = 1; i <= total_nodes; ++i) {
        if (dsu.find(i) == i && depth[i] == 0) {
            dfs(i, i);
        }
    }

    // Process Queries
    while (q--) {
        int u, v;
        cin >> u >> v;

        if (u == v) {
            cout << 0 << "\n";
        } else if (dsu.find(u) != dsu.find(v)) {
            cout << -1 << "\n";
        } else {
            int lca = get_lca(u, v);
            cout << node_val[lca] << "\n";
        }
    }

    return 0;
}
