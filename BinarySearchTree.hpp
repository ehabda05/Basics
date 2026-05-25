#include <iostream>
#include <queue>

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
  public:
    template<typename T>
    Node* BuildTree(const T& data) {
        if (data.empty()) return nullptr;
        std::size_t n = data.size();
        Node* root = new Node(data[0]);
        for (std::size_t i = 1; i < n; i++) {
            Node* cur = root;
            while (cur != nullptr) {
                if (data[i] < cur->val) {
                    if (cur->left != nullptr) {
                        cur = cur->left;
                        continue;
                    }
                    Node* newNode = new Node(data[i]);
                    cur->left = newNode;
                    break;
                }
                else if (data[i] > cur->val) {
                    if (cur->right != nullptr) {
                        cur = cur->right;
                        continue;
                    }
                    Node* newNode = new Node(data[i]);
                    cur->right = newNode;
                    break;

                }
                else {
                    std::cout << "Duplicate of " << data[i] << " detected\n";
                    break;
                }
            }
        }
        return root;
    }

    void PreOrder(Node* root) {
        if (root == nullptr) return;
        std::cout << root->val << "\t";
        PreOrder(root->left);
        PreOrder(root->right);
    }

    void InOrder(Node* root) {
        if (root == nullptr) return;
        InOrder(root->left);
        std::cout << root->val << "\t";
        InOrder(root->right);
    }

    void PostOrder(Node* root) {
        if (root == nullptr) return;
        PostOrder(root->left);
        PostOrder(root->right);
        std::cout << root->val << "\t";
    }

    void LevelOrder(Node* root) {
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);

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
};