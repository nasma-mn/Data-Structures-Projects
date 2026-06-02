//
// Created by nsmam on 16/12/2024.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H



#include <functional>
#include "iostream"
#include "exceptions.h"


template <class Key,class Data>
class Node{
public:
    Key *key;
    Data *data;
    Node *father;
    Node *left;
    Node *right ;
    int height ;
    Node():key(nullptr),data(nullptr),father(nullptr),left(nullptr) ,right(nullptr),height(0)
    {}
    Node(const Key &key, const Data &data):father(nullptr),left(nullptr) ,right(nullptr),height(0)
    {
        this->key = new Key(key);
        this->data = new Data(data);
    }
    ~Node() {
        delete key;
        delete data;
        left = right = father = nullptr;
    }
    Node& operator=(const Node& other) {
        if (this == &other) {
            return *this; // handle self-assignment
        }

        // Delete existing data
        delete key;
        delete data;

        // Deep copy of key and data
        key = new Key(*other.key);
        data = new Data(*other.data);

        // Reset relational pointers (do not copy tree structure!)
        father = nullptr;
        left = nullptr;
        right = nullptr;
        height = other.height;

        return *this;
    }

    void updateHeight()
    {
        int right_height = (right == nullptr ? -1 : right->height);
        int left_height = (left == nullptr ? -1 : left->height);
        this->height = std::max(right_height , left_height ) + 1;
    }
    int getHeight(Node *node)
    {
        if(node == nullptr){
            return -1;
        }
        node->updateHeight();
        return node->height;
    }
    int BalanceFactor()
    {
        return ((getHeight(left)) - (getHeight(right)));
    }
    bool isLeaf()
    {
        if(right == nullptr && left == nullptr)
        {
            return true;
        }
        return false;
    }

    void swap(Node* to_swap)
    {
        if (to_swap == nullptr) return;
        auto tmpkey = to_swap->key;
        auto tmpData = to_swap->data;
        to_swap->data = this->data;
        to_swap->key = this->key;
        this->data = tmpData;
        this->key = tmpkey;
    }
    Data* getData(){
        return data;
    }
    Node(const Node&) = delete;
    //  Node& operator=(const Node&) = delete;

};


template<class Key , class Data>
class AVL_Tree{
    //  typedef Node<Key,Data> Node;
public:
    Node<Key,Data> *root;
    Node<Key,Data> *max;
    int size;

public:
    class AVLIter {
        Node<Key, Data>* current;
//        Node<Key, Data>* finish;

    public:
        AVLIter(Node<Key, Data>* current)
                : current(current) {}

        AVLIter() : current(nullptr){}

        bool operator==(const AVLIter& iter) const {
            return this->current == iter.current;
        }

        bool operator!=(const AVLIter& iter) const {
            return this->current != iter.current;
        }

        // Find the next node in an in-order traversal
        Node<Key, Data>* findNext(Node<Key, Data>* node) {
            if (node->right) {
                // Go to the leftmost node in the right subtree
                node = node->right;
                while (node->left) {
                    node = node->left;
                }
                return node;
            }

            // Traverse up until we find a node that is a left child
            while (node->father && node == node->father->right) {
                node = node->father;
            }
            return node->father;
        }

        AVLIter& operator++() {
            if (current == nullptr ) {
                // Already at the end
                return *this;
            }

            // Move to the next node in the AVL tree
            current = findNext(current);

            // If we reach the end of the tree, mark the iterator as finished
//            if (current == nullptr) {
//                current = finish;
//            }

            return *this;
        }

        Node<Key, Data>* operator*() {
            return current;
        }

        friend class AVL_Tree<Key, Data>;
    };

// Begin iterator points to the minimum node in the tree
    AVLIter begin() const {
        return AVLIter(getMin(root));
    }

// End iterator points to nullptr
    AVLIter end() const {
        return AVLIter(nullptr);
    }
    class Delete
    {
    public:
        void operator()(Node<Key,Data> *node)
        {
            if (node == nullptr){
                return;
            }
            delete node->key;
            delete node->data;
            delete node;
        }
    };
    class Print
    {
    public:
        void operator()(Node<Key,Data> *node)
        {
            std::cout<< *(node->key)<<std::endl;
        }
    };
    AVL_Tree() : root(nullptr),max(nullptr),size(0) {}
    ~AVL_Tree()
    {
        treeClear();
    }
    template <class Func>
    void inOrderTour( Node<Key,Data>*node, Func function)const;
    Node<Key,Data>* getRoot();
    Node<Key,Data>* getMax(Node<Key,Data>* node)const;
    Node<Key,Data>* getMin(Node<Key,Data>* node)const;
    int getSize()const;
    void treeClear();
    Node<Key,Data>* find(const Key &key)const;
    Node<Key,Data>* find_place(const Key &new_key) const;
    void insert( const Key &new_key, const Data &new_data);
    void aux_insert(Node<Key,Data> *node);
    void fixTree(Node<Key,Data> *node);
    void rotate_rr(Node<Key,Data> *unbalancedNode);
    void rotate_ll(Node<Key,Data> *unbalancedNode);
    void rotate_rl(Node<Key,Data> *unbalancedNode);
    void rotate_lr(Node<Key,Data> *unbalancedNode);
    void remove(const Key &key);
    bool isEmpty()const;
    Node<Key,Data>* lower_bound(Key& key);

    void UpdateBalanceFactors(Node<Key,Data> *node);
    void printTree();
};
template<class Key,class Data>
template <class Func>
void AVL_Tree<Key,Data>::inOrderTour( Node<Key,Data> *node, Func function)const{
    if (node == nullptr){
        return;
    }
    inOrderTour(node->left,function);
    function(node);
    inOrderTour(node->right);
}
template <class Key,class Data ,class Func>
void PostOrderTour( Node<Key,Data> *node, Func function){
    if (node == nullptr){
        return;
    }
    PostOrderTour(node->left,function);
    PostOrderTour(node->right,function);
    function(node);
}
template <class Key,class Data ,class Func>
void PreOrderTour( Node<Key,Data>*node, Func function){
    if (node == nullptr)
        return;
    function(node);
    PreOrderTour(node->left,function);
    PreOrderTour(node->right,function);
}

template<class Key,class Data>
Node<Key,Data>* AVL_Tree<Key,Data>::find(const Key &key)const{
    
    Node<Key,Data>* current = this->root;
    while (current != nullptr) {
        if (key == *(current->key)) {
            return current;
        } else if (key < *(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

template<class Key, class Data>
Node<Key, Data>* AVL_Tree<Key, Data>::find_place(const Key &new_key) const{
    if (this->root == nullptr) {
        return nullptr;
    }
    Node<Key,Data>* current = this->root;
    Node<Key,Data>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (new_key < *(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return parent;
}

template<class Key,class Data>
void  AVL_Tree<Key,Data>::rotate_ll(Node<Key,Data> *unbalancedNode) {
    Node<Key,Data> *leftChild = unbalancedNode->left;
    unbalancedNode->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->father = unbalancedNode;
    }
    leftChild->right = unbalancedNode;
    leftChild->father = unbalancedNode->father;
    if (unbalancedNode->father != nullptr) {
        if (unbalancedNode->father->left == unbalancedNode) {
            unbalancedNode->father->left = leftChild;
        } else {
            unbalancedNode->father->right = leftChild;
        }
    } else {
        root = leftChild;
    }
    unbalancedNode->father = leftChild;
    unbalancedNode->updateHeight();
    leftChild->updateHeight();

}
template<class Key,class Data>
void  AVL_Tree<Key,Data>::rotate_rr(Node<Key,Data> *unbalancedNode) {
    Node<Key,Data> *rightChild = unbalancedNode->right;
    unbalancedNode->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->father = unbalancedNode;
    }
    rightChild->left = unbalancedNode;
    rightChild->father = unbalancedNode->father;
    if (unbalancedNode->father != nullptr) {
        if (unbalancedNode->father->left == unbalancedNode) {
            unbalancedNode->father->left = rightChild;
        } else {
            unbalancedNode->father->right = rightChild;
        }
    } else {
        root = rightChild;
    }
    unbalancedNode->father = rightChild;
    unbalancedNode->updateHeight();
    rightChild->updateHeight();
}
template<class Key,class Data>
void  AVL_Tree<Key,Data>::rotate_lr(Node<Key,Data> *node){
    rotate_rr(node->left);
    rotate_ll(node);
}

template<class Key,class Data>
void  AVL_Tree<Key,Data>::rotate_rl(Node<Key,Data> *node){
    rotate_ll(node->right);
    rotate_rr(node);
}

template<class Key,class Data>
void  AVL_Tree<Key,Data>::insert(const Key &new_key, const Data &new_data){
    if (find(new_key) != nullptr) {
        throw AlreadyExist();
    }
    Node<Key,Data> *new_node = new Node<Key,Data>(new_key,new_data);
    AVL_Tree<Key,Data>::aux_insert(new_node);
    this->size += 1;
}
template<class Key,class Data>
void  AVL_Tree<Key,Data>::aux_insert(Node<Key,Data> *node) {
    if (this->root == nullptr) {
        this->root = node;
        return ;
    }
    else{
        node->father = find_place(*(node->key));
        if (*(node->key) < *(node->father->key)) {
            node->father->left = node;
        } else {
            node->father->right = node;
        }
        this->fixTree(node);
    }
}

template<class Key,class Data>
void AVL_Tree<Key,Data>::fixTree(Node<Key,Data> *node) {
    this->UpdateBalanceFactors(node);
    Node<Key,Data> *itr = node;
    while (itr != nullptr) {
        if (itr->BalanceFactor() == 2) {
            if (itr->left->BalanceFactor() >= 0) {
                rotate_ll(itr);
                break;
            } else if (itr->left->BalanceFactor() == -1) {
                rotate_lr(itr);
                break;
            }

        }
        if (itr->BalanceFactor() == -2) {
            if (itr->right->BalanceFactor() <= 0) {
                rotate_rr(itr);
                break;
            } else if (itr->right->BalanceFactor() == 1) {
                rotate_rl(itr);
                break;
            }
        }
        this->UpdateBalanceFactors(node);
        itr = itr->father;
    }
}

template<class Key, class Data>
void AVL_Tree<Key, Data>::remove(const Key &key) {
    Node<Key,Data> *to_delete = find(key);
    if (to_delete == nullptr) {
        throw DoNotExist();
    }
    Node<Key,Data> *temp_father = to_delete->father;
    if (to_delete->left && to_delete->right) {
        Node<Key,Data> *itr = to_delete->right;
        while (itr->left != nullptr) {
            itr = itr->left;
        }
        to_delete->swap(itr);
        to_delete = itr; // Now the node to delete has at most one child
        temp_father = to_delete->father;
    }
    if (to_delete->left || to_delete->right) {
        Node<Key,Data> *son = (to_delete->left) ? to_delete->left : to_delete->right;
        if (temp_father) {
            if (temp_father->left == to_delete) {
                temp_father->left = son;
            } else {
                temp_father->right = son;
            }
        } else {
            root = son;
        }
        son->father = temp_father;
    }
    else {
        if (temp_father) {
            if (temp_father->left == to_delete) {
                temp_father->left = nullptr;
            } else {
                temp_father->right = nullptr;
            }
        } else {
            root = nullptr;
        }
    }
    delete to_delete;
    this->size = this->size-1;
    Node<Key,Data> *itr2 = temp_father;
    this->UpdateBalanceFactors(temp_father);
    while (itr2 != nullptr) {
        if (itr2->BalanceFactor() == 2) {
            if (itr2->left->BalanceFactor() >= 0) {
                rotate_ll(itr2);
            } else if (itr2->left->BalanceFactor() == -1) {
                rotate_lr(itr2);
            }
        }
        if (itr2->BalanceFactor() == -2) {
            if (itr2->right->BalanceFactor() <= 0) {
                rotate_rr(itr2);
            } else if (itr2->right->BalanceFactor() == 1) {
                rotate_rl(itr2);
            }
        }
        this->UpdateBalanceFactors(itr2);
        itr2 = itr2->father;
    }
}

template<class Key,class Data>
Node<Key,Data> *AVL_Tree<Key,Data>::getRoot()
{
    return this->root;
}

template<class Key,class Data>
Node<Key,Data> *AVL_Tree<Key,Data>::getMax(Node<Key,Data>* node)const
{
    while (node && node->right) {
        node = node->right;
    }
    return node;
}
template<class Key,class Data>
Node<Key,Data> *AVL_Tree<Key,Data>::getMin(Node<Key,Data>* node)const
{
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template<class Key,class Data>
int AVL_Tree<Key,Data>::getSize()const
{
    return this->size;
}

//template<class Key, class Data>
//void AVL_Tree<Key, Data>::treeClear(){
//    if (root == nullptr) {
//        return;
//    }
//    PostOrderTour(root, [](Node<Key,Data>* node) {
//        delete node;
//    });
//
//    root = nullptr;
//    max = nullptr;
//    this->size = 0;
//}
template<class Key, class Data>
void AVL_Tree<Key, Data>::treeClear() {
    // Internal recursive post-order delete
    std::function<void(Node<Key, Data>*)> clear = [&](Node<Key, Data>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node; // Calls Node destructor to delete key and data
    };

    clear(this->root);
    this->root = nullptr;
    this->size = 0;
    this->max = nullptr;
}


template<class Key,class Data>
bool AVL_Tree<Key,Data>::isEmpty()const{
    if (this->size == 0){
        return true;
    } else{
        return false;
    }
}
template<class Key,class Data>
void AVL_Tree<Key,Data>::UpdateBalanceFactors(Node<Key,Data> *node){
    Node<Key,Data> *itr = node;
    while (itr != nullptr){
        itr->updateHeight();
        itr = itr->father;
    }
}
template<class Key,class Data>
void AVL_Tree<Key, Data>::printTree(){
    PreOrderTour(root, Print());  // Now PreOrderTour is recognized as a member function
}
template<class Key, class Value>
Node<Key, Value>* AVL_Tree<Key, Value>::lower_bound(Key& key) {
    Node<Key, Value>* current = root;
    Node<Key, Value>* result = nullptr;

    while (current) {
        if (!((*(current->key)) < key)) {  // current->key >= key
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}


#endif // AVL_TREE_H