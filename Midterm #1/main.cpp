//
//  main.cpp
//  Midterm #1
//
//  Created by Nafi on 10/16/25.
//

#include <iostream>
using namespace std;

// integers to prevent copiler warningas in main()
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// DoublyLinkedList
class DoublyLinkedList {
private:
    //Struct: Node
    struct Node {
        int data;   // The Value stored inside the node.
        Node* prev; //Pointer to the previous node in the list.
        Node* next; // Pointer to the next node in the list.
        
        // constructor to initialize the node with data and optional previous/next pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // To Store the data value
            prev = p;   // To Set previous pointer
            next = n;   // to set next pointer
        }
    };
    
    // Pointers to the beginning and end of the linked list.
    Node* head;  // Points to the first node
    Node* tail;  // Points to the last node

public:
    // It's a constructor.
    DoublyLinkedList() {
        head = nullptr;  // Initially it'll have no nodes, so head is null
        tail = nullptr;  // Since no Nodes initially, tail is null.
    }

    // insert_after()
    //Insters a new node after a specific position in the list.
    void insert_after(int value, int position) {
        // If user enters a negative position, invalid input
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        
        // a new node will be created dynamically with the given value
        Node* newNode = new Node(value);
        
        // If the list is empty, new node becomes both head and tail.
        if (!head) {
            head = tail = newNode;
            return;
        }
        
        // temporary pointer to revert the list
        Node* temp = head;
        
        // No it will Move temp forward until reaching the desired position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        
        // If position is beyond current list length, abort
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; //  allocated free memory to prevent leaks
            return;
        }
        
        // Linking the new node into the chain
        newNode->next = temp->next;  // Connecting newNode forward to the node after temp
        newNode->prev = temp;        // Connect newNode backward to temp
        
        // Move the head pointer to the next node in the list
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Or else will create a new node in the list
        
        // linked temp forward to newNode
        temp->next = newNode;
    }
    
    // delete_val()
    // Removes the first node that matches the given value.
    void delete_val(int value) {
        // If list is empty, nothing to delete
        if (!head) return;
        
        // Start from the head and look for the value
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;   // Move forward until value is found or end is reached
        // If value can't be found, then exit.
        if (!temp) return;
        //connect the node before and after the targeted node.
        if (temp->prev)
            temp->prev->next = temp->next; // Skip over temp from left side
        else
            head = temp->next;  // If deleting the head, move head forward
        if (temp->next)
            temp->next->prev = temp->prev;  // // Skip temp from right side
        else
            tail = temp->prev; // If deleting the tail, move tail backward
        
        // Free memory for the removed node
        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        if (pos <= 0) {
            cout << "Position must be > 0." << endl;
            return;
        }
        Node* temp = head;
        for (int i = 1; i < pos && temp; i++) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        if (temp == head) {
            pop_front();
            return;
        }
        if (temp == tail) {
            pop_back();
            return;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;
    return 0;
}

