
#ifndef WET2MIVNI_HASHTABLE_H
#define WET2MIVNI_HASHTABLE_H
#include "LinkedList.h"
#include <iostream>
#include "memory"

#pragma once

template <typename Value>
class HashTable {
private:

    LinkedList<Value>* hash_table;
    int capacity;
    int size;


public:
    HashTable() : hash_table(new LinkedList<Value>[11]), capacity(11), size(0) {}
    ~HashTable() {
        delete[] hash_table;
    }
    void setSize(int s){
        size = s;
    }
    int getSize() const {
        return size;
    }




    void increaseHash() {
        int newCapacity = capacity * 2;
        auto* newList = new LinkedList<Value>[newCapacity];

        for (int i = 0; i < capacity; ++i) {
            Node<Value>* temp = hash_table[i].getStart();
            while (temp != nullptr) {
                int newIndex = temp->getKey() % newCapacity;
                if(newIndex< 0 ){
                    newIndex += newCapacity;
                }
                Node<Value>* curr = temp;
                temp = temp->m_next;
                hash_table[i].remove2(curr);
                newList[newIndex].add(curr);

            }
        }
        delete[] hash_table;
        hash_table = newList;
        capacity = newCapacity;
    }



    void insert(Node<Value>* node) {
        if (size + 1 >= capacity * 0.75) {

            increaseHash();


        }
        int index = node->getKey() % capacity;
        if(index < 0){
            index += capacity;
        }
        hash_table[index].add(node);
        ++size;
    }
    void insert(int key ,Node<Value>* node) {
        if (size + 1 >= capacity* 0.75) {

            increaseHash();

        }

        int index = key % capacity;
        if(index < 0){
            index += capacity;
        }
        hash_table[index].add(node);
        ++size;
    }
    void insert(int key, Value value) {
        if (size + 1 >= capacity* 0.75) {

            increaseHash();

        }
        int index = key % capacity;
        if(index < 0){
            index += capacity;
        }
        hash_table[index].add(key,value);
        ++size;
    }

    Node<Value>* find( int key) const {
        int index = key % capacity;
        if(index < 0){
            index += capacity;
        }
        return hash_table[index].find(key);
    }
    bool remove(int key) {

        int index = key % capacity;
        if(index < 0){
            index+=capacity;
        }
        if(find(key)){
            hash_table[index].remove2(find(key));
            size--;
//            if(size < capacity){
//                decreaseHash();
//            }
            return true;
        }
        return false;

    }
    bool remove_with_freeing(int key) {

        int index = key % capacity;
        if(index < 0){
            index+=capacity;
        }
        if(find(key)){
            hash_table[index].remove(find(key));
            size--;
//            if(size < capacity){
//                decreaseHash();
//            }
            return true;
        }
        return false;

    }
    bool remove2(int key) {

        int index = key % capacity;
        if(index < 0){
            index+=capacity;
        }
        if(find(key)){
            hash_table[index].remove2(key);
            size--;
            return true;
        }
        return false;

    }


    LinkedList<Value>* getHashTable() const{
        return hash_table;
    }
     void setHashTable(LinkedList<Value>* l) {
         hash_table=l;
    }
    int getCapacity() const{
        return capacity;
    }

    void print() const {
        std::cout << "HashTable Contents:" << std::endl;
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            Node<Value>* current = hash_table[i].getStart();
            if (!current) {
                std::cout << "Empty";
            } else {
                while (current) {
                    std::cout << "[" << current->getKey() << ": " << *(current->m_data) << "] ";
                    current = current->m_next;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "Total size: " << size << ", Capacity: " << capacity << std::endl;
    }

};

#endif //WET2MIVNI_HASHTABLE_H
