// #include <iostream>
// using namespace std;

// class IntervalHeap {
// private:
//     int hsize; // number of elements in heap
//     int maxsize; // size of the array
//     int** h; // 2D array to store the intervals

// public:
//     IntervalHeap(int s = 100) {
//         maxsize = s;
//         hsize = 0;
//         h = new int* [2];
//         h[0] = new int[maxsize]; // store the lower end of closed interval
//         h[1] = new int[maxsize]; // store the higher end of closed interval
//     }

//     ~IntervalHeap() {
//         delete[] h[0];
//         delete[] h[1];
//         delete[] h;
//     }

//     // Helper function to swap two elements
//     void swap(int& a, int& b) {
//         int temp = a;
//         a = b;
//         b = temp;
//     }

//     // Helper function to maintain min heap property on the left side
//     void minHeapify(int i) {
//         int left = 2 * i + 1;
//         int right = 2 * i + 2;
//         int smallest = i;

//         if (left < hsize && h[0][left] < h[0][smallest])
//             smallest = left;

//         if (right < hsize && h[0][right] < h[0][smallest])
//             smallest = right;

//         if (smallest != i) {
//             swap(h[0][i], h[0][smallest]);
//             swap(h[1][i], h[1][smallest]);
//             minHeapify(smallest);
//         }
//     }

//     // Helper function to maintain max heap property on the right side
//     void maxHeapify(int i) {
//         int left = 2 * i + 1;
//         int right = 2 * i + 2;
//         int largest = i;

//         if (left < hsize && h[1][left] > h[1][largest])
//             largest = left;

//         if (right < hsize && h[1][right] > h[1][largest])
//             largest = right;

//         if (largest != i) {
//             swap(h[0][i], h[0][largest]);
//             swap(h[1][i], h[1][largest]);
//             maxHeapify(largest);
//         }
//     }

//     // Insert a new element into the interval heap
//     void Insert(int d) {
//         // If the number of elements is even, create a new node
//         if (hsize % 2 == 0) {
//             h[0][hsize] = d; // Set the lower end of the interval
//             h[1][hsize] = d; // Set the higher end of the interval
//             hsize++;
//         }
//         else {
//             // If the number of elements is odd, add the new element to the existing node
//             h[1][hsize - 1] = d;
//             // Maintain min heap property on the left side
//             for (int i = (hsize - 2) / 2; i >= 0; i--) {
//                 minHeapify(i);
//             }
//             // Maintain max heap property on the right side
//             for (int i = (hsize - 1) / 2; i >= 0; i--) {
//                 maxHeapify(i);
//             }
//         }
//     }

//     // Update an element in the interval heap
//     void Update(int oldVal, int newVal) {
//         // Find the old value and update it with the new value
//         for (int i = 0; i < hsize; i++) {
//             if (h[0][i] == oldVal || h[1][i] == oldVal) {
//                 h[0][i] = newVal;
//                 h[1][i] = newVal;
//                 break;
//             }
//         }
//         // Re-heapify after update
//         for (int i = (hsize - 2) / 2; i >= 0; i--) {
//             minHeapify(i);
//         }
//         for (int i = (hsize - 1) / 2; i >= 0; i--) {
//             maxHeapify(i);
//         }
//     }

//     // Delete an element from the interval heap
//     void Delete(int val) {
//         // Find the element to delete
//         int index = -1;
//         for (int i = 0; i < hsize; i++) {
//             if (h[0][i] == val || h[1][i] == val) {
//                 index = i;
//                 break;
//             }
//         }
//         if (index == -1) {
//             cout << "Element not found in the heap." << endl;
//             return;
//         }
//         // Replace the element with the last element and decrease the heap size
//         h[0][index] = h[0][hsize - 1];
//         h[1][index] = h[1][hsize - 1];
//         hsize--;

//         // Re-heapify after deletion
//         for (int i = (hsize - 2) / 2; i >= 0; i--) {
//             minHeapify(i);
//         }
//         for (int i = (hsize - 1) / 2; i >= 0; i--) {
//             maxHeapify(i);
//         }
//     }

//     // Display the interval heap
//     void Display() {
//         cout << "Interval Heap: ";
//         for (int i = 0; i < hsize; i++) {
//             cout << "[" << h[0][i] << ", " << h[1][i] << "] ";
//         }
//         cout << endl;
//     }
// };

// int main() {
//     IntervalHeap heap;
//     heap.Insert(2);
//     heap.Insert(30);
//     heap.Insert(3);
//     heap.Insert(17);
//     heap.Insert(4);
//     heap.Insert(12);
//     heap.Insert(3);
//     heap.Insert(11);
//     heap.Insert(4);
//     heap.Insert(15);
//     heap.Insert(6);
//     heap.Insert(5);
//     heap.Display();

//     heap.Insert(40);
//     heap.Display();

//     heap.Update(17, 20);
//     heap.Display();

//     heap.Delete(30);
//     heap.Display();

//     return 0;
// }

#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

    // Helper function for insertion
    Node* insertUtil(Node* root, int value) {
        if (root == nullptr)
            return new Node(value);
        if (value < root->data)
            root->left = insertUtil(root->left, value);
        else if (value > root->data)
            root->right = insertUtil(root->right, value);
        return root;
    }

    // Helper function for deletion
    Node* deleteUtil(Node* root, int value) {
        if (root == nullptr)
            return root;
        if (value < root->data)
            root->left = deleteUtil(root->left, value);
        else if (value > root->data)
            root->right = deleteUtil(root->right, value);
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteUtil(root->right, temp->data);
        }
        return root;
    }

    // Helper function to find the node with the minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // Helper function for search
    bool searchUtil(Node* root, int value) {
        if (root == nullptr)
            return false;
        if (root->data == value)
            return true;
        if (value < root->data)
            return searchUtil(root->left, value);
        else
            return searchUtil(root->right, value);
    }

    // Helper function for isSum
    bool isSumUtil(Node* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return true;
        int leftSum = root->left ? root->left->data : 0;
        int rightSum = root->right ? root->right->data : 0;
        return (root->data == leftSum + rightSum) && isSumUtil(root->left) && isSumUtil(root->right);
    }

    // Helper function for findLCA
    Node* findLCAUtil(Node* root, Node* x, Node* y, bool& xFound, bool& yFound) {
        if (root == nullptr)
            return nullptr;

        if (root == x) {
            xFound = true;
            return root;
        }
        if (root == y) {
            yFound = true;
            return root;
        }

        Node* leftLCA = findLCAUtil(root->left, x, y, xFound, yFound);
        Node* rightLCA = findLCAUtil(root->right, x, y, xFound, yFound);

        if (leftLCA && rightLCA)
            return root;

        return (leftLCA != nullptr) ? leftLCA : rightLCA;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    // Insertion
    void insert(int value) {
        root = insertUtil(root, value);
    }

    // Deletion
    void remove(int value) {
        root = deleteUtil(root, value);
    }

    // Search
    bool contains(int value) {
        return searchUtil(root, value);
    }

    // Function to check if the binary tree is a sum tree
    bool isSum() {
        return isSumUtil(root);
    }

    // Function to find Lowest Common Ancestor (LCA) of two nodes
    Node* findLCA(Node* x, Node* y) {
        if (x == nullptr || y == nullptr)
            return nullptr;

        bool xFound = false, yFound = false;
        Node* lca = findLCAUtil(root, x, y, xFound, yFound);

        if (xFound && yFound)
            return lca;
        else
            return nullptr;
    }

    // Getter for root node
    Node* getRoot() {
        return root;
    }
};

int main() {
    BinaryTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    // Test the methods
    cout << "Is the tree a sum tree? " << (tree.isSum() ? "Yes" : "No") << endl;

    // Example usage of findLCA using the getter method
    Node* rootNode = tree.getRoot();
    if (rootNode) {
        Node* node5 = tree.findLCA(rootNode->left->left, rootNode->right->right);
        if (node5)
            cout << "Lowest Common Ancestor of 5 and 35: " << node5->data << endl;
        else
            cout << "Nodes are not present in the tree!" << endl;
    }
    else {
        cout << "Tree is empty!" << endl;
    }

    return 0;
}