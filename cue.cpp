#include <iostream>
#include <queue>   // Required for std::queue
#include <stdexcept> // For exception handling

int main() {
    std::queue<int> q; // Create a queue of integers

    // Insert elements into the queue
    q.push(10);
    q.push(20);
    q.push(30);

    std::cout << "Queue size: " << q.size() << "\n";
    std::cout << "Front element: " << q.front() << "\n";
    std::cout << "Back element: " << q.back() << "\n\n";

    // Remove elements safely
    while (!q.empty()) {
        std::cout << "Removing: " << q.front() << "\n";
        q.pop();
    }

    // Example of safe access
    try {
        if (q.empty()) {
            throw std::underflow_error("Queue is empty. Cannot access elements.");
        }
        std::cout << "Front: " << q.front() << "\n";
    } catch (const std::underflow_error &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
