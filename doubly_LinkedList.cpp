#include <iostream>
/*
    * There are very minute differences when comparing a single linked list to its doubly counterpart
    * The only difference found in the logic is the inclusion of the prev pointer as well as small optimizations for better written code
    * So my comments will reflect that difference and only explain the parts where these differences reside
*/

template<class T>
class Node {
public:
    T data; 
    Node<T>* next; 
    Node<T>* prev; 

    Node(const T &data)
    : data(data) {
        next = nullptr;
        prev = nullptr; // stores the node previous to it, but is automatically set to nullptr
    }
}; 

template<class T>
class DoublyLinkedList {
    Node *head, *tail; 
    T length;

public: 
    DoublyLinkedList(const T &data = 0) { 
        Node<T>* newNode = new Node<T>(data); 
        head = newNode; 
        tail = newNode;  
        length = 1; 
    }

    void printDLL() { 
        Node<T>* temp = head; 

        while(temp != nullptr)  {
            std::cout << temp->data << ' '; 
            temp = temp->next;
        }

        std::cout << '\n'; 
    }

    void append(const T &data) { 
        Node<T>* newNode = new Node<T>(data); 

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
    
    void prepend(const T &data) { 
        Node<T>* newNode = new Node<T>(data);

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
    
    Node<T>* getNode(const int &index) { 
        Node<T>* temp = head;

        if(index < 0 || index >= length) {
            std::cout << "Invalid index, cannot complete this operation\n"; 
            return nullptr; // want to return nullptr instead of head/tail, to ensure the user knows that the index was invalid
        }
        else     
            for(int i = 0; i < index; i++) 
                temp = temp->next; 

        return temp; 
    }

    T getNodedata(const int &index) {
        Node<T>* temp = head;

        if(index < 0 || index >= length) {
            std::cout << "Invalid index, cannot complete this operation\n"; 
            exit(-1); 
        }
        else     
            for(int i = 0; i < index; i++) 
                temp = temp->next;
        
        return temp->data; 
    }
    
    bool setNode(const int &index, const T &data) { 
        if(index < 0 || index >= length) {
            std::cout << "Invalid index!\n"; 
            return false; 
        }
        
        Node<T>* temp = getNode(index);
        
        if(temp != nullptr) {
            temp->data = data; 
            return true; 
        } 
        return false; 
    }
    
    bool insertNode(const int &index, const T &data) { 
        if(index < 0 || index > length) {
            std::cout << "Invalid index!\n"; 
            return false; 
        }

        if(index == 0) {
            prepend(data); 
        }
        else if(index == length) {
            append(data); 
        }
        else {
            Node *prevNode = getNode(index - 1);
            Node *newNode = new Node<T>(data); 

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
            Node<T>* temp = getNode(index); 
            Node<T>* previous_temp = getNode(index-1); 

            previous_temp->next = temp->next; 
            temp->next->prev = previous_temp; // I'm accessing the previous Node for temp and setting it to point to previous_temp 

            delete temp; 
        }
        --length; 
    }

    void reverse() {
        Node<T>* current = head; 
        Node<T>* temp = nullptr; 

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
        Node<T>* temp = head; 

        while(head != nullptr) {
            head = temp->next; 
            delete temp; 
            temp = head; 
        }
    }
}; 
