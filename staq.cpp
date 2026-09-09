#include <iostream>
#include <stack>
#include <limits> // For numeric_limits

using namespace std;

// Function to display stack contents without modifying the original stack
void displayStack(stack<int> s) {
    if (s.empty()) {
        cout << "Stack is empty.\n";
        return;
    }
    cout << "Stack elements (top to bottom): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";
}

int main() {
    stack<int> st;
    int choice, value;

    while (true) {
        cout << "\n--- Stack Menu ---\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. View Top\n";
        cout << "4. Display Stack\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        // Validate menu choice input
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: // Push
                cout << "Enter value to push: ";
                if (!(cin >> value)) {
                    cout << "Invalid input. Please enter an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                st.push(value);
                cout << value << " pushed onto the stack.\n";
                break;

            case 2: // Pop
                if (st.empty()) {
                    cout << "Stack is empty. Cannot pop.\n";
                } else {
                    cout << "Popped: " << st.top() << "\n";
                    st.pop();
                }
                break;

            case 3: // View Top
                if (st.empty()) {
                    cout << "Stack is empty.\n";
                } else {
                    cout << "Top element: " << st.top() << "\n";
                }
                break;

            case 4: // Display
                displayStack(st);
                break;

            case 5: // Exit
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please select between 1 and 5.\n";
        }
    }
}
