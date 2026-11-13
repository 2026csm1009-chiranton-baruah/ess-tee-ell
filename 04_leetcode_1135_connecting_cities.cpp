/*
===============================================================================
PROBLEM: LeetCode 1135 - Connecting Cities With Minimum Cost
TOPIC: Kruskal's Algorithm, DSU, Disconnected Graph Detection
LANGUAGE: C++17 (LeetCode class format)
===============================================================================

WHAT THIS SOLUTION DOES
-----------------------
There are n cities and connections. Each connection [a,b,cost] is an
undirected edge that can connect cities a and b at the given cost.
Return the minimum cost to connect every city. If this is impossible, return
-1.

LEETCODE INPUT
-------------
The judge supplies:
    int n
    vector<vector<int>> connections

Each connection is [city1, city2, cost]. Cities are numbered 1 through n.

OUTPUT
------
Return the minimum total cost, or -1 if the graph is disconnected.

SAMPLE INPUT
------------
n = 3
connections = [[1,2,5],[1,3,6],[2,3,1]]

SAMPLE OUTPUT
-------------
6

SAMPLE EXPLANATION
------------------
Choose city 2--3 for cost 1 and city 1--2 for cost 5. Total = 6.

ALGORITHM
---------
Sort all connections by cost and use DSU to add only edges that join
different components. A connected graph on n vertices requires n-1 accepted
edges. If fewer than n-1 edges are accepted, no spanning tree exists.

COMPLEXITY
----------
Time:  O(E log E)
Space: O(n) auxiliary, excluding the input and sorting storage.

IMPORTANT EDGE CASES
--------------------
- n = 1: answer is 0.
- Disconnected graph: answer is -1.
- Cycles and duplicate/parallel connections are handled by DSU.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
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

public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        sort(connections.begin(), connections.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        DSU dsu(n);
        long long total = 0;
        int used = 0;

        for (const auto& edge : connections) {
            if (dsu.unite(edge[0], edge[1])) {
                total += edge[2];
                ++used;
                if (used == n - 1) break;
            }
        }

        return (used == n - 1) ? (int)total : -1;
    }
};

/*
LOCAL TEST EXPECTATION
---------------------
n = 3, connections = {{1,2,5},{1,3,6},{2,3,1}}
minimumCost(...) returns 6.
*/
