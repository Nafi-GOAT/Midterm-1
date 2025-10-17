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
    // Deletes the node at a given position (1-based index)
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        if (pos <= 0) {
            cout << "Position must be > 0." << endl;
            return;
        }
        
        // Starts at the head
        Node* temp = head;
        
        // Moving forward to the given position
        for (int i = 1; i < pos && temp; i++) {
            temp = temp->next;
        }
        
        // If position is valid.
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        
        // Handle first node deletion
        if (temp == head) {
            pop_front();
            return;
        }
        
        // Handle last node deletion
        if (temp == tail) {
            pop_back();
            return;
        }
        
        // Reconnect surrounding nodes
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp; // Delete target node
    }
    
    // adds a new node to the end of the list.
    void push_back(int v) {
        Node* newNode = new Node(v); // creates new node with data
        if (!tail)
            head = tail = newNode; // If list empty, new node is head and tail
        else {
            tail->next = newNode;  // Old tail now points to new node
            newNode->prev = tail;  // New node points back to old tail
            tail = newNode;        // Update tail to new node
        }
    }
    //adds a new node to the front of the list.
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;  // Empty list case
        else {
            newNode->next = head;   // Link new node forward to current head
            head->prev = newNode;   // Link current head backward to new node
            head = newNode;         // Update head pointer
        }
    }

    // Removes the first node in the list.
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;  // Keep pointer to current head
        if (head->next) {
            head = head->next;  // Move head forward
            head->prev = nullptr;
        } else
            head = tail = nullptr; // Only one node existed
        delete temp;// Delete old head
    }
// Removes the last node in the list.
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;  // Keep pointer to current tail
        if (tail->prev) {
            tail = tail->prev;  // Move tail backward
            tail->next = nullptr;  // Disconnect old tail
        } else {
            head = tail = nullptr; // Only one node existed
        }
        delete temp;  // Delete the old tail node
    }
    
    // Other elemnts as per the requirments (as instructed)
    void every_other_element() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head; // Start at first node
        bool skip = false;    // Toggle to decide whether to skip or print

        while (current) {
            if (!skip)
                cout << current->data << " "; // Print if not skipping
            skip = !skip; // Flip between skip and print
            current = current->next; // Move forward to next node
        }

        cout << endl;
    }

    // Frees all dynamically allocated memory.
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head; //Store pointers to current Node
            head = head->next; // Move head to next node
            delete temp;       // Delete previous node
        }
    }
    
    // Displays all elements from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;  // Move forward through list
        }
        cout << endl;
    }

    // Displays all elements from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;  // Move backward through list
        }
        cout << endl;
    }
};

int main() {
    
    DoublyLinkedList list; // Create an empty doubly linked list

        // Add several nodes to demonstrate operations
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        list.push_back(40);
        list.push_back(50);

        cout << "Full list: ";
        list.print(); // Output all elements normally

        cout << "Every other element: ";
        list.every_other_element(); // Output every 2nd node skipped

        // Dummy line to use constants and avoid compiler warning
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;
    return 0;
}

