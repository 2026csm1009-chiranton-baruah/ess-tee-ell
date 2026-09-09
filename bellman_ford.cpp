#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

struct Edge {
    int u, v, wt;
};

bool bellmanFord(int V, int E, vector<Edge> &edges, int src) {
    vector<int> dist(V, INF);

    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        bool changed = false;

        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int wt = edge.wt;

            if (dist[u] != INF &&
                dist[u] + wt < dist[v]) {

                dist[v] = dist[u] + wt;
                changed = true;
            }
        }

        // Optimization: stop if nothing changed
        if (!changed)
            break;
    }

    // Check for negative-weight cycle
    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int wt = edge.wt;

        if (dist[u] != INF &&
            dist[u] + wt < dist[v]) {

            cout << "Negative weight cycle detected!\n";
            return false;
        }
    }

    cout << "Shortest distances from " << src << ":\n";

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            cout << i << " : INF\n";
        else
            cout << i << " : " << dist[i] << "\n";
    }

    return true;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);

    for (int i = 0; i < E; i++) {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].wt;
    }

    int src;
    cin >> src;

    bellmanFord(V, E, edges, src);

    return 0;
}
