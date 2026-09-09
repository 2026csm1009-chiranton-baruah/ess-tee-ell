#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for std::greater

int main() {
    // ---------- MAX-HEAP (default) ----------
    std::priority_queue<int> maxHeap;

    // Insert elements
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(20);
    maxHeap.push(15);

    std::cout << "Max-Heap (largest first): ";
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " "; // Access highest priority element
        maxHeap.pop(); // Remove it
    }
    std::cout << "\n";

    // ---------- MIN-HEAP ----------
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // Insert elements
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);
    minHeap.push(15);

    std::cout << "Min-Heap (smallest first): ";
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " "; // Access smallest element
        minHeap.pop();
    }
    std::cout << "\n";

    // ---------- CUSTOM OBJECT ----------
    struct Task {
        int priority;
        std::string name;
    };

    // Custom comparator for max-heap based on priority
    auto cmp = [](const Task &a, const Task &b) {
        return a.priority < b.priority; // higher priority first
    };

    std::priority_queue<Task, std::vector<Task>, decltype(cmp)> taskQueue(cmp);

    taskQueue.push({3, "Low priority"});
    taskQueue.push({10, "High priority"});
    taskQueue.push({5, "Medium priority"});

    std::cout << "Tasks by priority:\n";
    while (!taskQueue.empty()) {
        std::cout << taskQueue.top().priority << " - " << taskQueue.top().name << "\n";
        taskQueue.pop();
    }

    return 0;
}
