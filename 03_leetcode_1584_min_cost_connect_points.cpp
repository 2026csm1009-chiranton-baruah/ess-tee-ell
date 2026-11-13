/*
===============================================================================
PROBLEM: LeetCode 1584 - Min Cost to Connect All Points
TOPIC: MST on an Implicit Complete Graph, Prim's Algorithm
LANGUAGE: C++17 (LeetCode class format)
===============================================================================

WHAT THIS SOLUTION DOES
-----------------------
Given n points in a 2D plane, connect every point so that the total cost is
minimum. The cost of connecting points i and j is their Manhattan distance:

    distance(i,j) = abs(x[i] - x[j]) + abs(y[i] - y[j])

Every pair of points can be connected, so the underlying graph is complete.
Explicitly generating all O(n^2) edges and sorting them is unnecessary.
This solution uses Prim's algorithm with an array of best known connection
costs, giving O(n^2) time and O(n) auxiliary space.

LEETCODE INPUT
-------------
The judge supplies:
    vector<vector<int>> points

Each element points[i] is [xi, yi]. No stdin parsing is needed on LeetCode.

OUTPUT
------
Return an integer: the minimum total connection cost.

SAMPLE INPUT
------------
points = [[0,0],[2,2],[3,10],[5,2],[7,0]]

SAMPLE OUTPUT
-------------
20

SAMPLE EXPLANATION
------------------
One MST can use edges with Manhattan distances 4, 3, 4, and 9, totalling 20.

ALGORITHM
---------
1. Start Prim's algorithm from point 0.
2. minDist[i] stores the cheapest edge currently known from the selected
   tree to unselected point i.
3. Repeatedly select the unvisited point with minimum minDist.
4. Add that distance to the answer.
5. Update minDist for every remaining point using Manhattan distance.
6. Repeat until all points have been selected.

COMPLEXITY
----------
Time:  O(n^2)
Space: O(n)

WHY THIS IS USEFUL
------------------
This is a standard pattern for dense or implicit graphs: compute edge weights
when needed rather than storing every possible edge.
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = (int)points.size();
        if (n <= 1) return 0;

        const int INF = INT_MAX;
        vector<int> minDist(n, INF);
        vector<bool> used(n, false);

        minDist[0] = 0;
        long long total = 0;

        for (int step = 0; step < n; ++step) {
            int u = -1;

            // Find the cheapest point not yet included in the MST.
            for (int i = 0; i < n; ++i) {
                if (!used[i] && (u == -1 || minDist[i] < minDist[u])) {
                    u = i;
                }
            }

            used[u] = true;
            total += minDist[u];

            // Relax the implicit edges from the newly selected point.
            for (int v = 0; v < n; ++v) {
                if (used[v]) continue;

                int distance =
                    abs(points[u][0] - points[v][0]) +
                    abs(points[u][1] - points[v][1]);

                minDist[v] = min(minDist[v], distance);
            }
        }

        return (int)total;
    }
};

/*
LOCAL TEST HARNESS (optional)
-----------------------------
LeetCode does not require main(). To test locally, uncomment or adapt:

int main() {
    Solution s;
    vector<vector<int>> p = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << s.minCostConnectPoints(p) << '\n'; // Expected: 20
}
*/
