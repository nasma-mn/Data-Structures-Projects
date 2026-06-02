
#pragma once
using namespace std;

#include "HashTable.h"
#include <memory>
#include "Node.h"
#include "Genre.h"
#include "Song.h"
class UnionFind {
public:
    HashTable<Genre> genres;

    UnionFind():genres(){}


    Node<Genre>* Find(Node<Song>* song)  {

        auto root = song;
        int s = 0;
        while (root->get_father() != nullptr) {
            s += root->getData()->numOfGenreChanges;
            root = root->get_father();
        }

        auto curr = song;
        int toSubtract = 0;

        while (curr->get_father() != nullptr) {
            Node<Song>* temp = curr;
            int og = curr->getData()->numOfGenreChanges;
            temp->getData()->numOfGenreChanges = s - toSubtract;
            toSubtract += og;
            curr = curr->get_father();
            temp->set_father(root);
        }
        return root->getData()->genre;
    }
    int Find2(Node<Song>* song)  {

        auto root = song;
        int s = 0;
        while (root->get_father() != nullptr) {
            s += root->getData()->numOfGenreChanges;
            root = root->get_father();
        }

        auto curr = song;
        int toSubtract = 0;

        while (curr->get_father() != nullptr) {
            Node<Song>* temp = curr;
            int og = curr->getData()->numOfGenreChanges;
            temp->getData()->numOfGenreChanges = s - toSubtract;
            toSubtract += og;
            curr = curr->get_father();
            temp->set_father(root);
        }
        return s + root->getData()->numOfGenreChanges;
    }


    void unite(Node<Genre>* a, Node<Genre>* b,Node<Genre>* c) {
        if (!a || !b) {
            return;
        }

        auto root1 = a->getData()->flippedTreeRoot;
        auto root2 = b->getData()->flippedTreeRoot;
        if( a->getData()->size == 0 && b->getData()->size > 0){
            root2->getData()->numOfGenreChanges = root2->getData()->numOfGenreChanges + 1;
            root2->getData()->genre = c;
            c->getData()->flippedTreeRoot = root2;
            c->getData()->size = b->getData()->size;
            b->getData()->flippedTreeRoot = nullptr;
            b->getData()->size = 0;
        } else if(a->getData()->size > 0 && b->getData()->size == 0){
            root1->getData()->numOfGenreChanges = root1->getData()->numOfGenreChanges + 1;
            root1->getData()->genre = c;
            c->getData()->flippedTreeRoot = root1;
            c->getData()->size = a->getData()->size;
            a->getData()->flippedTreeRoot = nullptr;
            a->getData()->size = 0;
        }else if(a->getData()->size == 0 && b->getData()->size == 0){
            return;
        } else if (a->getData()->size >= b->getData()->size) {
            root1->getData()->numOfGenreChanges = root1->getData()->numOfGenreChanges+1;
            root2->getData()->numOfGenreChanges=root2->getData()->numOfGenreChanges + 1 - root1->getData()->numOfGenreChanges;
            root2->set_father(root1);
            root1->getData()->genre = c;
            root2->getData()->genre = nullptr;
            c->getData()->flippedTreeRoot = root1;
            a->getData()->flippedTreeRoot = nullptr;
            b->getData()->flippedTreeRoot = nullptr;
            c->getData()->size = a->getData()->size + b->getData()->size;
            a->getData()->size = 0;
            b->getData()->size = 0;
        } else {
            root2->getData()->numOfGenreChanges = root2->getData()->numOfGenreChanges + 1;
            root1->getData()->numOfGenreChanges = root1->getData()->numOfGenreChanges + 1 - root2->getData()->numOfGenreChanges;
            root1->set_father(root2);
            root2->getData()->genre = c;
            root1->getData()->genre = nullptr;
            c->getData()->flippedTreeRoot = root2;
            a->getData()->flippedTreeRoot = nullptr;
            b->getData()->flippedTreeRoot = nullptr;
            c->getData()->size = a->getData()->size + b->getData()->size;
            a->getData()->size = 0;
            b->getData()->size = 0;
        }
    }

    ~UnionFind() { }
};

