//                  QUESTION 1: 

// #include <iostream>
// #include <vector>

// using namespace std;

// class Stack {
// private:
//     vector<int> items; // vector to store stack elements

// public:
//     // chhecking if the stack is empty
//     bool isEmpty() {
//         return items.empty();
//     }

//     // Push an element onto the stack
//     void push(int item) {
//         items.push_back(item);
//     }

//     // poping the top element from the stack and return it
//     int pop() {
//         if (isEmpty()) {
//             return -1; // Or any other appropriate value to indicate empty stack
//         }
//         int top = items.back(); // getting the top element
//         items.pop_back(); // removing the top element from the vector
//         return top; // returning the top element
//     }

//     // peeking at the top element of the stack without removing it
//     int peek() {
//         if (isEmpty()) {
//             return -1; // Or any other appropriate value to indicate empty stack
//         }
//         return items.back(); // Return the top element
//     }

//     // getting the size of the stack
//     size_t size() {
//         return items.size();
//     }

//     // reversing the order of elements in the stack
//     void flipStack() {
//         // No need to flip if stack has 0 or 1 element
//         if (items.size() <= 1) {
//             return;
//         }

//         // swapping the first and last elements in the vector
//         int temp = items.front();
//         items.front() = items.back();
//         items.back() = temp;
//     }
// };

// int main() {
//     Stack stack;
//     stack.push(1);
//     stack.push(2);
//     stack.push(3);

//     cout << "Stack elements before flipping:" << endl;
//     while (!stack.isEmpty()) {
//         cout << stack.pop() << " ";
//     }
//     cout << endl;

//     stack.push(1);
//     stack.push(2);
//     stack.push(3);

//     stack.flipStack();

//     cout << "Stack elements after flipping:" << endl;
//     while (!stack.isEmpty()) {
//         cout << stack.pop() << " ";
//     }
//     cout << endl;

//     return 0;
// }

//                  QUESTION 2: 
// #include <iostream>
// #include <vector>

// using namespace std;

// class UndoStack {
// private:
//     vector<int> items; // vector to store stack elements
//     const int maxSize = 100; 

// public:
//     // pushing elements onto the stack
//     void push(int item) {
//         if (items.size() == maxSize) {
//             items.erase(items.begin()); // Removing the oldest element if stack is full
//         }
//         items.push_back(item); // pushing the new element onto the stack
//     }

//     // poping the top element from the stack and return it
//     int pop() {
//         if (items.empty()) {
//             return -1; // Or any other appropriate value to indicate empty stack
//         }
//         int top = items.back(); // Get the top element
//         items.pop_back(); // Remove the top element from the vector
//         return top; // Return the top element
//     }

//     
//     int peek() { at
//         if (items.empty()) {
//             return -1; // Or any other appropriate value to indicate empty stack
//         }
//         return items.back(); // Return the top element
//     }

//     // Get the size of the stack
//     size_t size() {
//         return items.size();
//     }
// };

// int main() {
//     UndoStack stack;

//     // pushing more than 100 elements into the stack
//     for (int i = 1; i <= 205; ++i) {
//         stack.push(i);
//     }

//     // Popping elements from the stack
//     cout << "Popping elements from the stack:" << endl;
//     for (int i = 1; i <= 100; ++i) {
//         cout << stack.pop() << " ";
//     }
//     cout << endl;

//     return 0;
// }


//                  QUESTION 3: 

// #include <iostream>
// #include <vector>
// #include <cmath>

// using namespace std;
// template<typename T>

// class Queue {
// private:
//     vector<T> data;
//     int frontIndex;
//     int rearIndex;
//     int capacity;

// public:
//     Queue(int size) : frontIndex(0), rearIndex(-1), capacity(size) {
//         data.resize(size);
//     }

//     void enqueue(const T& value) {
//         if (isFull()) {
//             // cout << "Queue is full. Cannot enqueue." << endl;
//             return;
//         }
//         rearIndex = (rearIndex + 1) % capacity;
//         data[rearIndex] = value;
//     }

//     T dequeue() {
//         if (isEmpty()) {
//             cout << "Queue is empty. Cannot dequeue." << endl;
//             return T();
//         }
//         T frontValue = data[frontIndex];
//         frontIndex = (frontIndex + 1) % capacity;
//         return frontValue;
//     }

//     bool isEmpty() {
//         return (rearIndex == frontIndex - 1) || (frontIndex == 0 && rearIndex == capacity - 1);
//     }

//     bool isFull() {
//         return (rearIndex + 1) % capacity == frontIndex;
//     }
// };

// // radix sort for integers
// void radixSortInteger(vector<int>& arr, int maxDigits, int radix) {
//     vector<Queue<int>> buckets(radix, Queue<int>(arr.size()));

//     // iterating over each digit position from right to left
//     for (int digit = 1; digit <= maxDigits; ++digit) {
//         // distributing keys into buckets based on the current digit
//         for (int num : arr) {
//             int digitValue = (num / static_cast<int>(pow(radix, digit - 1))) % radix;
//             buckets[digitValue].enqueue(num);
//         }

//         // concatenating keys from buckets back into array
//         int index = 0;
//         for (Queue<int>& bucket : buckets) {
//             while (!bucket.isEmpty()) {
//                 arr[index++] = bucket.dequeue();
//             }
//         }
//     }
// }

// // radix sort for strings
// void radixSortString(vector<string>& arr, int maxLength) {
//     const int radix = 256; // Assuming ASCII characters

//     // iterate over each character position from right to left
//     for (int charPos = maxLength - 1; charPos >= 0; --charPos) {
//         vector<Queue<string>> buckets(radix, Queue<string>(arr.size()));

//         // distributing keys into buckets based on the current character
//         for (string& str : arr) {
//             int charValue = (charPos < str.length()) ? static_cast<int>(str[charPos]) : 0;
//             buckets[charValue].enqueue(str);
//         }

//         // concatenating keys from buckets back into array
//         int index = 0;
//         for (Queue<string>& bucket : buckets) {
//             while (!bucket.isEmpty()) {
//                 arr[index++] = bucket.dequeue();
//             }
//         }
//     }
// }

// int main() {
//     int nIntegers;
//     cout << "Enter the number of integers: ";
//     cin >> nIntegers;

//     // Input for integers
//     vector<int> intArr(nIntegers);
//     cout << "Enter the integers:" << endl;
//     for (int i = 0; i < nIntegers; ++i) {
//         cin >> intArr[i];
//     }

//     int maxDigitsInt = 0;
//     for (int num : intArr) {
//         maxDigitsInt = max(maxDigitsInt, static_cast<int>(log10(num)) + 1);
//     }
//     int radixInt = 10; 

//     int nStrings;
//     cout << "Enter the number of strings: ";
//     cin >> nStrings;

//     // Input for string keys
//     vector<string> strArr(nStrings);
//     cout << "Enter the strings:" << endl;
//     cin.ignore(); // Ignore newline character from previous input
//     for (int i = 0; i < nStrings; ++i) {
//         getline(cin, strArr[i]);
//     }

//     int maxLengthStr = 0;
//     for (const string& str : strArr) {
//         maxLengthStr = max(maxLengthStr, static_cast<int>(str.length()));
//     }

//     // Sorting integers
//     radixSortInteger(intArr, maxDigitsInt, radixInt);

//     // Sorting strings
//     radixSortString(strArr, maxLengthStr);

//     // printing sorted integers
//     cout << "Sorted integer array: ";
//     for (int num : intArr) {
//         cout << num << " ";
//     }
//     cout << endl;

//     // printing sorted strings
//     cout << "Sorted string array: ";
//     for (const string& str : strArr) {
//         cout << str << " ";
//     }
//     cout << endl;

//     return 0;
// }

