//          Question 1
// #include<bits/stdc++.h>
// using namespace std;

// class IntervalHeap {
//     int hsize; //number of elements in heap;
//     int maxsize; //size of the array
//     int **h;
// public:
//     IntervalHeap(int s=100){
//         maxsize = s;
//         hsize = 0;
//         h = new int*[2];
//         h[0] = new int[maxsize];//store the lower end of closed interval
//         h[1] = new int[maxsize];//store the higher end of closed interval
//     };

//     void Insert(int d) {
//         if (hsize == maxsize) {
//             cout << "Heap is full\n";
//             return;
//         }
//         int i = hsize / 2;
//         if (hsize % 2 == 0) {
//             h[0][i] = h[1][i] = d;
//         } else {
//             if (d < h[0][i]) {
//                 h[1][i] = h[0][i];
//                 h[0][i] = d;
//             } else {
//                 h[1][i] = d;
//             }
//         }
//         hsize++;
//     }

//     void Update(int old_val, int new_val) {
//         for (int i = 0; i < hsize / 2; i++) {
//             if (h[0][i] == old_val) {
//                 h[0][i] = new_val;
//                 if (new_val > h[1][i]) {
//                     swap(h[0][i], h[1][i]);
//                 }
//                 return;
//             }
//             if (h[1][i] == old_val) {
//                 h[1][i] = new_val;
//                 if (new_val < h[0][i]) {
//                     swap(h[0][i], h[1][i]);
//                 }
//                 return;
//             }
//         }
//         cout << "Value not found\n";
//     }

//     void Delete(int d) {
//         for (int i = 0; i < hsize / 2; i++) {
//             if (h[0][i] == d || h[1][i] == d) {
//                 h[0][i] = h[0][hsize / 2 - 1];
//                 h[1][i] = h[1][hsize / 2 - 1];
//                 hsize--;
//                 return;
//             }
//         }
//         cout << "Value not found\n";
//     }

//     void Display() {
//         for (int i = 0; i < hsize / 2; i++) {
//             cout << "[" << h[0][i] << ", " << h[1][i] << "] ";
//         }
//         cout << "\n";
//     }
// };

// int main() {
//     IntervalHeap heap(10);
//     heap.Insert(5);
//     heap.Insert(10);
//     heap.Display();
//     heap.Update(5, 20);
//     heap.Display();
//     heap.Delete(7);
//     heap.Display();
//      heap.Insert(3);
//     heap.Insert(17);
//     heap.Insert(2);
//     heap.Insert(30);
//     heap.Insert(10);
//     heap.Insert(15);
//     heap.Insert(20);
//     heap.Insert(40);
//     heap.Delete(17);
//     heap.Display();
//     return 0;
// }


//          Question 2

// #include<bits/stdc++.h>
// using namespace std;

// struct Node {
//     int key;
//     Node* left;
//     Node* right;
// };

// Node* newNode(int key) {
//     Node* node = new Node();
//     node->key = key;
//     node->left = node->right = NULL;
//     return node;
// }

// Node* insert(Node* node, int key) {
//     if (node == NULL) return newNode(key);
//     if (key < node->key)
//         node->left = insert(node->left, key);
//     else if (key > node->key)
//         node->right = insert(node->right, key);
//     return node;
// }

// Node* minValueNode(Node* node) {
//     Node* current = node;
//     while (current && current->left != NULL)
//         current = current->left;
//     return current;
// }

// Node* deleteNode(Node* root, int key) {
//     if (root == NULL) return root;
//     if (key < root->key)
//         root->left = deleteNode(root->left, key);
//     else if (key > root->key)
//         root->right = deleteNode(root->right, key);
//     else {
//         if (root->left == NULL) {
//             Node* temp = root->right;
//             free(root);
//             return temp;
//         }
//         else if (root->right == NULL) {
//             Node* temp = root->left;
//             free(root);
//             return temp;
//         }
//         Node* temp = minValueNode(root->right);
//         root->key = temp->key;
//         root->right = deleteNode(root->right, temp->key);
//     }
//     return root;
// }

// bool search(Node* root, int key) {
//     if (root == NULL) return false;
//     if (root->key == key) return true;
//     if (root->key < key)
//         return search(root->right, key);
//     return search(root->left, key);
// }

// int isSum(Node* node) {
//     if(node == NULL)
//         return 0;
//     if(node->left == NULL && node->right == NULL)
//         return node->key;
//     int left_sum = isSum(node->left);
//     int right_sum = isSum(node->right);
//     if(left_sum == -1 || right_sum == -1 || node->key != left_sum + right_sum)
//         return -1;
//     return node->key * 2;
// }

// Node* findLCA(Node* node, int x, int y) {
//     if (node == NULL) return NULL;
//     if (node->key == x || node->key == y) return node;
//     Node* left_lca = findLCA(node->left, x, y);
//     Node* right_lca = findLCA(node->right, x, y);
//     if (left_lca && right_lca) return node;
//     return (left_lca != NULL)? left_lca: right_lca;
// }

// int main() {
//     Node* root = NULL;
//     int choice, key, x, y;
//     Node* lca; // Declare lca here
//     while (true) {
//         cout << "1. Insert\n2. Delete\n3. Search\n4. Check if sum tree\n5. Find LCA\n6. Exit\nEnter your choice: ";
//         cin >> choice;
//         switch (choice) {
//             case 1:
//                 cout << "Enter key to insert: ";
//                 cin >> key;
//                 root = insert(root, key);
//                 break;
//             case 2:
//                 cout << "Enter key to delete: ";
//                 cin >> key;
//                 root = deleteNode(root, key);
//                 break;
//             case 3:
//                 cout << "Enter key to search: ";
//                 cin >> key;
//                 if (search(root, key))
//                     cout << "Key found\n";
//                 else
//                     cout << "Key not found\n";
//                 break;
//             case 4:
//                 if (isSum(root) != -1)
//                     cout << "It is a sum tree\n";
//                 else
//                     cout << "It is not a sum tree\n";
//                 break;
//             case 5:
//                 cout << "Enter two keys to find LCA: ";
//                 cin >> x >> y;
//                 lca = findLCA(root, x, y); // Use lca here
//                 if (lca != NULL)
//                     cout << "LCA of " << x << " and " << y << " is " << lca->key << "\n";
//                 else
//                     cout << x << " and/or " << y << " are not in the tree\n";
//                 break;
//             case 6:
//                 exit(0);
//             default:
//                 cout << "Invalid choice\n";
//         }
//     }
//     return 0;
// }
