/*
===============================================================================
PROBLEM: LeetCode 1631 - Path With Minimum Effort
TOPIC: Minimum Bottleneck Path, Kruskal + DSU
LANGUAGE: C++17 (LeetCode class format)
===============================================================================

WHAT THIS SOLUTION DOES
-----------------------
Given a matrix of heights, move from the top-left cell to the bottom-right
cell. You may move up, down, left, or right. The effort of a path is the
maximum absolute height difference between any two consecutive cells.
Return the minimum possible effort.

This solution models each neighbouring pair of cells as an undirected edge
whose weight is their absolute height difference. Kruskal processes edges in
increasing order. The first moment when source and destination become
connected gives the minimum possible bottleneck value.

LEETCODE INPUT
-------------
The judge supplies:
    vector<vector<int>> heights

OUTPUT
------
Return one integer: the minimum possible path effort.

SAMPLE INPUT
------------
heights = [
  [1,2,2],
  [3,8,2],
  [5,3,5]
]

SAMPLE OUTPUT
-------------
2

SAMPLE EXPLANATION
------------------
A path exists from the top-left to the bottom-right whose largest adjacent
height difference is 2. No path can achieve a smaller maximum difference.

ALGORITHM
---------
1. Give each cell a unique ID: id = row * columns + column.
2. Generate edges to the cell below and to the right (this creates every
   undirected grid adjacency exactly once).
3. Edge weight = absolute difference of the two cell heights.
4. Sort all edges by weight.
5. Process them with DSU.
6. As soon as the source and destination share a DSU component, return the
   current edge weight.

WHY STOPPING WORKS
------------------
After processing all edges of weight <= X, DSU components represent exactly
the cells connected using only edges of weight <= X. The first X for which
source and destination become connected is therefore the smallest possible
maximum edge weight on any connecting path.

COMPLEXITY
----------
For R rows and C columns:
Number of vertices V = R*C.
Number of edges E is at most about 2*R*C.
Time:  O(E log E)
Space: O(V + E)

ALTERNATIVE
-----------
A modified Dijkstra solution is also possible, where the relaxation is:
newEffort = max(currentEffort, edgeWeight).
This file intentionally demonstrates the Kruskal/DSU formulation.
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

        bool connected(int a, int b) {
            return find(a) == find(b);
        }
    };

    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = (int)heights.size();
        int cols = (int)heights[0].size();

        if (rows == 1 && cols == 1) return 0;

        auto id = [cols](int r, int c) {
            return r * cols + c;
        };

        vector<Edge> edges;
        edges.reserve(rows * cols * 2);

        const int dr[2] = {1, 0};
        const int dc[2] = {0, 1};

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (int k = 0; k < 2; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < rows && nc < cols) {
                        int w = abs(heights[r][c] - heights[nr][nc]);
                        edges.push_back({id(r, c), id(nr, nc), w});
                    }
                }
            }
        }

        sort(edges.begin(), edges.end());

        int source = 0;
        int destination = rows * cols - 1;
        DSU dsu(rows * cols);

        for (const Edge& e : edges) {
            dsu.unite(e.u, e.v);
            if (dsu.connected(source, destination)) {
                return e.w;
            }
        }

        return 0; // A rectangular grid is always connected.
    }
};

/*
LOCAL TEST EXPECTATION
---------------------
heights = {{1,2,2},{3,8,2},{5,3,5}}
minimumEffortPath(...) returns 2.

heights = {{1,2,3},{3,8,4},{5,3,5}}
minimumEffortPath(...) returns 1.
*/
