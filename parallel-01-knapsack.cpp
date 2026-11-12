
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

int knapsackParallel(
    const vector<int>& weight,
    const vector<int>& value,
    int n,
    int W
) {
    vector<vector<int>> dp(
        n + 1,
        vector<int>(W + 1, 0)
    );

    for (int i = 1; i <= n; i++) {

        #pragma omp parallel for schedule(static)
        for (int j = 0; j <= W; j++) {

            if (weight[i - 1] <= j) {
                dp[i][j] = max(
                    dp[i - 1][j],
                    value[i - 1] +
                    dp[i - 1][j - weight[i - 1]]
                );
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;

    cout << "Number of items: ";
    cin >> n;

    cout << "Knapsack capacity: ";
    cin >> W;

    vector<int> weight(n), value(n);

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++)
        cin >> value[i];

    omp_set_num_threads(omp_get_max_threads());

    auto start = high_resolution_clock::now();

    int result = knapsackParallel(weight, value, n, W);

    auto stop = high_resolution_clock::now();

    cout << "Maximum value: " << result << endl;

    cout << "Number of threads: "
         << omp_get_max_threads() << endl;

    cout << "Execution time: "
         << duration<double, milli>(stop - start).count()
         << " ms\n";

    return 0;
}
