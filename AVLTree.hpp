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

template<typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template<typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree& other)
    : root(clone(other.root)) {}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& other) {
    if (this != &other) {
        clear(root);
        root = clone(other.root);
    }
    return *this;
}

template<typename T>
void AVLTree<T>::insert(const T& value) {
    insert(root, value);
}

template<typename T>
void AVLTree<T>::remove(const T& value) {
    remove(root, value);
}

template<typename T>
bool AVLTree<T>::contains(const T& value) const {
    return contains(root, value);
}

template<typename T>
int AVLTree<T>::getHeight() const {
    return height(root);
}

template<typename T>
int AVLTree<T>::height(Node* node) const {
    return node ? node->height : 0;
}

template<typename T>
int AVLTree<T>::getBalance(Node* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

template<typename T>
void AVLTree<T>::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

template<typename T>
void AVLTree<T>::rotateLeft(Node*& node) {
    Node* rightChild = node->right;

    node->right = rightChild->left;
    rightChild->left = node;

    updateHeight(node);
    updateHeight(rightChild);

    node = rightChild;
}

template<typename T>
void AVLTree<T>::rotateRight(Node*& node) {
    Node* leftChild = node->left;

    node->left = leftChild->right;
    leftChild->right = node;

    updateHeight(node);
    updateHeight(leftChild);

    node = leftChild;
}

template<typename T>
void AVLTree<T>::balance(Node*& node) {
    if (!node) {
        return;
    }

    updateHeight(node);

    int bf = getBalance(node);

    // Left heavy
    if (bf > 1) {
        // Left-right case
        if (getBalance(node->left) < 0) {
            rotateLeft(node->left);
        }

        // Left-left case
        rotateRight(node);
    }

    // Right heavy
    else if (bf < -1) {
        // Right-left case
        if (getBalance(node->right) > 0) {
            rotateRight(node->right);
        }

        // Right-right case
        rotateLeft(node);
    }
}

template<typename T>
void AVLTree<T>::insert(Node*& node, const T& value) {
    if (!node) {
        node = new Node(value);
        return;
    }

    if (value < node->val) {
        insert(node->left, value);
    } else if (value > node->val) {
        insert(node->right, value);
    } else {
        return; // duplicate value
    }

    balance(node);
}

template<typename T>
void AVLTree<T>::remove(Node*& node, const T& value) {
    if (!node) {
        return;
    }

    if (value < node->val) {
        remove(node->left, value);
    } else if (value > node->val) {
        remove(node->right, value);
    } else {
        // Case 1: no child
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        }

        // Case 2: only right child
        else if (!node->left) {
            Node* oldNode = node;
            node = node->right;
            delete oldNode;
        }

        // Case 3: only left child
        else if (!node->right) {
            Node* oldNode = node;
            node = node->left;
            delete oldNode;
        }

        // Case 4: two children
        else {
            Node* successor = findMin(node->right);
            node->val = successor->val;
            remove(node->right, successor->val);
        }
    }

    balance(node);
}

template<typename T>
bool AVLTree<T>::contains(Node* node, const T& value) const {
    if (!node) {
        return false;
    }

    if (value < node->val) {
        return contains(node->left, value);
    } else if (value > node->val) {
        return contains(node->right, value);
    } else {
        return true;
    }
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template<typename T>
void AVLTree<T>::clear(Node* node) {
    if (!node) {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::clone(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* newNode = new Node(node->val);
    newNode->height = node->height;
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);

    return newNode;
}

#endif