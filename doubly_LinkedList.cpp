#include <iostream>
/*
    * There are very minute differences when comparing a single linked list to its doubly counterpart
    * The only difference found in the logic is the inclusion of the prev pointer as well as small optimizations for better written code
    * So my comments will reflect that difference and only explain the parts where these differences reside
*/

class Node {
public:
    int value; 
    Node* next; 
    Node* prev; 

    Node(const int &value)
    : value(value) {
        next = nullptr;
        prev = nullptr; // stores the node previous to it, but is automatically set to nullptr
    }
}; 

class DoublyLinkedList {
    Node *head, *tail; 
    int length;

public: 
    DoublyLinkedList(const int &value = 0) { 
        Node* newNode = new Node(value); 
        head = newNode; 
        tail = newNode;  
        length = 1; 
    }

    void printDLL() { 
        Node* temp = head; 

        while(temp != nullptr)  {
            std::cout << temp->value << ' '; 
            temp = temp->next;
        }

        std::cout << '\n'; 
    }

    void append(const int &value) { 
        Node* newNode = new Node(value); 

        if(length == 0) {
            head = newNode;
            tail = newNode; 
        }
        else {
            newNode->prev = tail; 
            tail->next = newNode; 
            tail = newNode; 
        }
        length++; 
    }
    
    void prepend(const int &value) { 
        Node* newNode = new Node(value);

        if(length == 0) {
            head = newNode;
            tail = newNode;  
        }
        else {
            newNode->next = head; 
            head->prev = newNode;  // now we include the change required for head's prev and set it to newNode 
            head = newNode;
        }

        ++length; 
    }
    
    void deleteFirst() { 
        Node *tempNode = head; // should be a global within the function

        if(length == 0) 
            return; 
        else if(length == 1) {
            head = nullptr; 
            tail = nullptr; 
        }
        else {
            head = head->next; 
            head->prev = nullptr; // we set head->prev to nullptr so when we delete temp we can't point to freed memory
        }

        // ensure that delete is universal in order for the node to be removed from memory in both scenarios
        delete tempNode; 
        --length;
    }
     
    void deleteLast() { 
        Node *previousNode = tail;

        if(length == 0) 
            return; 
        else if(length == 1) {
            head = nullptr; 
            tail = nullptr; 
        }
        else {
            tail = tail->prev; // we set tail to to point to its previous Node 
            tail->next = nullptr; // same logic for head->prev in deleteFirst() but now for tail->next
        }

        delete previousNode; 
        --length; 
    }
    
    Node* getNode(const int &index) { 
        Node* temp = head;

        if(index < 0 || index >= length) {
            std::cout << "Invalid index, cannot complete this operation\n"; 
            return nullptr; // want to return nullptr instead of head/tail, to ensure the user knows that the index was invalid
        }
        else     
            for(int i = 0; i < index; i++) 
                temp = temp->next; 

        return temp; 
    }

    int getNodeValue(const int &index) {
        Node* temp = head;

        if(index < 0 || index >= length) {
            std::cout << "Invalid index, cannot complete this operation\n"; 
            exit(-1); 
        }
        else     
            for(int i = 0; i < index; i++) 
                temp = temp->next;
        
        return temp->value; 
    }
    
    bool setNode(const int &index, const int &value) { 
        if(index < 0 || index >= length) {
            std::cout << "Invalid index!\n"; 
            return false; 
        }
        
        Node* temp = getNode(index);
        
        if(temp != nullptr) {
            temp->value = value; 
            return true; 
        } 
        return false; 
    }
    
    bool insertNode(const int &index, const int &value) { 
        if(index < 0 || index > length) {
            std::cout << "Invalid index!\n"; 
            return false; 
        }

        if(index == 0) {
            prepend(value); 
        }
        else if(index == length) {
            append(value); 
        }
        else {
            Node *prevNode = getNode(index - 1);
            Node *newNode = new Node(value); 

            newNode->next = prevNode->next; 
            newNode->prev = prevNode; 
            prevNode->next = newNode; 
        }
        ++length; 
        return true; 
    }
    
    void deleteNode(const int &index) {
        if(index < 0 || index >= length) {
            std::cout << "Invalid index!"; 
            return; 
        }

        if(index == 0) {
            return deleteFirst();  
        }
        else if(index == (length-1)) {
            return deleteLast(); 
        }
        else {
            Node* temp = getNode(index); 
            Node* previous_temp = getNode(index-1); 

            previous_temp->next = temp->next; 
            temp->next->prev = previous_temp; // I'm accessing the previous Node for temp and setting it to point to previous_temp 

            delete temp; 
        }
        --length; 
    }

    bool isPalindrome() {
        if(length == 0)
            return false; 
        else if(head->value != tail->value) 
            return false; 
        
        Node* headTemp = head; 
        Node* tailTemp = tail; 
        
        while(headTemp != tailTemp || (headTemp != nullptr && tailTemp != nullptr)) {
            if(headTemp->value != tailTemp->value) {
                return false; 
            }
            
            headTemp = headTemp->next; 
            tailTemp = tailTemp->prev; 
        }
        
        return true; 
    }

    void reverse() {
        Node* current = head; 
        Node* temp = nullptr; 

        while(current != nullptr) {
            temp = current->prev; 
            current->prev = current->next; 
            current->next = temp; 
            current = current->prev; 
        }

        temp = head; 
        head = tail; 
        tail = temp; 
    }

    ~DoublyLinkedList() {
        Node* temp = head; 

        while(head != nullptr) {
            head = temp->next; 
            delete temp; 
            temp = head; 
        }
    }
}; 
