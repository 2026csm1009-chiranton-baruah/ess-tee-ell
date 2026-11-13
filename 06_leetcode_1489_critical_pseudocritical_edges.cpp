/*
===============================================================================
PROBLEM: LeetCode 1489 - Find Critical and Pseudo-Critical Edges in MST
TOPIC: Kruskal, DSU, Edge Classification, MST Uniqueness
LANGUAGE: C++17 (LeetCode class format)
===============================================================================

WHAT THIS SOLUTION DOES
-----------------------
Classifies each edge of a connected, weighted, undirected graph:

CRITICAL EDGE:
An edge that appears in every possible minimum spanning tree. If it is
excluded, the best spanning tree becomes more expensive or no spanning tree
can be formed.

PSEUDO-CRITICAL EDGE:
An edge that appears in at least one MST, but is not required in every MST.
It can be included in some MST without increasing the optimum cost.

LEETCODE INPUT
-------------
The judge supplies:
    int n
    vector<vector<int>> edges

Each edge is [u,v,weight]. The original edge index is retained so the output
can refer to the input ordering.

OUTPUT
------
Return a vector containing two lists:
    answer[0] = indices of critical edges
    answer[1] = indices of pseudo-critical edges

SAMPLE INPUT
------------
n = 5
edges = [
  [0,1,1],
  [1,2,1],
  [2,3,2],
  [0,3,2],
  [0,4,3],
  [3,4,3],
  [1,4,6]
]

SAMPLE OUTPUT
-------------
[[0,1],[2,3,4,5]]

SAMPLE EXPLANATION
------------------
Edges 0 and 1 are required in every MST. Edges 2, 3, 4, and 5 can each occur
in at least one MST of the same minimum total cost. Edge 6 occurs in no MST.

ALGORITHM
---------
1. Compute the original MST weight W using Kruskal.
2. For every edge e:
   A. Exclude e and recompute the MST.
      If the graph disconnects or its cost exceeds W, e is critical.
   B. Otherwise, force e into the MST, then run Kruskal on other edges.
      If the resulting spanning tree has cost W, e is pseudo-critical.
3. Return the two index lists.

COMPLEXITY
----------
This straightforward and interview-friendly solution runs Kruskal O(E) times.
Time: O(E^2 alpha(V) + E log E), often simplified to O(E^2 alpha(V)).
Space: O(V + E), excluding copies made by the judge.

IMPLEMENTATION DETAIL
---------------------
The forced-edge run first unions the endpoints of e and starts the total cost
at e's weight. The excluded-edge run skips e entirely. Edge IDs make these
tests unambiguous even when multiple edges have identical endpoints/weights.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct DSU {
        vector<int> parent, sz;

        explicit DSU(int n) : parent(n), sz(n, 1) {
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
        int u, v, w, id;
    };

    struct MSTResult {
        long long cost;
        int used;
    };

    MSTResult kruskal(int n, const vector<Edge>& edges,
                      int skipId = -1, int forceId = -1) {
        DSU dsu(n);
        long long cost = 0;
        int used = 0;

        // If forceId is supplied, include that edge before processing others.
        if (forceId != -1) {
            const Edge& forced = edges[forceId];
            dsu.unite(forced.u, forced.v);
            cost += forced.w;
            ++used;
        }

        for (const Edge& e : edges) {
            if (e.id == skipId || e.id == forceId) continue;

            if (dsu.unite(e.u, e.v)) {
                cost += e.w;
                ++used;
                if (used == n - 1) break;
            }
        }

        return {cost, used};
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n, vector<vector<int>>& inputEdges) {

        vector<Edge> edges;
        edges.reserve(inputEdges.size());

        for (int i = 0; i < (int)inputEdges.size(); ++i) {
            edges.push_back({
                inputEdges[i][0], inputEdges[i][1],
                inputEdges[i][2], i
            });
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            if (a.w != b.w) return a.w < b.w;
            return a.id < b.id;
        });

        // Re-index by original ID so forceId can access edges[id] directly.
        vector<Edge> byId(edges.size());
        for (const Edge& e : edges) byId[e.id] = e;

        MSTResult baseline = kruskal(n, edges);
        long long best = baseline.cost;

        vector<int> critical, pseudo;

        for (int id = 0; id < (int)byId.size(); ++id) {
            MSTResult without = kruskal(n, edges, id, -1);

            if (without.used != n - 1 || without.cost > best) {
                critical.push_back(id);
                continue;
            }

            MSTResult with = kruskal(n, edges, -1, id);
            if (with.used == n - 1 && with.cost == best) {
                pseudo.push_back(id);
            }
        }

        return {critical, pseudo};
    }
};

/*
LOCAL TEST EXPECTATION
---------------------
Input described in the sample should return:
critical = {0,1}
pseudo-critical = {2,3,4,5}

LeetCode accepts the vector<vector<int>> result directly.
*/
