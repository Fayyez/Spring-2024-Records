#include <iostream>
using namespace std;

class IntervalHeap {
    int hsize;
    int maxsize;
    int **h;

public:
    IntervalHeap(int s = 100) {
        maxsize = s;
        hsize = 0;
        h = new int *[2];
        h[0] = new int[maxsize];
        h[1] = new int[maxsize];
    }

    void Insert(int lower, int higher) {
        if (hsize >= maxsize) {
            cout << "Interval Heap Is Full!" << endl;
            return;
        }
        h[0][hsize] = lower;
        h[1][hsize] = higher;
        AdjustUp(hsize);
        hsize++;
    }

    void Update(int i, int newLowerValue, int newHigherValue) {
        if (i < 0 || i >= hsize) {
            cout << "Index is not valid!" << endl;
            return;
        }
        h[0][i] = newLowerValue;
        h[1][i] = newHigherValue;
        AdjustUp(i);
        AdjustDown(i);
    }

    void Delete(int i) {
        if (i < 0 || i >= hsize) {
            cout << "Index is not valid!" << endl;
            return;
        }
        // Swapping with last element
        h[0][i] = h[0][hsize - 1];
        h[1][i] = h[1][hsize - 1];
        hsize--;
        AdjustDown(i);
    }

    void show() {
        cout << "Interval Heap: ";
        for (int i = 0; i < hsize; ++i) {
            cout << "[" << h[0][i] << ", " << h[1][i] << "] ";
        }
        cout << endl;
    }

    void AdjustUp(int i) { // Adjust heap from upper side
        int parent = (i - 1) / 2; // getting parent
        while (i > 0 && h[0][parent] > h[0][i]) {
            // Swapping lower and higher values:
            int temp = h[0][parent];
            h[0][parent] = h[0][i];
            h[0][i] = temp;

            temp = h[1][parent];
            h[1][parent] = h[1][i];
            h[1][i] = temp;
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void AdjustDown(int i) { // Adjust heap from lower side
        int leftChild = 2 * i + 1; // Getting left child of current
        int rightChild = 2 * i + 2; // Getting right child of current
        int smallest = i;
        if (leftChild < hsize && h[0][leftChild] < h[0][smallest]) {
            smallest = leftChild;
        }
        if (rightChild < hsize && h[0][rightChild] < h[0][smallest]) {
            smallest = rightChild;
        }
        if (smallest != i) {
            // swaping
            int temp = h[0][i];
            h[0][i] = h[0][smallest];
            h[0][smallest] = temp;

            temp = h[1][i];
            h[1][i] = h[1][smallest];
            h[1][smallest] = temp;
            AdjustDown(smallest);
        }
    }
};

int main() {
    IntervalHeap heap; // Instance of Interval

    int lower, higher;
    char choice;

    do {
        cout << "1. Insert Interval\n";
        cout << "2. Delete Interval\n";
        cout << "3. Update Interval\n";
        cout << "4. Display Heap\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter lower and higher values of interval: ";
                cin >> lower >> higher;
                heap.Insert(lower, higher);
                break;
            case '2':
                int index;
                cout << "Enter index of interval to delete: ";
                cin >> index;
                heap.Delete(index);
                break;
            case '3':
                int ind, newLower, newHigher;
                cout << "Enter index of interval to update: ";
                cin >> ind;
                cout << "Enter new lower and higher values of interval: ";
                cin >> newLower >> newHigher;
                heap.Update(ind, newLower, newHigher);
                break;
            case '4':
                heap.show();
                break;
            case '5':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice!";
        }
        cout << endl;
    } while (choice != '5');

    return 0;
}
