#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>

template<typename T>
class AVLTree {
private:
    struct Node {
        T val;
        Node* left;
        Node* right;
        int height;

        Node(const T& value)
            : val(value), left(nullptr), right(nullptr), height(1) {}
    };

public:
    AVLTree();
    ~AVLTree();

    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);

    void insert(const T& value);
    void remove(const T& value);
    bool contains(const T& value) const;
    int getHeight() const;

private:
    Node* root;

    int height(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void balance(Node*& node);

    void insert(Node*& node, const T& value);
    void remove(Node*& node, const T& value);
    bool contains(Node* node, const T& value) const;

    Node* findMin(Node* node) const;

    void clear(Node* node);
    Node* clone(Node* node);
};

#endif // AVLTREE_HPP
