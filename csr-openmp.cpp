
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <omp.h>
#include <iomanip>

using namespace std;

// -----------------------------------------
// Serial CSR conversion
// -----------------------------------------

void serialCSR(
    const vector<vector<int>>& adj,
    vector<int>& degree,
    vector<int>& row_ptr,
    vector<int>& col_idx,
    int V
) {

    // Step 1: Calculate degrees
    for (int i = 0; i < V; i++) {
        degree[i] = adj[i].size();
    }

    // Step 2: Calculate prefix sum
    row_ptr[0] = 0;

    for (int i = 0; i < V; i++) {
        row_ptr[i + 1] = row_ptr[i] + degree[i];
    }

    // Step 3: Populate column indices
    for (int i = 0; i < V; i++) {

        for (int j = 0; j < degree[i]; j++) {
            col_idx[row_ptr[i] + j] = adj[i][j];
        }
    }
}

// -----------------------------------------
// Parallel CSR conversion using OpenMP
// -----------------------------------------

void parallelCSR(
    const vector<vector<int>>& adj,
    vector<int>& degree,
    vector<int>& row_ptr,
    vector<int>& col_idx,
    int V
) {

    // Step 1: Parallel degree calculation
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < V; i++) {
        degree[i] = adj[i].size();
    }

    // Step 2: Prefix sum (sequential)
    row_ptr[0] = 0;

    for (int i = 0; i < V; i++) {
        row_ptr[i + 1] = row_ptr[i] + degree[i];
    }

    // Step 3: Parallel column index population
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < V; i++) {

        for (int j = 0; j < degree[i]; j++) {
            col_idx[row_ptr[i] + j] = adj[i][j];
        }
    }
}

// -----------------------------------------
// Main function
// -----------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 4) {
        cerr << "Usage: ./csr_compare input.txt output.txt [threads]\n";
        return 1;
    }

    // Configure OpenMP
    omp_set_dynamic(0);

    if (argc == 4) {
        int threads = stoi(argv[3]);

        if (threads <= 0) {
            cerr << "Invalid thread count.\n";
            return 1;
        }

        omp_set_num_threads(threads);
    }

    // -------------------------------------
    // Read input graph
    // -------------------------------------

    ifstream fin(argv[1]);

    if (!fin) {
        cerr << "Cannot open input file.\n";
        return 1;
    }

    int V, E;
    fin >> V >> E;

    if (!fin || V <= 0 || E < 0) {
        cerr << "Invalid graph header.\n";
        return 1;
    }

    string line;
    getline(fin, line);

    vector<vector<int>> adj(V);
    vector<bool> seen(V, false);

    for (int i = 0; i < V; i++) {

        if (!getline(fin, line)) {
            cerr << "Incomplete adjacency list.\n";
            return 1;
        }

        stringstream ss(line);

        int u;

        if (!(ss >> u) || u < 0 || u >= V || seen[u]) {
            cerr << "Invalid vertex entry.\n";
            return 1;
        }

        seen[u] = true;

        int v;

        while (ss >> v) {

            if (v < 0 || v >= V) {
                cerr << "Invalid adjacent vertex.\n";
                return 1;
            }

            adj[u].push_back(v);
        }
    }

    for (int i = 0; i < V; i++) {
        if (!seen[i]) {
            cerr << "Missing vertex " << i << "\n";
            return 1;
        }
    }

    // Total adjacency entries
    int M = 0;

    for (int i = 0; i < V; i++) {
        M += adj[i].size();
    }

    // -------------------------------------
    // Allocate CSR arrays
    // -------------------------------------

    vector<int> degree_serial(V);
    vector<int> row_serial(V + 1);
    vector<int> col_serial(M);

    vector<int> degree_parallel(V);
    vector<int> row_parallel(V + 1);
    vector<int> col_parallel(M);

    // -------------------------------------
    // Serial execution
    // -------------------------------------

    double serial_start = omp_get_wtime();

    serialCSR(
        adj,
        degree_serial,
        row_serial,
        col_serial,
        V
    );

    double serial_end = omp_get_wtime();

    double serial_time = serial_end - serial_start;

    // -------------------------------------
    // Parallel execution
    // -------------------------------------

    double parallel_start = omp_get_wtime();

    parallelCSR(
        adj,
        degree_parallel,
        row_parallel,
        col_parallel,
        V
    );

    double parallel_end = omp_get_wtime();

    double parallel_time = parallel_end - parallel_start;

    // -------------------------------------
    // Verify CSR correctness
    // -------------------------------------

    bool correct =
        (row_serial == row_parallel) &&
        (col_serial == col_parallel) &&
        (degree_serial == degree_parallel);

    // -------------------------------------
    // Performance comparison
    // -------------------------------------

    cout << fixed << setprecision(6);

    cout << "\n========== CSR CONVERSION RESULTS ==========\n";

    cout << "Vertices             : " << V << "\n";
    cout << "Input edges          : " << E << "\n";
    cout << "Adjacency entries    : " << M << "\n";
    cout << "OpenMP threads       : " << omp_get_max_threads() << "\n";

    cout << "\n------------ EXECUTION TIME ---------------\n";

    cout << "Serial time          : "
         << serial_time << " seconds\n";

    cout << "Parallel time        : "
         << parallel_time << " seconds\n";

    cout << "\n------------ PERFORMANCE ------------------\n";

    double speedup = serial_time / parallel_time;

    double efficiency = speedup / omp_get_max_threads();

    cout << "Speedup              : "
         << speedup << "x\n";

    cout << "Parallel efficiency  : "
         << efficiency * 100 << "%\n";

    cout << "\n------------ CORRECTNESS ------------------\n";

    if (correct) {
        cout << "CSR verification    : PASSED\n";
    } else {
        cout << "CSR verification    : FAILED\n";
        return 1;
    }

    // -------------------------------------
    // Write CSR output
    // -------------------------------------

    ofstream fout(argv[2]);

    if (!fout) {
        cerr << "Cannot create output file.\n";
        return 1;
    }

    fout << V << " " << E << "\n";

    fout << "row_ptr:\n";

    for (int i = 0; i <= V; i++) {
        fout << row_parallel[i] << " ";
    }

    fout << "\ncol_idx:\n";

    for (int i = 0; i < M; i++) {
        fout << col_parallel[i] << " ";
    }

    fout << "\n";

    fout.close();

    cout << "\nCSR output saved to: " << argv[2] << "\n";

    cout << "============================================\n";

    return 0;
}
