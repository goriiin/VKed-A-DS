#include <iostream>
#include <vector>
#include <cassert>



void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
}

template<typename T>
class BTree {
public:
    struct Node {
        Node(bool leaf) : leaf(leaf) {}

        ~Node() {
            for (Node *child: children) {
                delete child;
            }
        }

        bool leaf;
        std::vector<T> keys;
        std::vector<Node *> children;
    };

    BTree(size_t min_degree)
            : root(nullptr), t(min_degree) {
        assert(min_degree >= 2);
    }

    ~BTree() {
        if (root)
            delete root;
    }

    void insert(const T &key) {
        if (!root)
            root = new Node(true);

        if (is_node_full(root)) {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            split(root, 0);
        }

        insert_non_full(root, key);
    }

    void print(std::ostream&out) {
        if (root == nullptr) return;

        std::vector<Node *> currentLevel = {root};
        while (!currentLevel.empty()) {
            std::vector<Node *> nextLevel;
            for (Node *node: currentLevel) {
                for (auto &key: node->keys) {
                    out << key << " ";
                }

                if (!node->leaf) {
                    for (Node *child: node->children) {
                        nextLevel.push_back(child);
                    }
                }
            }
            out << std::endl;
            currentLevel = nextLevel;
        }
    }
private:
    Node *root;
    size_t t;
    bool is_node_full(Node *node) {
        return node->keys.size() == 2 * t - 1;
    }

    void split(Node *node, size_t index) {
        Node *child = node->children[index];
        Node *newChild = new Node(child->leaf);
        node->children.insert(node->children.begin() + index + 1, newChild);
        node->keys.insert(node->keys.begin() + index, child->keys[t - 1]);

        newChild->keys.assign(child->keys.begin() + t, child->keys.end());
        child->keys.resize(t - 1);

        if (!child->leaf) {
            newChild->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        }
    }

    void insert_non_full(Node *node, const T &key) {
        int pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos]) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && key < node->keys[pos]) {
                pos--;
            }

            if (is_node_full(node->children[pos + 1])) {
                split(node, pos + 1);
                if (key > node->keys[pos + 1]) {
                    pos++;
                }
            }
            insert_non_full(node->children[pos + 1], key);
        }
    }


};


void run(std::istream &in, std::ostream &out) {
    int t;
    in >> t;
    BTree<int> tree(t);

    int key;

    while (in >> key) {
        tree.insert(key);
    }

    tree.print(out);
}

