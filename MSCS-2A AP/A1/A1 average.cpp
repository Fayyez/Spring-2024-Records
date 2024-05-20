// Question no 1
#include <iostream>

#include <stdexcept>


class SortedSet {
	
	private:
	    struct Node {
	    	
	        T data;
	        Node* next;
	        Node(const T& d) : data(d), next(NULL) {}
	    };

	    Node* head;
	    Node* tail;
	
	public:
    	SortedSet() : head(NULL), tail(NULL) {}

	    void insert(const T& data) {
	    	
	        Node* newNode = new Node(data);
	
	        if (!head || data < head->data) {
	            newNode->next = head;
	            head = newNode;
	            if (!tail) tail = head;
	            return;
	        }
	
	        Node* prev = NULL;
	        Node* curr = head;
	        while (curr && curr->data < data) {
	            prev = curr;
	            curr = curr->next;
	        }
	
	        if (curr && curr->data == data) {
	            delete newNode;
	            return;
	        }
	
	        newNode->next = curr;
	        if (!prev) {
	            head = newNode;
	        } else {
	            prev->next = newNode;
	        }
	        if (!curr) tail = newNode;
	    }
	    
	    void print() const {
	        Node* temp = head;
	        while (temp) {
	            std::cout << temp->data << " ";
	            temp = temp->next;
	        }
	        std::cout << std::endl;
	    }

	    void merge(SortedSet<T> const &otherSet) {
	        Node* temp = otherSet.head;
	        while (temp) {
	            insert(temp->data);
	            temp = temp->next;
	        }
	    }

	    void remove(int index) {
	        if (index < 0) return;
	
	        if (index == 0) {
	            Node* temp = head;
	            head = head->next;
	            delete temp;
	            if (!head) tail = NULL;
	            return;
	        }
	
	        Node* prev = NULL;
	        Node* curr = head;
	        int i = 0;
	        while (curr && i < index) {
	            prev = curr;
	            curr = curr->next;
	            i++;
	        }
	
	        if (!curr) return;
	
	        prev->next = curr->next;
	        if (!prev->next) tail = prev;
	        delete curr;
	    }


	    void merge(SortedSet<T> const &otherSet) {
	        Node* temp = otherSet.head;
	        while (temp) {
	            insert(temp->data);
	            temp = temp->next;
	        }
	    }
};

	int main() {
	    SortedSet<int> a;
	    a.insert(1);	a.insert(2);
		a.insert(3);	a.insert(4);
	    a.insert(10);	a.insert(50);
	
	    SortedSet<int> b;
	    b.insert(6);	b.insert(10);
	    b.insert(11);
	
	    std::cout << "Set a: ";
	    
	    a.print();
	    
	    std::cout << "Set b: ";
	    
	    b.print();
	
	    a.merge(b);
	    
	    std::cout << "After Merging the Resultant Set will be= ";
	    
	    a.print();
	    return 0;
	}
	
	
	
//	Question no 2

#include <iostream>
#include <stdexcept>


class SortedSet {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(NULL) {}
    };

    Node* head;
    Node* tail;

public:
    SortedSet() : head(NULL), tail(NULL) {}

    void insert(const T& data) {
        Node* newNode = new Node(data);

        if (!head || data < head->data) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = head;
            return;
        }

        Node* prev = NULL;
        Node* curr = head;
        while (curr && curr->data < data) {
            prev = curr;
            curr = curr->next;
        }

        if (curr && curr->data == data) {
            delete newNode;
            return;
        }

        newNode->next = curr;
        prev->next = newNode;
        if (!curr) tail = newNode;
    }
    
    
    void print() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

	  void rotate(int k) {
        if (k <= 0) {
            std::cerr << "Entered Rotation Value Is Invalid. Enter Postive Number." << std::endl;
            return;
        }

        int count = 1;
        Node* current = head;
        while (current && count < k) {
            current = current->next;
            count++;
        }

        if (!current) {
            std::cerr << "Entered Rotation Value Is Invalid. Enter the value according to size" << std::endl;
            return;
        }

        tail->next = head;
        head = current->next;
        current->next = NULL;
        tail = current;
    }
    
    
    void remove(int index) {
        if (index < 0) return;

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (!head) tail = NULL;
            return;
        }

        Node* prev = NULL;
        Node* curr = head;
        int i = 0;
        while (curr && i < index) {
            prev = curr;
            curr = curr->next;
            i++;
        }

        if (!curr) return;

        prev->next = curr->next;
        if (!prev->next) tail = prev;
        delete curr;
    }

};

int main() {
    SortedSet<int> a;
    a.insert(10);
    a.insert(20);
    a.insert(30);
    a.insert(40);
    a.insert(50);
    a.insert(60);

    std::cout << "Actual linked list= ";
    a.print();

    int k;
    std::cout << "Value of K for Rotation= ";
    std::cin >> k;

    a.rotate(k);

    std::cout << "After Rotating by " << k << " node, the Link List will be= ";
    a.print();

    return 0;
}

//Question no 3

#include <iostream>

#include <set>

using namespace std;

class Node {
	public:
	    T data;
	    Node<T>* next;
	    Node(T value) : data(value), next(NULL) {}
	};


class SortedSet {
	private:
	    	Node<T>* head;
	
	public:
	    SortedSet() : head(NULL) {}

    
	    void insert(T value) {
	        Node<T>* newNode = new Node<T>(value);
	        if (!head || value < head->data) {
	            newNode->next = head;
	            head = newNode;
	        } else {
	            Node<T>* temp = head;
	            while (temp->next && temp->next->data < value) {
	                temp = temp->next;
	            }
	            newNode->next = temp->next;
	            temp->next = newNode;
	        }
	    }
	
	    
	    void print() {
	        Node<T>* temp = head;
	        while (temp != NULL) {
	            cout << temp->data << " ";
	            temp = temp->next;
	        }
	        cout << endl;
	    }

    
	    void reverse() {
	        Node<T>* prev = NULL;
	        Node<T>* current = head;
	        Node<T>* next = NULL;
	
	        while (current != NULL) {
	            next = current->next;
	            current->next = prev;
	            prev = current;
	            current = next;
	        }
	
	        head = prev;
	    }
};

int main() {
    // Test cases
    SortedSet<int> list1;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    cout << "Original list 1: ";
    list1.print();
    list1.reverse();
    cout << "Reversed list 1: ";
    list1.print();

    SortedSet<int> list2;
    list2.insert(1);
    list2.insert(2);
    list2.insert(3);
    list2.insert(4);
    list2.insert(5);
    cout << "Original list 2: ";
    list2.print();
    list2.reverse();
    cout << "Reversed list 2: ";
    list2.print();

    SortedSet<int> list3;
    cout << "Original empty list: ";
    list3.print();
    list3.reverse();
    cout << "Reversed empty list: ";
    list3.print();

    SortedSet<int> list4;
    list4.insert(1);
    cout << "Original list with single element: ";
    list4.print();
    list4.reverse();
    cout << "Reversed list with single element: ";
    list4.print();

    return 0;
}
