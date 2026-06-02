//
// Created by assin on 1/15/2025.
//

#ifndef WET2MIVNI_NODE_H
#define WET2MIVNI_NODE_H
#pragma once

template<class DATA>
class Node {
public:
    int m_key;
    DATA* m_data; // Changed to raw pointer
    Node* m_next;
    Node* m_previous;
    Node* m_father;
 //   int rank;


    // Default constructor
    Node() : m_key(0), m_data(nullptr), m_next(nullptr), m_previous(nullptr), m_father(nullptr) {}

    // Copy constructor
    Node(const Node<DATA>& node)
            : m_key(node.m_key),
              m_data(node.m_data ? new DATA(*node.m_data) : nullptr),
              m_next(nullptr),
              m_previous(nullptr),
              m_father(node.m_father)
              {}


    Node(int key, const DATA& data)
            : m_key(key),
              m_data(new DATA(data)),
              m_next(nullptr),
              m_previous(nullptr),
              m_father(nullptr){}


    Node(int Key1, int key, DATA* data)
            : m_key(key),
              m_data(data),
              m_next(nullptr),
              m_previous(nullptr),
              m_father(nullptr) {}


    // Getter for data
    DATA* getData() {
        return m_data;
    }

    // Getter for key
    int getKey() {
        return m_key;
    }
    void setKey(int k){
        m_key = k;
    }

    // Getter for father
    Node<DATA>* get_father() {
        return m_father;
    }

    // Setter for father
    void set_father(Node<DATA>* new_father) {
        m_father = new_father;
    }



    // Destructor
    ~Node() {
//       delete m_data; // Clean up dynamically allocated memory
    }

    void swap(Node<DATA>* first, Node<DATA>* second) {
        int tempKey = first->m_key;
        first->m_key = second->m_key;
        second->m_key = tempKey;

        // Swap m_data
        DATA* tempData = first->m_data;
        first->m_data = second->m_data;
        second->m_data = tempData;

        // Swap m_next
        Node* tempNext = first->m_next;
        first->m_next = second->m_next;
        second->m_next = tempNext;

        // Swap m_previous
        Node* tempPrevious = first->m_previous;
        first->m_previous = second->m_previous;
        second->m_previous = tempPrevious;

        // Swap m_father
        Node* tempFather = first->m_father;
        first->m_father = second->m_father;
        second->m_father = tempFather;

        // Swap rank
        int tempRank = first->rank;
        first->rank = second->rank;
        second->rank = tempRank;
    }

};

#endif //WET2MIVNI_NODE_H
