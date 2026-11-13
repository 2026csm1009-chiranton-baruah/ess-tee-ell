/*
===============================================================================
PROBLEM: LeetCode 1168 - Optimize Water Distribution in a Village
TOPIC: MST, Kruskal's Algorithm, Virtual Vertex, DSU
LANGUAGE: C++17 (LeetCode class format)
===============================================================================

WHAT THIS SOLUTION DOES
-----------------------
There are n houses. Each house i can receive water by:
1. Building a well at house i, costing wells[i-1].
2. Connecting it through a pipe to another house.

The pipes input contains [house1, house2, cost]. Find the minimum total cost
so every house has access to water.

KEY GRAPH TRANSFORMATION: VIRTUAL VERTEX
----------------------------------------
Create an additional vertex 0 representing the water source.
For every house i, add an edge (0,i) with weight wells[i-1].
Each possible pipe is an ordinary edge between two house vertices.

An MST of this augmented graph chooses the cheapest combination of wells and
pipes that connects all houses to the virtual source.

LEETCODE INPUT
-------------
The judge supplies:
    int n
    vector<int> wells
    vector<vector<int>> pipes

- wells[i-1] is the cost of building a well at house i.
- Each pipes entry is [house1, house2, cost].
- House labels are 1 through n.

OUTPUT
------
Return the minimum total cost.

SAMPLE INPUT
------------
n = 3
wells = [1,2,2]
pipes = [[1,2,1],[2,3,1]]

SAMPLE OUTPUT
-------------
3

SAMPLE EXPLANATION
------------------
Build a well at house 1 for cost 1, then connect house 2 to 1 for cost 1,
and house 3 to 2 for cost 1. Total = 3.

ALGORITHM
---------
1. Add virtual-source edges (0,i,wells[i-1]).
2. Append all pipe edges.
3. Sort all edges by cost.
4. Run Kruskal on vertices 0 through n.
5. Stop after n successful unions (an MST on n+1 vertices has n edges).

COMPLEXITY
----------
Let P be the number of possible pipes.
Time:  O((n+P) log(n+P))
Space: O(n+P)

WHY THE VIRTUAL NODE WORKS
--------------------------
Every connected solution must connect every house to the source of water.
The virtual node models the option of independently building a well, so
ordinary MST machinery can choose wells and pipes in one optimisation.
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
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };

public:
    int minCostToSupplyWater(int n, vector<int>& wells,
                             vector<vector<int>>& pipes) {
        vector<Edge> edges;
        edges.reserve(n + pipes.size());

        for (int i = 1; i <= n; ++i) {
            edges.push_back({0, i, wells[i - 1]});
        }

        for (const auto& p : pipes) {
            edges.push_back({p[0], p[1], p[2]});
        }

        sort(edges.begin(), edges.end());

        DSU dsu(n + 1); // vertices 0,1,...,n
        long long total = 0;
        int used = 0;

        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total += e.w;
                ++used;
                if (used == n) break;
            }
        }

        return (int)total;
    }
};

/*
LOCAL TEST EXPECTATION
---------------------
n = 3
wells = {1,2,2}
pipes = {{1,2,1},{2,3,1}}
minCostToSupplyWater(...) returns 3.
*/
