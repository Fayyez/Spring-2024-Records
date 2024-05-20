#include <iostream>
#include <string.h>
using namespace std;

template <class T>
class Node 
{
    public:
        T data;
        Node* next;

        Node()          //default constructor
	        {
		        data = 0;
		        next = 0;
    	    }
};
    
template <class T>
class SortedSet 
{
    private:
        Node<T> * head;
        Node<T> * tail;

    public:
    
        SortedSet()         //default Construtor
	    {
		    head = 0;   
		    tail = 0;
	    }

        ~SortedSet()        // Destructor
        {
            Node<T> * curr = head;
            Node<T> * next;
            while (curr != nullptr) 
            {
                next = curr->next;
                delete curr;
                curr = next;
            }
        }
    
        void print() const 
        {
            Node<T> * curr = head;
            while (curr != nullptr) 
            {
                cout << curr->data;
                (curr->next != 0) ? cout << "->" : cout << "";
                curr = curr->next;
            }
            cout << endl;
        }
    
        void deleteFromPosition(int const index) 
        {
            Node<T> * curr = head;
            Node<T> * prev = 0;
        
            if (index == 0)      // to delete head
            {
                if (head == 0)
                return;
            
                Node<T> * temp = head;
                head = head->next;
                delete temp;
                if (head == 0) tail = 0;
            
                return;
            }
   
            for( int i=0; curr != 0 && i < index; i++)// to get node at index i
            { 
                prev = curr;
                curr = curr->next;
            }
            if (curr == 0 || index < 0) //index not in range
            {
                cout<< "Index not in range!" << " " ;
                return;
            }
        
            prev->next = curr->next;
            delete curr;
            if (prev->next == 0) tail = prev;
        }
    
        void unionSet(const SortedSet<T> & otherSet) 
        {
            Node<T> * currB = otherSet.head;
            Node<T> * prev = 0;
            Node<T> * currA = head;

            while (currA != 0 && currB != 0) 
            {
                if (currA->data < currB->data) 
                {
                    prev = currA;
                    currA = currA->next;
                } 
                else if (currA->data > currB->data) 
                {
                    Node<T> * newNode = new Node<T>;
                    newNode->data = currB->data;
                    newNode->next = currA;
                    if (prev == 0) {
                        head = newNode;
                    } else {
                        prev->next = newNode;
                    }
                    prev = newNode;
                    currB = currB->next;
                } 
                else 
                {
                    prev = currA;
                    currA = currA->next;
                    currB = currB->next;
                }
            }

            while (currB != 0) //for the remaining elements in otherSet 
            {
                insert(currB->data);
                currB = currB->next;
            }
        }

        void insert(const T data) 
        {
            Node<T> * newNode = new Node<T>;
            newNode->data = data;

            if (head == 0 || data < head->data) 
            {
                newNode->next = head;
                head = newNode;
                if (tail == 0) tail = head;
                return;
            }

            Node<T> * curr = head;
            Node<T> * prev = 0;
            while (curr != 0 && curr->data < data) //finding position
            {
                prev = curr;
                curr = curr->next;
            }
        
            if (curr != 0 && curr->data == data) // to avoid duplication
            {
                delete newNode;
                return;
            }

            prev->next = newNode;
            newNode->next = curr;
            if (curr == 0) tail = newNode;
        }
        
        //-------------Q3 Reversal of the list----------------
        void reverseList() 
        {
            if (head == 0 || head->next == 0)
                return;
    
            Node<T> * curr = head;
            Node<T> * next_temp = 0;
            Node<T> * prev = 0;
            while (curr != 0) 
            {
                next_temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next_temp;
            }
            head = prev;
        }
    
        //--------------Q2 Counter Cloclwise Rotation------------
        void rotate(int k) 
        {   
            Node<T> * curr = head;
            int length = 0;
    
            if( k <= 0 ) 
            {
                cout << "Invalid input for k!" << endl;
                return;
            }
            if(head == nullptr)
            {
                cout << "List is empty!" << endl;
                return;
            }
    
            while (curr != 0) 
            {
                length++;   // calculating total length of list to perform rotations for 'k' larger than list size
                curr = curr->next;
            }

            k = k % length;
            if (k == 0) 
            return;
    
            curr = head;
            for (int i = 0; i < k-1 ; i++) 
            {
                curr = curr->next;
            }
            tail->next = head;
            head = curr->next; 
            tail = curr; 
            curr->next = 0;
        }
};

int main() {
    SortedSet<int> LLa;
    LLa.insert(10); LLa.insert(50); LLa.insert(30); LLa.insert(70);

    SortedSet<int> LLb;
    LLb.insert(40); LLb.insert(20); LLb.insert(10); //repeating data value
    LLb.insert(60);  LLb.insert(80);  LLb.insert(100);
    

    cout << "Sorted Set A: ";
    LLa.print();

    cout << "Sorted Set B: ";
    LLb.print(); cout<< endl;

    cout << "Sorted Set A after Union: ";
    LLa.unionSet(LLb);
    LLa.print();
    
    int deleteIndex = 2;
    cout << "Sorted Set A after Deletion at index '"<< deleteIndex << "': ";
    LLa.deleteFromPosition(deleteIndex);
    LLa.print();
    
    int k = 2;
    cout << "Sorted Set A after '" << k <<  "' Rotations: ";
    LLa.rotate(k);
    LLa.print();
    
    cout << "Sorted Set B after Reversal: ";
    LLb.reverseList();
    LLb.print();

    return 0;
}