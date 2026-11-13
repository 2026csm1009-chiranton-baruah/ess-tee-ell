/*
===============================================================================
PROBLEM: HackerRank - Kruskal (MST): Really Special Subtree
TOPIC: Minimum Spanning Tree, Kruskal's Algorithm, Disjoint Set Union (DSU)
LANGUAGE: C++17
===============================================================================

WHAT THIS PROGRAM DOES
----------------------
Finds the minimum total weight needed to connect all vertices of a connected,
undirected, weighted graph.

Kruskal's algorithm sorts edges by non-decreasing weight and accepts an edge
only when its endpoints currently belong to different connected components.
DSU efficiently tracks those components and prevents cycles.

INPUT FORMAT
------------
V E
u1 v1 w1
u2 v2 w2
...
uE vE wE

Vertices are numbered 1 through V. Each edge is undirected.

OUTPUT
------
Print the MST's total weight. This implementation prints -1 if the graph is
disconnected (the original HackerRank problem guarantees a connected graph).

SAMPLE INPUT
------------
4 5
1 2 1
2 3 2
3 4 3
1 4 10
1 3 4

SAMPLE OUTPUT
-------------
6

SAMPLE EXPLANATION
------------------
Kruskal selects edges of weights 1, 2, and 3. They connect all four vertices
without a cycle, so the MST cost is 1 + 2 + 3 = 6.

ALGORITHM
---------
1. Sort all edges by weight.
2. Initialise each vertex as a separate DSU component.
3. For each edge (u,v,w) in sorted order:
   - Find the representative of u and v.
   - If they differ, union the components and add w to the answer.
   - Otherwise, skip the edge because it would create a cycle.
4. Stop after selecting V-1 edges.

COMPLEXITY
----------
Sorting: O(E log E)
DSU:     O(E alpha(V)) amortised
Total:   O(E log E)
Space:   O(V + E)

NOTES
-----
- The total MST weight is unaffected by how equal-weight edges are ordered.
- If the problem asks for a particular MST edge set under a tie-breaking rule,
  include that exact tie-break in the comparator.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    DSU dsu(V);
    long long totalCost = 0;
    int selectedEdges = 0;

    for (const auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalCost += e.w;
            ++selectedEdges;
            if (selectedEdges == V - 1) break;
        }
    }

    cout << (selectedEdges == V - 1 ? totalCost : -1) << '\n';
    return 0;
}
