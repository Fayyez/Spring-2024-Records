// Question 1

#include <iostream>
using namespace std;

const int MAX_SIZE = 5; // Maximum size of the stack

class Stack {
private:
    int arr[MAX_SIZE];
    int top;

public:
    Stack() {
        top = -1;
    } // Initialize top to -1 to signify an empty stack

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == MAX_SIZE - 1);
    }

    void push(int element) {
        if (!isFull()) {
            top++;
            arr[top] = element;
            cout << "Inserted element: " << element << " into the stack.\n";
        } else {
            cout << "Stack is full. Cannot insert element " << element << ".\n";
        }
    }

    void pop() {
        if (!isEmpty()) {
            int poppedElement = arr[top];
            top--;
            cout << "Removed element: " << poppedElement << " from the stack.\n";
        } else {
            cout << "Stack is empty. Cannot remove from an empty stack.\n";
        }
    }

    int topElement() {
        if (!isEmpty()) {
            return arr[top];
        } else {
            cout << "Stack is empty.\n";
            return -1; // Consider -1 as an invalid value when stack is empty.
        }
    }

    void flipStack() {
        if (isEmpty() || top == 0) {
            return; // No need to flip if the stack is empty or has only one element
        }
        int start = 0;
        int end = top;
        while (start < end) {
            // Swap elements at start and end indices
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
};

int main() {
    Stack myStack;
    // Insert elements until the stack becomes full
    for (int i = 1; i <= 5; ++i) {
        myStack.push(i);
    }

    cout << "Before reversing:" << endl;
    while (!myStack.isEmpty()) {
        cout << myStack.topElement() << " ";
        myStack.pop();
    }
    cout << endl;

    // Insert elements again
    for (int i = 1; i <= 5; ++i) {
        myStack.push(i);
    }

    myStack.flipStack();

    cout << "After reversing:" << endl;
    while (!myStack.isEmpty()) {
        cout << myStack.topElement() << " ";
        myStack.pop();
    }
    cout << endl;

    return 0;
}



