#include <iostream>
#include <vector>


void run(std::istream &istream, std::ostream &ostream);

int main() {
    run(std::cin, std::cout);
}

template<typename T>
class b_tree {
    struct Node {
        bool leaf;
        std::vector<T> keys;
        std::vector<Node *> children;

        Node() = default;
        Node(bool leaf) : leaf(leaf) {}

        ~Node() {
            for (Node *ch: children) {
                delete ch;
            }
        }

        void resize(size_t _t) {
            keys.resize(2 * _t -1);
            children.resize(2 * _t);
        }
    };

    size_t t;
    Node *root;
public:
    b_tree(size_t min_degree) : t(min_degree), root(nullptr) {}

    ~b_tree() {
        if (root)
            delete root;
    }

    void insert(const T &key) {
        if (root == nullptr)
            root = new Node(true);

        if (is_node_full(root)) {
            Node *new_root = new Node(false);
            new_root->children.push_back(root);

            split_child(new_root, 0, root);
            root = new_root;
        }

        insert_non_full(root, key);
    }

    void print(std::ostream &out) {
        _print(out,root);
    }

private:
    void _print(std::ostream &out, Node *node) {
        for (const auto & key : node->keys){
            out << key << " ";
        }
        out << std::endl;

        for (auto n: node->children) {
            _print(out, n);
        }
    }

    bool is_node_full(Node *node) {
        return node->keys.size() == 2*t - 1;
    }

    void insert_non_full(Node *node, const T &key) {
        int pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos]) {
                node->keys[pos + 1] = node->keys[pos];
                --pos;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && key < node->keys[pos]) {
                --pos;
            }
            if (is_node_full(node->children[pos])) {
                split_child(node, pos, node->children[pos]);
                if (key > node->keys[pos - 1]) {
                    ++pos;
                }
            }
            insert_non_full(node->children[pos], key);
        }
    }

    void split_child(Node *x, size_t index, Node* y) {
        Node* z = new Node(y->leaf);
        z->keys.assign(y->keys.begin() + t, y->keys.end());
        if (!y->leaf) {
            z->children.assign(y->children.begin() + t, y->children.end()); // Используем assign для копирования
        }

        y->keys.resize(t - 1);
        y->children.resize(t);

        x->children.insert(x->children.begin() + index + 1, z);
        x->keys.insert(x->keys.begin() + index, y->keys[t - 1]);
    }
};

void run(std::istream &in, std::ostream &out) {
    int t;
    in >> t;
    b_tree<int> btree(t);

    for (int i = 0; i < 10; ++i){
        in >> t;
        btree.insert(t);
    }
//
//    while (in >> t) {
//        btree.insert(t);
//    }
    btree.print(out);
}
