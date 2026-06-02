

#ifndef WET2MIVNI_LINKEDLIST_H
#define WET2MIVNI_LINKEDLIST_H
#include "Node.h"
template <class D>
class LinkedList {
public:
    Node<D>* m_start;
    Node<D>* m_end;
    int m_size;

public:
    class Iterator {
        Node<D>* current;
    public:
        Iterator(Node<D>* start) : current(start) {}
        bool operator!=(const Iterator& other) const { return current != other.current; }
        Iterator& operator++() { current = current->m_next; return *this; }
        Node<D>* operator*() const { return current; }
        Node<D>* getCurrent()const{
            return current;
        }
    };

    Iterator begin() { return Iterator(m_start); }
    Iterator end() { return Iterator(nullptr); }
    LinkedList():m_start(nullptr),m_end(nullptr),m_size(0){}

    ~LinkedList(){
//        while(m_start != nullptr) {
//            Node< D> *toDelete = m_start;
//            m_start = m_start->m_next;
//            delete toDelete;
//        }
    }
    int getSize() const {
        return m_size;
    }
    Node<D>* getStart() const{
        return m_start;
    }

    Node<D>* find(int key) const{
        Node<D>* temp = m_start;
        while(temp != nullptr){
            if(temp->getKey() == key){
                return temp;
            }
            temp = temp->m_next;
        }
        return nullptr;
    }
//    Node<D>* find(const D& data) const{
//        Node<D>* temp = m_start;
//        while(temp != nullptr && temp->getData()!=data){
//            temp = temp->m_next;
//        }
//        return temp;
//    }



    void add(Node<D>* node){
        if(node == nullptr){
            return;
        }
        node->m_next = nullptr;
        node->m_previous = nullptr;
        if(m_start == nullptr){
            m_start = node;
            m_end = node;
        }else{
            if(m_end != nullptr){
                m_end->m_next=node;
            }

            node->m_previous=m_end;
            node->m_next = nullptr;
            m_end = node;
        }
        m_size++;
    }


//    void add(Node<D>* node) {
//        if (!node) {
//            return;
//        }
//
//        // Ensure the node's pointers are reset
//        node->m_next = nullptr;
//        node->m_previous = nullptr;
//
//        if (m_start == nullptr) {
//            // List is empty
//            m_start = node;
//            m_end = node;
//        } else {
//            // Add to the end of the list
//
//            m_end->m_next = node;
//            node->m_previous = m_end;
//            m_end = node;
//        }
//
//        // Increment size
//        m_size++;
//    }

    void add(int key,D& data){
        add(new Node<D>(key, data));
    }

    bool remove(int key){
        Node< D>* curr = find(key);
        if (!curr) {
            return false;
        }

        if (curr->m_previous != nullptr) {
            curr = curr->m_next;
        } else {
            m_start = curr->m_next;
        }

        if (curr->m_next) {
            curr->m_next->m_previous = curr->m_previous;
        } else {
            m_end = curr->m_previous;
        }

        delete curr;
        m_size--;
        return true;
    }
    bool remove(Node<D>* node){

        if (node == nullptr) {
            return false; // Return false if the node is null
        }

        // If the node is the first node in the list
        if (node == m_start) {
            m_start = node->m_next; // Update the start to the next node
            if (m_start != nullptr) {
                m_start->m_previous = nullptr; // Detach the previous pointer of the new start
            }
        } else {
            if(node->m_previous!= nullptr){
                node->m_previous->m_next = node->m_next;
            } else{
                m_start = node->m_next;
            }
            // Update the previous node's next pointer
        }

        // If the node is the last node in the list
        if (node == m_end) {
            m_end = node->m_previous; // Update the end to the previous node
            if (m_end != nullptr) {
                m_end->m_next = nullptr; // Detach the next pointer of the new end
            }
        } else {
            if(node->m_next != nullptr){
                node->m_next->m_previous = node->m_previous;
            }else {
                m_end = node->m_previous;
            }
            // Update the next node's previous pointer
        }

        // Detach the node completely
        node->m_next = nullptr;
        node->m_previous = nullptr;
        delete node->getData();
        delete node;
        // Decrement the size of the linked list
        m_size--;

        return true; // Indicate successful removal
    }
//    bool remove2(Node<D>* node){
//
//        if(node == nullptr){
//            return false;
//        }
//        if (node->m_previous != nullptr) {
//            node->m_previous->m_next = node->m_next;
//        } else {
//            m_start = node->m_next;
//        }
//
//        if (node->m_next != nullptr) {
//            node->m_next->m_previous = node->m_previous;
//        } else {
//            m_end = node->m_previous;
//        }
//        node->m_next = nullptr;
//        node->m_previous= nullptr;
//
//
//        m_size--;
//        return true;
//    }
    bool remove2(Node<D>* node) {
        if (node == nullptr) {
            return false; // Return false if the node is null
        }

        // If the node is the first node in the list
        if (node == m_start) {
            m_start = node->m_next; // Update the start to the next node
            if (m_start != nullptr) {
                m_start->m_previous = nullptr; // Detach the previous pointer of the new start
            }
        } else {
            if(node->m_previous!= nullptr){
                node->m_previous->m_next = node->m_next;
            } else{
                m_start = node->m_next;
            }
             // Update the previous node's next pointer
        }

        // If the node is the last node in the list
        if (node == m_end) {
            m_end = node->m_previous; // Update the end to the previous node
            if (m_end != nullptr) {
                m_end->m_next = nullptr; // Detach the next pointer of the new end
            }
        } else {
            if(node->m_next != nullptr){
                node->m_next->m_previous = node->m_previous;
            }else {
                m_end = node->m_previous;
            }
             // Update the next node's previous pointer
        }

        // Detach the node completely
        node->m_next = nullptr;
        node->m_previous = nullptr;

        // Decrement the size of the linked list
        m_size--;

        return true; // Indicate successful removal
    }



};


#endif //WET2MIVNI_LINKEDLIST_H