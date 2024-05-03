#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        explicit Node(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
    };

    int _height(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    Node* _right_rotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(_height(y->left), _height(y->right)) + 1;
        x->height = std::max(_height(x->left), _height(x->right)) + 1;

        return x;
    }

    Node* _left_rotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(_height(x->left), _height(x->right)) + 1;
        y->height = std::max(_height(y->left), _height(y->right)) + 1;

        return y;
    }

    int _get_balance(Node* node) {
        if (node == nullptr)
            return 0;
        return _height(node->left) - _height(node->right);
    }

    void _fix_height(Node* node) {
        node->height = std::max(_height(node->left), _height(node->right)) + 1;
    }

    Node* _balance_node(Node* node) {
        int balance = _get_balance(node);

        if (balance > 1 && _get_balance(node->left) >= 0)
            return _right_rotate(node);
        if (balance > 1 && _get_balance(node->left) < 0) {
            node->left = _left_rotate(node->left);
            return _right_rotate(node);
        }
        if (balance < -1 && _get_balance(node->right) <= 0)
            return _left_rotate(node);
        if (balance < -1 && _get_balance(node->right) > 0) {
            node->right = _right_rotate(node->right);
            return _left_rotate(node);
        }

        return node;
    }

    Node* _insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
        if (node->key == key)
            return node;

        if (key < node->key)
            node->left = _insert(node->left, key);
        else if (key > node->key)
            node->right = _insert(node->right, key);
        else
            return node;

        _fix_height(node);

        return _balance_node(node);
    }

    Node* _delete(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key)
            node->left = _delete(node->left, key);
        else if (key > node->key)
            node->right = _delete(node->right, key);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                Node* temp = _min_value_node(node->right);

                node->key = temp->key;

                node->right = _delete(node->right, temp->key);
            }
        }

        _fix_height(node);

        return _balance_node(node);
    }

    Node* _min_value_node(Node* node) {
        Node* current = node;

        while (current->left != nullptr) current = current->left;

        return current;
    }

    bool _exists(Node* node, int key) {
        if (node == nullptr) return false;
        if (node->key == key) return true;
        if (key < node->key) return _exists(node->left, key);
        return _exists(node->right, key);
    }

    int _next(Node* node, int key) {
        Node* current = node;
        int next_value = key;

        while (current != nullptr) {
            if (key < current->key) {
                next_value = current->key;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return next_value;
    }

    int _prev(Node* node, int key) {
        Node* current = node;
        int prev_value = -1;
        while (current != nullptr) {
            if (key > current->key) {
                prev_value = current->key;
                current = current->right;
            } else {
                current = current->left;
            }
        }

        return prev_value;
    }
    Node* root;

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = _insert(root, key);
    }

    void remove(int key) {
        root = _delete(root, key);
    }

    bool contains(int key) {
        return _exists(root, key);
    }

    int get_next(int key) {
        return _next(root, key);
    }

    int get_prev(int key) {
        return _prev(root, key);
    }
};

int main() {
    AVLTree tree;

    string operation;
    int key;

    while (std::cin >> operation) {
        if (operation == "insert") {
            std::cin >> key;
            tree.insert(key);
        } else if (operation == "delete") {
            std::cin >> key;
            tree.remove(key);
        } else if (operation == "exists") {
            std::cin >> key;
            std::cout << (tree.contains(key) ? "true" : "false") << endl;
        } else if (operation == "next") {
            std::cin >> key;
            int next_value = tree.get_next(key);
            std::cout << (next_value != -1 ? to_string(next_value) : "none") << endl;
        } else if (operation == "prev") {
            std::cin >> key;
            int prev_value = tree.get_prev(key);
            std::cout << (prev_value != -1 ? to_string(prev_value) : "none") << endl;
        }
    }

    return 0;
}