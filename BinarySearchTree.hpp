#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <cstddef>
#include "Queue.hpp"
#include "Vector.hpp"

template<typename T>
class BinarySearchTree {
  public:
    struct Node {
        T val;
        Node* left;
        Node* right;

        Node(const T& v) : val(v), left(nullptr), right(nullptr) {}
    };
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& other);
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);
    void BuildTree(const Vector<T>& data);
    void insert(const T& value);
    void clear();
    Node* getRoot() const;
    void PreOrder(Node* node);
    void InOrder(Node* node);
    void PostOrder(Node* node);
    void LevelOrder(Node* node);
  private:
    Node* root;
};


template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}


template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear();
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) : root(nullptr) {
    if (other.root == nullptr) return;
    Queue<Node*> q;
    q.push(other.root);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        insert(cur->val);
    }
}


template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other) {
    if (this == &other) return *this;
    clear();
    if (other.root == nullptr) return *this;
    Queue<Node*> q;
    q.push(other.root);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        insert(cur->val);
    }
    return *this;
}
    
template<typename T>
void BinarySearchTree<T>::BuildTree(const Vector<T>& data) {
    if (data.empty()) return;
    std::size_t n = data.size();
    for (std::size_t i = 0; i < n; i++) {
        insert(data[i]);
    }
}


template<typename T>
void BinarySearchTree<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    Node* cur = root;
    while (cur != nullptr) {
        if (value < cur->val) {
            if (cur->left != nullptr) {
                cur = cur->left;
                continue;
            }
            cur->left = newNode;
            return;
        }
        else if (value > cur->val) {
            if (cur->right != nullptr) {
                cur = cur->right;
                continue;
            }
            cur->right = newNode;
            return;

        }
        else {
            std::cout << "Duplicate of " << value << " detected\n";
            delete newNode;
            return;
        }
    }
}


template<typename T>
void BinarySearchTree<T>::clear() {
    if (root == nullptr) return;
    Queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        delete cur;
    }

    root = nullptr;
}


template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::getRoot() const {
    return root;
}


template<typename T>
void BinarySearchTree<T>::PreOrder(Node* node) {
    if (node == nullptr) return;
    std::cout << node->val << "\t";
    PreOrder(node->left);
    PreOrder(node->right);
}


template<typename T>
void BinarySearchTree<T>::InOrder(Node* node) {
    if (node == nullptr) return;
    InOrder(node->left);
    std::cout << node->val << "\t";
    InOrder(node->right);
}


template<typename T>
void BinarySearchTree<T>::PostOrder(Node* node) {
    if (node == nullptr) return;
    PostOrder(node->left);
    PostOrder(node->right);
    std::cout << node->val << "\t";
}


template<typename T>
void BinarySearchTree<T>::LevelOrder(Node* node) {
    if (node == nullptr) return;
    Queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        std::size_t n = q.size();
        for (std::size_t i = 0; i < n; i++) {
            Node* cur = q.front(); q.pop();
            std::cout << cur->val << "\t";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        std::cout << "\n";
    }
}

#endif // BINARYSEARCHTREE_HPP