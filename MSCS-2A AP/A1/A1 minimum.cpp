//importing libraries
#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

//using template class
template<typename T>
class SortedSet {
private:
    class Node {
    public:
        T data;
        Node* next;
        
        Node(const T& value) {
            data = value;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

public:
    SortedSet() {
        head = nullptr;
        tail = nullptr;
    }

    //inserting values by checking if head is empty or not
    void insert(const T& data) {
        if (contains(data))
            return;

        Node* newNode = new Node(data);
        if (head == nullptr || data < head->data) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) tail = newNode;
        } else if (data > tail->data) {
            tail->next = newNode;
            tail = newNode;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->data < data) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    //delete the value at given index by this function
    void Delete(int index) {
        if (index < 0 || index >= getSize()) {
            cout << "Invalid index.\n";
            return;
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr) tail = nullptr;
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1; ++i) {
                temp = temp->next;
            }
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            if (temp->next == nullptr) tail = temp;
        }
    }

    //printing the elements of lists
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    //this will get the size of the list
    int getSize() const {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    //rotating the list by input value of k
    void rotate(int k) {
    if (k <= 0) {
        cout << "Invalid value of k. Please enter a positive value.\n";
        return;
    }

    if (getSize() == 0 || getSize() == 1) {
        cout << "No rotation required.\n";
        return;
    }

    k = k % getSize(); // ensure k is within the size of the list

    if (k == 0) {
        cout << "No rotation required.\n";
        return;
    }

    Node* current = head;
    int count = 1;
    while (count < k && current != nullptr) {
        current = current->next;
        count++;
    }

    if (current == nullptr || current->next == nullptr) {
        cout << "No rotation required.\n";
        return;
    }

    Node* kthNode = current;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = head;
    head = kthNode->next;
    kthNode->next = nullptr;
}


    //reversing the list
    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
    }

    //Geting the input list
    void inputList() {
        T value;
        string input;
        bool stopInput = false;

        cout << "Enter values for the list (type 'stop' to end): ";
        while (!stopInput) {
            cin >> input;
            if (input == "stop") {
                stopInput = true;
                break;
            }

            istringstream stream(input);
            if (!(stream >> value)) {
                cout << "Invalid input. Please enter a valid value or 'stop' to end.\n";
                continue;
            }
            insert(value);
        }
    }

    //union of input lists
    void unionSet(const SortedSet<T>& otherSet) {
        Node* temp = otherSet.head;
        while (temp) {
            insert(temp->data);
            temp = temp->next;
        }
    }

private:
    // this function checks if it contains values or not
    bool contains(const T& data) const {
        Node* current = head;
        while (current) {
            if (current->data == data)
                return true;
            current = current->next;
        }
        return false;
    }
};

//main function
int main() {
    SortedSet<int> a, b;
    int k;

    cout << "Enter the values for set A: ";
    a.inputList();

    cout << "Enter the values for set B: ";
    b.inputList();

    cout << "Sorted set A: ";
    a.print();
    cout << "Sorted set B: ";
    b.print();

    a.unionSet(b);

    cout << "After union, set A:";
    a.print();

    cout << "Enter the value of k for rotation: ";
    cin >> k;
    while (k <= 0 || k >= a.getSize()) {
        cout << "Invalid rotation value. Please enter again: ";
        cin >> k;
    }

    a.rotate(k);

    cout << "Original linked list: ";
    a.print();

    a.reverseList();

    cout << "Reversed linked list: ";
    a.print();

 return 0;
}