/*
===============================================================================
PROBLEM: HackerRank - Prim's (MST): Special Subtree
TOPIC: Minimum Spanning Tree, Prim's Algorithm, Priority Queue
LANGUAGE: C++17
===============================================================================

WHAT THIS PROGRAM DOES
----------------------
Given a connected, undirected, weighted graph and a starting vertex, compute
the total weight of a minimum spanning tree (MST).

An MST connects every vertex using exactly V-1 edges, contains no cycle, and
has minimum possible total edge weight. The starting vertex affects the order
in which Prim's algorithm grows the tree, but not the minimum total cost.

INPUT FORMAT (HackerRank)
------------------------
V E
u1 v1 w1
u2 v2 w2
...
uE vE wE
S

- V: number of vertices, numbered 1 through V.
- E: number of undirected edges.
- ui, vi: endpoints of an edge.
- wi: edge weight.
- S: starting vertex for Prim's algorithm.

OUTPUT
------
Print one integer: the total weight of the MST.

SAMPLE INPUT
------------
5 6
1 2 3
1 3 4
4 2 6
5 2 2
2 3 5
3 5 7
1

SAMPLE OUTPUT
-------------
15

SAMPLE EXPLANATION
------------------
One valid MST contains:
(2,5) with weight 2
(1,2) with weight 3
(1,3) with weight 4
(2,4) with weight 6
Total = 2 + 3 + 4 + 6 = 15.

ALGORITHM
---------
1. Store the graph as an adjacency list.
2. Push (0, start) into a min-priority queue.
3. Repeatedly extract the cheapest edge candidate.
4. If its vertex is already visited, ignore it.
5. Otherwise, mark it visited, add its weight to the answer, and push all
   outgoing edges leading to unvisited vertices.
6. Stop after all V vertices have been selected.

COMPLEXITY
----------
Time:  O((V + E) log E), commonly expressed as O(E log V) for connected graphs.
Space: O(V + E).

NOTES
-----
- This implementation assumes the graph is connected, as in the standard
  HackerRank problem.
- Parallel edges are safe: the priority queue naturally considers each.
- For a disconnected graph, Prim's algorithm started from S only visits the
  component containing S; this program detects that and prints -1.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, long long>>> adj(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int start;
    cin >> start;

    using State = pair<long long, int>; // {edge weight, vertex}
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<bool> visited(V + 1, false);

    pq.push({0, start});
    long long totalCost = 0;
    int selectedVertices = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        totalCost += weight;
        ++selectedVertices;

        for (auto [v, w] : adj[u]) {
            if (!visited[v]) pq.push({w, v});
        }
    }

    cout << (selectedVertices == V ? totalCost : -1) << '\n';
    return 0;
}
