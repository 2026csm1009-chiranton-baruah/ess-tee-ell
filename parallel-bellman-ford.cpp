
#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;
using Clock = chrono::steady_clock;

// ============================================================
// 1. CONFIGURATION
// ============================================================

constexpr uint32_t V = 10'000'000;
constexpr uint32_t K = 4;

constexpr long long INF = LLONG_MAX / 4;

constexpr bool INJECT_NEGATIVE_SELF_LOOP = false;
constexpr bool PRINT_ALL_DISTANCES = true;

constexpr int THREADS[] = {
    1, 2, 3, 4, 5, 6, 8, 9, 10, 12
};

constexpr int NUM_CONFIGS = 10;

// ============================================================
// 2. EDGE REPRESENTATION
// ============================================================

struct Edge {
    uint32_t src;
    int32_t weight;
};

// Incoming-edge representation:
// incoming[v*K + j] stores the j-th incoming edge of v.

vector<Edge> incoming;

// ============================================================
// 3. DETERMINISTIC RANDOM NUMBER GENERATOR
// ============================================================

uint64_t splitmix64(uint64_t x) {

    x += 0x9e3779b97f4a7c15ULL;

    x = (x ^ (x >> 30))
        * 0xbf58476d1ce4e5b9ULL;

    x = (x ^ (x >> 27))
        * 0x94d049bb133111ebULL;

    return x ^ (x >> 31);
}

// ============================================================
// 4. RANDOM DIRECTED GRAPH GENERATION
// ============================================================

void generateGraph() {

    incoming.resize((size_t)V * K);

    #pragma omp parallel for schedule(static)
    for (long long vv = 1; vv < V; vv++) {

        uint32_t v = (uint32_t)vv;

        for (uint32_t j = 0; j < K; j++) {

            uint64_t key =
                0x123456789ABCDEF0ULL ^
                ((uint64_t)v * K + j);

            // Ensure every edge points from a lower
            // numbered vertex to a higher numbered vertex.

            uint32_t src =
                (uint32_t)(splitmix64(key) % v);

            // Random edge weight in [-5, 20].

            int32_t weight =
                (int32_t)(
                    splitmix64(key ^ 0xABCDEFULL) % 26
                ) - 5;

            incoming[(size_t)v * K + j] = {
                src, weight
            };
        }
    }
}

// ============================================================
// 5. RESULT STRUCTURE
// ============================================================

struct Result {

    bool negative_cycle = false;

    uint64_t iterations = 0;

    double seconds = 0.0;
};

// ============================================================
// 6. PARALLEL BELLMAN-FORD
// ============================================================

Result bellmanFordOMP(
    vector<long long>& dist_old,
    vector<long long>& dist_new
) {

    Result result;

    // Shared reduction variables.
    int changed = 0;
    int cycle_found = 0;

    // Shared control variables.
    int stop = 0;
    int negative_cycle = 0;

    auto start = Clock::now();

    // Create one OpenMP team for the complete algorithm.

    #pragma omp parallel shared( \
        dist_old, dist_new, changed, cycle_found, \
        stop, negative_cycle, result)

    {

        // ====================================================
        // PHASE A: V-1 RELAXATION ITERATIONS
        // ====================================================

        for (uint64_t iter = 0;
             iter < (uint64_t)V - 1;
             iter++) {

            // Reset change flag.

            #pragma omp single
            {
                changed = 0;
            }

            // ------------------------------------------------
            // Parallel vertex relaxation.
            // Every thread processes different destination
            // vertices.
            // ------------------------------------------------

            #pragma omp for schedule(static) reduction(|:changed)

            for (long long vv = 0; vv < V; vv++) {

                uint32_t v = (uint32_t)vv;

                long long best = dist_old[v];

                // Optional negative self-loop at root.

                if constexpr (INJECT_NEGATIVE_SELF_LOOP) {

                    if (v == 0) {
                        best = min(best, dist_old[0] - 1);
                    }
                }

                // Root has no ordinary incoming edges.
                // Other vertices have exactly K incoming edges.

                if (v != 0) {

                    for (uint32_t j = 0; j < K; j++) {

                        const Edge& e =
                            incoming[(size_t)v * K + j];

                        long long source_dist =
                            dist_old[e.src];

                        if (source_dist != INF) {

                            long long candidate =
                                source_dist + e.weight;

                            if (candidate < best) {
                                best = candidate;
                            }
                        }
                    }
                }

                // Each thread writes to a distinct dist_new[v].

                dist_new[v] = best;

                if (best < dist_old[v]) {
                    changed = 1;
                }
            }

            // The implicit barrier above guarantees that
            // all distance updates have completed.

            // ------------------------------------------------
            // Swap arrays and check termination.
            // ------------------------------------------------

            #pragma omp single
            {

                dist_old.swap(dist_new);

                result.iterations++;

                if constexpr (INJECT_NEGATIVE_SELF_LOOP) {

                    if (dist_old[0] < 0) {
                        negative_cycle = 1;
                        stop = 1;
                    }
                }

                if (!changed) {
                    stop = 1;
                }
            }

            // The single construct has an implicit barrier.
            // All threads observe the same stop value.

            if (stop) {
                break;
            }
        }

        // ====================================================
        // PHASE B: NEGATIVE CYCLE DETECTION
        // ====================================================

        // Skip the general scan if a negative self-loop
        // has already been detected.

        if (!negative_cycle) {

            #pragma omp single
            {
                cycle_found = 0;
            }

            // ------------------------------------------------
            // Examine every ordinary edge in parallel.
            // ------------------------------------------------

            #pragma omp for schedule(static) reduction(|:cycle_found)

            for (long long vv = 1; vv < V; vv++) {

                uint32_t v = (uint32_t)vv;

                for (uint32_t j = 0; j < K; j++) {

                    const Edge& e =
                        incoming[(size_t)v * K + j];

                    if (dist_old[e.src] != INF &&
                        dist_old[e.src] + e.weight < dist_old[v]) {

                        cycle_found = 1;
                    }
                }
            }

            // Reduction is complete at the implicit barrier.

            #pragma omp single
            {
                negative_cycle = cycle_found;
            }
        }
    }

    auto end = Clock::now();

    result.seconds =
        chrono::duration<double>(end - start).count();

    result.negative_cycle = (negative_cycle != 0);

    return result;
}

// ============================================================
// 7. DISTANCE CHECKSUM
// ============================================================

uint64_t calculateChecksum(
    const vector<long long>& dist
) {

    uint64_t checksum = 0;

    for (uint32_t v = 0; v < V; v++) {

        if (dist[v] != INF) {

            checksum += (uint64_t)dist[v];
        }
    }

    return checksum;
}

// ============================================================
// 8. MAIN
// ============================================================

int main() {

    // Prevent OpenMP from changing the requested thread count.

    omp_set_dynamic(0);

    // --------------------------------------------------------
    // Generate graph once.
    // --------------------------------------------------------

    generateGraph();

    // Allocate distance arrays once.

    vector<long long> dist_old(V);
    vector<long long> dist_new(V);

    uint64_t reference_checksum = 0;

    bool have_reference = false;

    bool cycle_detected = false;

    Result final_result;

    // ========================================================
    // THREAD COUNT EXPERIMENTS
    // ========================================================

    for (int config = 0;
         config < NUM_CONFIGS;
         config++) {

        int threads = THREADS[config];

        omp_set_num_threads(threads);

        // Reset distances outside the timed region.

        fill(dist_old.begin(), dist_old.end(), INF);
        fill(dist_new.begin(), dist_new.end(), INF);

        // Source vertex.

        dist_old[0] = 0;

        // Execute parallel Bellman-Ford.

        Result result =
            bellmanFordOMP(dist_old, dist_new);

        // ----------------------------------------------------
        // Verify consistency between thread configurations.
        // ----------------------------------------------------

        if (!result.negative_cycle) {

            uint64_t checksum =
                calculateChecksum(dist_old);

            if (!have_reference) {

                reference_checksum = checksum;
                have_reference = true;

            } else if (checksum != reference_checksum) {

                cerr << "ERROR: Inconsistent SSSP results\n";

                return 1;
            }
        }

        // Timing output goes to stderr.

        cerr << "Threads = " << threads
             << " | Iterations = " << result.iterations
             << " | Time = " << result.seconds
             << " seconds\n";

        if (result.negative_cycle) {

            cycle_detected = true;
            break;
        }

        final_result = result;
    }

    // ========================================================
    // FINAL OUTPUT
    // ========================================================

    if (cycle_detected) {

        cout << "CYCLE\n";

        return 0;
    }

    cout << "SSSP\n";

    cout << "Reachable vertices: "
         << V << "/" << V << '\n';

    cout << "Distance checksum: "
         << reference_checksum << '\n';

    cout << "Final iteration count: "
         << final_result.iterations << '\n';

    if constexpr (PRINT_ALL_DISTANCES) {

        for (uint32_t v = 0; v < V; v++) {

            cout << v << " "
                 << dist_old[v] << '\n';
        }
    }

    return 0;
}
