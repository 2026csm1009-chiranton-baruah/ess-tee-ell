/*
===============================================================================
PROBLEM: HackerRank - Roads and Libraries
TOPIC: Connected Components, DSU, Minimum Spanning Forest
LANGUAGE: C++17
===============================================================================

WHAT THIS PROGRAM DOES
----------------------
There are n cities and some possible roads. A library must be accessible to
every city. A library can be built in any city for cost c_lib; a road can be
built between a listed pair of cities for cost c_road.

Find the minimum total cost to ensure every city can access a library.

IMPORTANT OBSERVATION
---------------------
If c_lib <= c_road, building a library in every city is never more expensive
than using roads to share library access.

Otherwise, in every connected component of the available-road graph:
- Build exactly one library.
- Build a spanning tree connecting the other cities in that component.

If there are C connected components, the answer is:
    C * c_lib + (n - C) * c_road

This is a minimum spanning forest / connected-components application. Since
all roads have the same construction cost, choosing any spanning tree in each
component is optimal.

INPUT FORMAT (HackerRank)
------------------------
q
n m c_lib c_road
u1 v1
u2 v2
...
um vm
(repeat for each test case)

- q: number of test cases.
- n: number of cities.
- m: number of available roads.
- c_lib: cost of building one library.
- c_road: cost of building one road.
- Cities are numbered 1 through n.

OUTPUT
------
For each test case, print the minimum total cost on its own line.

SAMPLE INPUT
------------
2
3 3 2 1
1 2
3 1
2 3
6 6 2 5
1 3
3 4
2 4
1 2
2 3
5 6

SAMPLE OUTPUT
-------------
4
12

SAMPLE EXPLANATION
------------------
Test 1: One connected component. Build one library and two roads:
2 + 1 + 1 = 4.
Test 2: Roads cost more than libraries, so build six libraries:
6 * 2 = 12.

COMPLEXITY
----------
Time:  O((n + m) alpha(n)) per test case.
Space: O(n).
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--) {
        int n, m;
        long long c_lib, c_road;
        cin >> n >> m >> c_lib >> c_road;

        DSU dsu(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        }

        if (c_lib <= c_road) {
            cout << (long long)n * c_lib << '\n';
            continue;
        }

        int components = 0;
        for (int city = 1; city <= n; ++city) {
            if (dsu.find(city) == city) ++components;
        }

        long long answer =
            (long long)components * c_lib +
            (long long)(n - components) * c_road;

        cout << answer << '\n';
    }

    return 0;
}
