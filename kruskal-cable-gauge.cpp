#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long g;
    
    // Sort edges by gauge in ascending order
    bool operator<(const Edge& other) const {
        return g < other.g;
    }
};

struct DSU {
    vector<int> parent;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
        components = n;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].g;
    }

    // Step 1: Sort edges by gauge limit
    sort(edges.begin(), edges.end());

    // Step 2: Add edges dynamically using DSU
    DSU dsu(n);
    long long min_G = -1;

    for (const auto& edge : edges) {
        dsu.unite(edge.u, edge.v);
        
        // As soon as all nodes belong to 1 connected component
        if (dsu.components == 1) {
            min_G = edge.g;
            break;
        }
    }

    // Step 3: Print result
    cout << min_G << "\n";

    return 0;
}
