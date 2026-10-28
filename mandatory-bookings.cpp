#include <bits/stdc++.h>
using namespace std;

struct Interval {
    long long s, e;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<Interval> mandatory(m), optional(n);
    for (int i = 0; i < m; i++) cin >> mandatory[i].s >> mandatory[i].e;
    for (int i = 0; i < n; i++) cin >> optional[i].s >> optional[i].e;

    // Step 1: sort and merge mandatory intervals
    sort(mandatory.begin(), mandatory.end(), [](auto &a, auto &b){
        return a.s < b.s;
    });

    vector<Interval> merged;
    for (auto &cur : mandatory) {
        if (!merged.empty() && cur.s < merged.back().e) {
            // overlap becomes invalid
            cout << -1 << "\n";
            return 0;
        }
        merged.push_back(cur);
    }

    // Step 2: filter optional using binary search
    vector<Interval> valid;
    for (auto &opt : optional) {
        // find mandatory interval with start >= opt.s
        auto it = lower_bound(merged.begin(), merged.end(), opt,
            [](const Interval &a, const Interval &b){
                return a.s < b.s;
            });

        bool clash = false;
        if (it != merged.end() && opt.e > it->s) clash = true; // overlaps next mandatory
        if (it != merged.begin()) {
            auto prev = it - 1;
            if (opt.s < prev->e) clash = true; // overlaps previous mandatory
        }
        if (!clash) valid.push_back(opt);
    }

    // Step 3: greedy scheduling
    sort(valid.begin(), valid.end(), [](auto &a, auto &b){
        return a.e < b.e;
    });

    int count = 0;
    long long last_end = -1;
    for (auto &ev : valid) {
        if (ev.s >= last_end) {
            count++;
            last_end = ev.e;
        }
    }

    cout << count << "\n";
    return 0;
}
