// #include <iostream>

// class IntervalHeap {
// private:
//     int hsize; // number of elements in heap
//     int maxsize; // size of the array
//     int **h; // 2D array to store the lower and higher ends of intervals

//     void swap(int& a, int& b) {
//         int temp = a;
//         a = b;
//         b = temp;
//     }

//     void heapifyUp(int idx) {
//         int parent = (idx - 1) / 2;
//         while (idx > 0 && h[0][idx] < h[0][parent]) {
//             if (h[0][idx] < h[0][parent] || (h[0][idx] == h[0][parent] && h[1][idx] > h[1][parent])) {
//                 swap(h[0][idx], h[0][parent]);
//                 swap(h[1][idx], h[1][parent]);
//             }
//             idx = parent;
//             parent = (idx - 1) / 2;
//         }
//     }

//     void heapifyDown(int idx) {
//         int leftChild = 2 * idx + 1;
//         int rightChild = 2 * idx + 2;
//         int minIdx = idx;

//         if (leftChild < hsize && h[0][leftChild] < h[0][minIdx]) {
//             minIdx = leftChild;
//         } else if (leftChild < hsize && h[0][leftChild] == h[0][minIdx] && h[1][leftChild] > h[1][minIdx]) {
//             minIdx = leftChild;
//         }

//         if (rightChild < hsize && h[0][rightChild] < h[0][minIdx]) {
//             minIdx = rightChild;
//         } else if (rightChild < hsize && h[0][rightChild] == h[0][minIdx] && h[1][rightChild] > h[1][minIdx]) {
//             minIdx = rightChild;
//         }

//         if (minIdx != idx) {
//             swap(h[0][idx], h[0][minIdx]);
//             swap(h[1][idx], h[1][minIdx]);
//             heapifyDown(minIdx);
//         }
//     }

// public:
//     IntervalHeap(int s = 100) {
//         maxsize = s;
//         hsize = 0;
//         h = new int*[2];
//         h[0] = new int[maxsize]; // store the lower end of closed interval
//         h[1] = new int[maxsize]; // store the higher end of closed interval
//     }

//     void insert(int d) {
//         if (hsize == maxsize) {
//             std::cout << "Heap is full!" << std::endl;
//             return;
//         }

//         h[0][hsize] = d;
//         h[1][hsize] = d; // Assuming initial interval is [d, d]
//         hsize++;
//         heapifyUp(hsize - 1);
//     }

//     void update(int oldVal, int newVal) {
//         for (int i = 0; i < hsize; ++i) {
//             if (h[0][i] == oldVal) {
//                 h[0][i] = newVal;
//                 h[1][i] = newVal;
//                 if (i > 0 && h[0][i] < h[0][(i - 1) / 2]) {
//                     heapifyUp(i);
//                 } else {
//                     heapifyDown(i);
//                 }
//                 return;
//             }
//         }
//         std::cout << "Element not found!" << std::endl;
//     }

//     void remove(int val) {
//         int i;
//         for (i = 0; i < hsize; ++i) {
//             if (h[0][i] == val) {
//                 break;
//             }
//         }
//         if (i == hsize) {
//             std::cout << "Element not found!" << std::endl;
//             return;
//         }
//         hsize--;
//         h[0][i] = h[0][hsize];
//         h[1][i] = h[1][hsize];
//         if (i > 0 && h[0][i] < h[0][(i - 1) / 2]) {
//             heapifyUp(i);
//         } else {
//             heapifyDown(i);
//         }
//     }

//     void display() {
//         for (int i = 0; i < hsize; ++i) {
//             std::cout << "[" << h[0][i] << ", " << h[1][i] << "] ";
//         }
//         std::cout << std::endl;
//     }

//     ~IntervalHeap() {
//         delete[] h[0];
//         delete[] h[1];
//         delete[] h;
//     }
// };

// int main() {
//     IntervalHeap intervalHeap;
//     intervalHeap.insert(10);
//     intervalHeap.insert(20);
//     intervalHeap.insert(30);
//     intervalHeap.insert(40);
//     intervalHeap.insert(50);
//     intervalHeap.insert(60);

//     std::cout << "Interval Heap: ";
//     intervalHeap.display();

//     intervalHeap.update(20, 25);
//     std::cout << "After updating 20 to 25: ";
//     intervalHeap.display();

//     intervalHeap.remove(40);
//     std::cout << "After removing 40: ";
//     intervalHeap.display();

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

    bool isSumHelper(Node* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr))
            return true;

        int leftSum = node->left ? node->left->data : 0;
        int rightSum = node->right ? node->right->data : 0;

        return (node->data == leftSum + rightSum) && isSumHelper(node->left) && isSumHelper(node->right);
    }

public:
	
    BinaryTree() {
        root = nullptr;
    }

    Node* getRoot() {
        return root;
    }

    Node* insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
            return root;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            if (temp->left == nullptr) {
                temp->left = new Node(value);
                return temp->left;
            } else {
                q.push(temp->left);
            }

            if (temp->right == nullptr) {
                temp->right = new Node(value);
                return temp->right;
            } else {
                q.push(temp->right);
            }
        }

        return nullptr;
    }

    bool search(int value) {
        if (root == nullptr)
            return false;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            if (temp->data == value)
                return true;

            if (temp->left != nullptr)
                q.push(temp->left);

            if (temp->right != nullptr)
                q.push(temp->right);
        }

        return false;
    }

    bool isSum() {
        if (root == nullptr)
            return true;

        return isSumHelper(root);
    }

    Node* findLCA(Node* root, Node* x, Node* y) {
        if (root == nullptr || x == nullptr || y == nullptr)
            return nullptr;

        if (root == x || root == y)
            return root;

        Node* leftLCA = findLCA(root->left, x, y);
        Node* rightLCA = findLCA(root->right, x, y);

        if (leftLCA && rightLCA)
            return root;

        return leftLCA != nullptr ? leftLCA : rightLCA;
    }
};

int main() {
	
    BinaryTree tree;
    Node* n1 = tree.insert(1);
    Node* n2 = tree.insert(2);
    Node* n3 = tree.insert(3);
    Node* n4 = tree.insert(4);
    Node* n5 = tree.insert(5);
    Node* n6 = tree.insert(6);

    cout << "Is the tree a sum tree? " << (tree.isSum() ? "Yes" : "No") << endl;

    Node* lca = tree.findLCA(tree.getRoot(), n2, n3);
    if (lca != nullptr)
        cout << "Lowest Common Ancestor of 2 and 3 is: " << lca->data << endl;

    return 0;
}
