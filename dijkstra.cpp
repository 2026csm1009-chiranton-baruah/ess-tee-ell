#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void dijkstra(int V, vector<vector<pair<int, int>>> &adj, int src) {
    vector<int> dist(V, INF);

    // {distance, vertex}
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Ignore outdated entry
        if (d != dist[u])
            continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int wt = edge.second;

            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from " << src << ":\n";

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            cout << i << " : INF\n";
        else
            cout << i << " : " << dist[i] << "\n";
    }
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});

        // Uncomment for undirected graph
        // adj[v].push_back({u, w});
    }

    int src;
    cin >> src;

    dijkstra(V, adj, src);

    return 0;
}
