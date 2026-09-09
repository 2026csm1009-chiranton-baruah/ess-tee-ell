#include <iostream>
#include <deque>    // Required for std::deque
#include <stdexcept> // For exception handling

int main() {
    try {
        // Create a deque of integers
        std::deque<int> dq;

        // Insert elements at the back
        dq.push_back(10);
        dq.push_back(20);

        // Insert elements at the front
        dq.push_front(5);
        dq.push_front(1);

        // Display elements
        std::cout << "Deque elements: ";
        for (int num : dq) {
            std::cout << num << " ";
        }
        std::cout << "\n";

        // Access elements
        std::cout << "Front element: " << dq.front() << "\n";
        std::cout << "Back element: " << dq.back() << "\n";

        // Modify elements
        dq[1] = 15; // Direct access like vector
        std::cout << "After modification: ";
        for (int num : dq) {
            std::cout << num << " ";
        }
        std::cout << "\n";

        // Remove elements
        dq.pop_front();
        dq.pop_back();

        std::cout << "After popping front and back: ";
        for (int num : dq) {
            std::cout << num << " ";
        }
        std::cout << "\n";

        // Safe access with bounds checking
        std::cout << "Element at index 1: " << dq.at(1) << "\n";

    } catch (const std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
