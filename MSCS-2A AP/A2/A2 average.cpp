// // Question 1: (‘Invertible’ Stack) 

// #include <iostream>
// #include <stdexcept>
// using namespace std;

// class Stack {
// private:
//     int size;
//     int stk_ptr;
//     int *stackArray;
//     bool inverted;
//     int start;
// public:
//     Stack(int s)
//     {
//         size = s;
//         stk_ptr = 0;
//         start = 0;
//         stackArray = new int[size];
//         inverted = false;
        
//     }
    
//     bool isEmpty()
//     {
//         return (stk_ptr == 0);
//     }
    
//     bool isFull()
//     {
//         return (stk_ptr == size);
//     }

//     // Pushes an element onto the stack
//     void push(int num) 
//     {
//         if (!isFull() ) {
//             stackArray[stk_ptr] = num;
//             stk_ptr = stk_ptr + 1;
//         }
//     }
        
//     void pop(int &n) 
//     {
//         if (!isEmpty()) {
//             if (inverted) {
//                 n = stackArray[start++]; 
//             } else {
//                 n = stackArray[--stk_ptr]; 
//             }
//         }
//     }
        
//     int top()
//     {
//         int s = start;
//         int p = stk_ptr;
//         if(inverted){
//             return stackArray[s];
//         }else{
//            return  stackArray[--p];
//         }
//     }
        
//     void show(){
//         if(!inverted){
//             int p = stk_ptr-1;
//             cout<<"Not inverted Stack: "<<"\n\n";
//             while(p >= start){
//                 cout<<stackArray[p--]<<endl;
//             }
//         }else{
//             int s = start;
//             cout<<"Inverted Stack: "<<"\n\n";
//             while(s<stk_ptr){
//                 cout<<stackArray[s++]<<endl;
//             }
//         }
//     }
//     void flipStack(){
//         inverted = !inverted;
//     }
// };

// int main() {
    
//     //Instance of Stack
//     Stack stack(6);
    
//     //Push values
//     stack.push(1);
//     stack.push(2);
//     stack.push(3);
//     stack.push(4);
//     stack.push(5);
//     stack.push(6);
    
    
//     //---------------------- Before Inverting Stack ----------------
    
//     //Showing Stack
//     cout << "\nStack before inversion: \n\n";
//     stack.show();
    
//     //Pop newest element of non inverted stack
//     cout << "\nStack after pop: \n\n";
//     int p;
//     stack.pop(p);
//     //Stack after pop
//     stack.show();
    
//     //Getting first element
//     cout << "\n\nFirst Element: ";
//     cout<<stack.top();
    
    
//     //---------------------- After Inverting Stack ----------------
    
//     //Invert Stack
//     stack.flipStack();
    
//     cout << "\nStack after inversion: \n\n";
//     //Showing Stack
//     stack.show();
    
//     //Pop oldest element after inversion
//     cout << "\nStack after pop: \n\n";
//     int p;
//     stack.pop(p);
//     //Stack after pop
//     stack.show();
    
//      //Getting first element
//     cout << "\n\nFirst Element: ";
//     cout<<stack.top();

//     // std::cout << "Top element: " << stack.top() << std::endl;

//     // stack.pop();

//     // std::cout << "Top element after pop: " << stack.top() << std::endl;

//     return 0;
// }

//Question 2: (‘Undo’ Stack)

// #include <iostream>
// using namespace std;

// class UndoStack {
// private:
//     int max_size;
//     int *stack;
//     int top_element;

// public:
//     UndoStack(){
//         max_size = 100;
//         stack = new int[max_size];
//         top_element = -1;
//     }

//     bool isEmpty() const {
//         return top_element == -1;
//     }

//     bool isFull() const {
//         return top_element == max_size - 1;
//     }

//     void push(int element) {
//         if (isFull()) {
//             //Removing oldest element  If the stack is full
//             for (int i = 0; i < max_size - 1; ++i) {
//                 stack[i] = stack[i + 1];
//             }
//             top_element--;
//         }
//         stack[++top_element] = element;
//     }

//     int pop() {
//         if (isEmpty()) {
//             cout << "Stack is empty, cannot pop.\n";
//             return -1;
//         }
//         return stack[top_element--];
//     }

//     int top() const {
//         if (isEmpty()) {
//             cout << "Stack is empty.\n";
//             return -1;
//         }
//         return stack[top_element];
//     }
// };

// int main() {
    
//     //Instance
//     UndoStack stack;
    
//     // Pushing elemenets
//     for (int i = 0; i < 110; ++i) {
//         stack.push(i);
//     }
    
//     // Poping some elements
//     for (int i = 0; i < 10; ++i) {
//         std::cout << "Popped: " << stack.pop() << std::endl;
//     }
    
//     return 0;
// }

#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int MAX_DIGITS = 10; // Maximum number of digits in an integer or string key
const int MAX_VALUES = 10; // Maximum possible values for each digit (0-9)

// Radix sort for integer keys
void radixSort(int arr[], int n, int k) {
    queue<int> buckets[MAX_VALUES];
    
    // Iterate through each digit from least significant to most significant
    for (int digit = 1; digit <= k; digit++) {
        // Distribute elements into buckets based on the current digit
        for (int i = 0; i < n; i++) {
            int key = (arr[i] / static_cast<int>(pow(10, digit - 1))) % 10;
            buckets[key].push(arr[i]);
        }
        
        // Collect elements from buckets back into the array
        int index = 0;
        for (int i = 0; i < MAX_VALUES; i++) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

// Radix sort for string keys
void radixSort(string arr[], int n, int k) {
    queue<string> buckets[MAX_VALUES];
    
    for (int digit = k - 1; digit >= 0; digit--) {
        for (int i = 0; i < n; i++) {
            int key = arr[i][digit] - '0'; // Convertig character to integer value
            buckets[key].push(arr[i]);
        }
        
        int index = 0;
        for (int i = 0; i < MAX_VALUES; i++) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

int main() {
    // Example usage for integer keys
    int intArr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(intArr) / sizeof(int);
    radixSort(intArr, n, 3);
    
    cout << "Sorted integer keys: ";
    for (int i = 0; i < n; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl;
    
    string strArr[] = {"apple", "banana", "orange", "grape", "kiwi", "pear"};
    n = sizeof(strArr) / sizeof(string);
    radixSort(strArr, n, 5); // Assuming all strings have length <= 5
    
    cout << "Sorted string keys: ";
    for (int i = 0; i < n; i++) {
        cout << strArr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
