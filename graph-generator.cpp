
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <unordered_set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 5) {
        cerr << "Usage: ./graph_generator <vertices> <edges> "
             << "<directed: 0/1> <output_file>\n";
        return 1;
    }

    int V = stoi(argv[1]);
    int E = stoi(argv[2]);
    bool directed = (stoi(argv[3]) != 0);
    string filename = argv[4];

    if (V <= 0 || E < 0) {
        cerr << "Invalid graph dimensions.\n";
        return 1;
    }

    // Maximum possible edges without self-loops
    long long max_edges = directed
        ? 1LL * V * (V - 1)
        : 1LL * V * (V - 1) / 2;

    if (E > max_edges) {
        cerr << "Too many edges for the given number of vertices.\n";
        return 1;
    }

    // Random number generator
    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> vertex_dist(0, V - 1);

    // Adjacency list
    vector<vector<int>> adj(V);

    // Track edges to prevent duplicates
    unordered_set<unsigned long long> edge_set;

    auto edge_key = [V](int u, int v) {
        return 1ULL * u * V + v;
    };

    // Generate random edges
    while (static_cast<long long>(edge_set.size()) < E) {

        int u = vertex_dist(rng);
        int v = vertex_dist(rng);

        // No self-loops
        if (u == v)
            continue;

        // Normalize undirected edges
        if (!directed && u > v)
            swap(u, v);

        unsigned long long key = edge_key(u, v);

        // Ignore duplicate edges
        if (edge_set.insert(key).second) {

            adj[u].push_back(v);

            // Add reverse edge for undirected graphs
            if (!directed) {
                adj[v].push_back(u);
            }
        }
    }

    // Write graph to file
    ofstream fout(filename);

    if (!fout) {
        cerr << "Unable to create output file.\n";
        return 1;
    }

    fout << V << " " << E << "\n";

    for (int i = 0; i < V; i++) {

        fout << i;

        for (int neighbor : adj[i]) {
            fout << " " << neighbor;
        }

        fout << "\n";
    }

    fout.close();

    cout << "Graph generated successfully!\n";
    cout << "Vertices: " << V << "\n";
    cout << "Edges: " << E << "\n";
    cout << "Graph type: "
         << (directed ? "Directed" : "Undirected") << "\n";
    cout << "Output file: " << filename << "\n";

    return 0;
}
